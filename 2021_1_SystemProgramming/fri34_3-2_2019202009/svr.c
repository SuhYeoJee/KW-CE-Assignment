//////////////////////////////////////////////////////////////////////////
// File Name    : svr.c                                                 //
// Date         : 2021/05/30                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #3-2 (thread)    //
// Description  : create and bind socket				//
//      wait client -> client connect -> fork()				//
//          main process: wait client connect				//
//          sub process: read HTTP request and get URL data		//
//                      find cache file, send response message		//
//                  write logfile (critical section, thread //semaphore)        //
//////////////////////////////////////////////////////////////////////////

#include "myProxy.h"

int main(void) {
	main_svr();
	return 0;
}

//////////////////////////////////////////////////////////
// main_svr						//
// =====================================================//
// Input: void						//
// Output: void						//
// Purpose: create and bind sorket, connect with client	//
//	fork() - sub process: sub_svr			//
//		 main process: wait client		//
//       if [SIGINT] write logfile and exit
//////////////////////////////////////////////////////////
void main_svr(void) {
    struct sockaddr_in server_addr, client_addr;
    int len, opt = 1;
    pid_t pid;
    mainPid = getpid(); //main process pid

    startTime = time(NULL);			//start time
    processCount = 0;
    signal(SIGCHLD, (void*)sigchld_handler); //when sub process return
    signal(SIGALRM, (void*)sigalrm_handler); //when web server timeout
    signal(SIGINT, (void*)sigint_handler);

    openLogfile();          //open logfile.txt
    if (logFp == NULL) {    //file open error
        printf("Can't open logfile. \n");
        return;
    }
    
    //get semaphore
    if ((semid = semget((key_t)40000, 1, IPC_CREAT | 0666)) == -1) { 
        printf("Server: semget failed.\n"); //semget error
        return;
    }
    arg.val = 1; // SETVAL 
    if ((semctl(semid, 0, SETVAL, arg)) == -1) { //set semaphore value
        printf("Server: semctl failed.\n"); //semctl error
        return;
    }

    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) { // make svr socket
        printf("Server: Can't open stream socket.\n"); // socket error
        return;
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero((char*)&server_addr, sizeof(server_addr)); // set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNO);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) { //bind
        printf("Server: Can't bind local address.\n"); // bind error
        return;
    }
    listen(server_fd, 5);	//listen

    while (1) {
        bzero((char*)&client_addr, sizeof(client_addr));
        len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len); //accept client
        if (client_fd < 0) { // accept error
            printf("Server: accept failed.\n");
            return;
        }

        processCount++; // + new sub process
        pid = fork();
        if (pid == -1) {	//fork err
            close(client_fd); //close socket
            close(server_fd);
            continue;
        }
        if (pid == 0) {		//sub process
            sub_svr(client_addr);
            close(client_fd); //close socket
            return;
        }
        //main process
        close(client_fd);
    }
    close(server_fd);
}

/////////////////////////////////////////////////////////////
// sub_svr						   //
// ========================================================//
// Input: struct sockaddr_in client_addr                   //
// Output: void						   //
// Purpose: read HTTP request message		           //
//    get URL and find cache file                          //
//    write logFile (critical section //semaphore, thread)//
//    if [HIT] send cache data to cleint                   // 
//    if [MISS] send client request msg to web server      //
//        send web server response msg to client           //
//        write cache file                                 //
//        if [TIME OUT]  send 'timeout msg' to client      //
/////////////////////////////////////////////////////////////
void sub_svr(struct sockaddr_in client_addr) {
    int len, cacheFile, hit;
    int socket_fd, opt = 1;
    char buf[BUFFSIZE], tmp[BUFFSIZE], oURL[BUFFSIZE], hURL[41];
    char cacheDir[40], dirName[40], fileName[100];
    struct in_addr inet_client_address;
    void* tret;
    pid_t pid;
    pid = getpid();
    inet_client_address.s_addr = client_addr.sin_addr.s_addr;

    makeCacheDir(cacheDir); //make cache Dir

    read(client_fd, buf, BUFFSIZE); //get client request message
    strcpy(tmp, buf); //to use strtok()
    getOURL(tmp, oURL); // get oURL

    strcpy(tmp, oURL);  strtok(tmp, "/");
    if (strcmp(tmp, "detectportal.firefox.com") == 0) return; //don't use
    else if (strlen(oURL) == 0) return;
    if (!oURL) return; //invalid

    sha1_hash(oURL, hURL);		//get hash
    getCachePath(hURL, cacheDir, dirName, fileName); //get cache directory, file name

    hit = isHit(dirName, hURL); //[HIT/MISS] 
    if (strchr(oURL, '/') == NULL) { //write logfile (critical section)
        printf("*PID# %d is waiting for the semaphore.\n", pid);
        p(semid); //semaphore p()
        printf("*PID# %d is in the critical zone.\n", pid);
        optr = oURL, hptr = hURL; // global valriables

        if (pthread_create(&tid, NULL, writeLogfile, (void*)&hit) != 0) { // make thread
            printf("Server: pthread_create error.\n");
            return;
        }
        printf("*PID# %d create the *TID# %d.\n", pid, (int)tid);
        pthread_join(tid, &tret); // wait thread
        printf("*TID# %d is exited.\n", (int)tid);

        v(semid); //semaphore v()
        printf("*PID# %d exited the critical section.\n", pid);
    }

    if (hit) { //[HIT] send cache
        cacheFile = open(fileName, O_RDONLY);
        if (cacheFile < 0) { // file open error
            printf("Server: can't open cacheFile");
            return;
        }
        while ((len = read(cacheFile, buf, BUFFSIZE)) > 0) //read cache file
            write(client_fd, buf, len); // send cache data to cilent
        close(cacheFile);
    }
    else {
        alarm(30); //start alarm
        socket_fd = wserver_request(buf, oURL); //open, connect socket

        cacheFile = open(fileName, O_CREAT | O_WRONLY, 0644); // write cache
        if (cacheFile < 0) { // file open error
            printf("Server: cacheFile open error");
            return;
        }
        while ((len = read(socket_fd, buf, sizeof(buf))) > 0) {	//read response msg
           alarm(0); //stop alarm
           write(client_fd, buf, len); //send res msg to client
           write(cacheFile, buf, len); //write cache data
           bzero(buf, sizeof(buf));
        }
        close(socket_fd); //close socket
        close(cacheFile); //close cache file
    }
    close(client_fd); //closee socket
    return;
}

///////////////////////////////////////////////////////////////
// wserver_request				             //
// ==========================================================//
// Input: char* buf(client request msg)                      //
//        char* oURL(client input URL www.-)                 //
// Output: int socket_fd - socket connected with web server  //	
// Purpose: create socket and connect with web server        //
//	gethostbyname is used -> need internet connection    //
//	send client request msg to web server	             //
///////////////////////////////////////////////////////////////
int wserver_request(char* buf, char* oURL) {
    int socket_fd, opt = 1;
    struct sockaddr_in wserver_addr;
    struct hostent* hent;
    char* dotted;
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {	// create socket
        printf("Server: can't create socket.\n"); //socket error
        return -1;
    }
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
    //get dotted address
    while ((hent = (struct hostent*)gethostbyname(strtok(oURL, "/"))) == NULL) sleep(1); //try again after 1sec
    dotted = inet_ntoa(*((struct in_addr*)hent->h_addr_list[0]));

    bzero((char*)&wserver_addr, sizeof(wserver_addr)); //set web server address
    wserver_addr.sin_family = AF_INET;
    wserver_addr.sin_addr.s_addr = inet_addr(dotted); //IP ADDR
    wserver_addr.sin_port = htons(80);

    while (connect(socket_fd, (struct sockaddr*)&wserver_addr, sizeof(wserver_addr)) < 0) 
        sleep(1);//try again after 1sec
    write(socket_fd, buf, strlen(buf)); //request msg to web server

    return socket_fd;
}
