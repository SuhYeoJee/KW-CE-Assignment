//////////////////////////////////////////////////////////////////////////
// File Name    : svr.c                                                 //
// Date         : 2021/05/11                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #2-3                    //
//                      (Construction Proxy Connection)                 //
// Description  : create and bind socket				//
//      wait client -> client connect -> fork()				//
//          main process: wait client connect				//
//          sub process: read HTTP request and get URL data		//
//                      find cache file, send response message		//
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
//////////////////////////////////////////////////////////
void main_svr(void) {
    struct sockaddr_in server_addr, client_addr;
    int server_fd;// , client_fd;
    int len, len_out;
    char buf[BUFFSIZE];
    pid_t pid;
    int opt = 1;

    signal(SIGCHLD, (void*)handler); //when sub process return
    signal(SIGALRM, (void*)timeOut);
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Server: Can't open stream socket.\n");
        return;
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNO);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Server: Can't bind local address.\n");
        return;
    }

    listen(server_fd, 5);	//listen

    while (1) {
        bzero((char*)&client_addr, sizeof(client_addr));
        len = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &len); //accept
        if (client_fd < 0) {
            printf("Server: accept failed.\n");
            return;
        }

        printf("[%d: %d] client was connected.\n",
                client_addr.sin_addr.s_addr, client_addr.sin_port);
        pid = fork();
        if (pid == -1) {	//fork err
            close(client_fd);
            close(server_fd);
            continue;
        }
        if (pid == 0) {		//sub process
        sub_svr(client_addr);
            printf("[%d: %d] client was disconnected.\n",
                    client_addr.sin_addr.s_addr, client_addr.sin_port);
            close(client_fd);
            return;
        }
        close(client_fd); //main process
    }
    close(server_fd);
    return;
}

/////////////////////////////////////////////////////////////
// sub_svr						   //
// ========================================================//
// Input: struct sockaddr_in client_addr                   //
// Output: void						   //
// Purpose: read HTTP request message		           //
//    get URL and find cache file                          //
//    if [HIT] send cache data to cleint                   //
//    if [MISS] send client request msg to web server      //
//        send web server response msg to client           //
//        write cache file                                 //
//        if [TIME OUT] (10s) send 'timeout msg' to client //
/////////////////////////////////////////////////////////////
void sub_svr(struct sockaddr_in client_addr) {
    int len, cacheFile;
    int opt = 1;

    char buf[BUFFSIZE], tmp[BUFFSIZE];
    char oURL[BUFFSIZE], hURL[41];
    char cacheDir[40], dirName[40], fileName[100];
    char* dotted;

    int socket_fd;
    struct in_addr inet_client_address;
    inet_client_address.s_addr = client_addr.sin_addr.s_addr;
	
    makeCacheDir(cacheDir); //make cache Dir

    read(client_fd, buf, BUFFSIZE);
    strcpy(tmp, buf);
    getOURL(tmp, oURL); // get oURL
    if (strcmp(oURL, "detectportal.firefox.com") == 0) return;
    else if (strlen(oURL) == 0) return;

    if (!oURL) return;
    printf("\noURL: %s\n", oURL);
    puts("==============================");
    printf("Request form [%s : %d]\n",
            inet_ntoa(inet_client_address), client_addr.sin_port);
    puts(buf);
    puts("==============================");

    sha1_hash(oURL, hURL);		//get hash
    getCachePath(hURL, cacheDir, dirName, fileName);

    if (isHit(dirName, hURL)) { //[HIT] send cache
        printf("**HIT**\n");
        cacheFile = open(fileName, O_RDONLY);
        if (cacheFile < 0) {
            printf("Server: can't open cacheFile");
            return;
        }
        while ((len = read(cacheFile, buf, BUFFSIZE)) > 0) {
            write(client_fd, buf, len);
            write(STDOUT_FILENO, buf, len);
        }
        close(cacheFile);
    }
    else {
        printf("**MISS**\n");
        alarm(10); //start alarm(10)
        socket_fd = wserver_request(buf, oURL); //open, connect socket

        cacheFile = open(fileName, O_CREAT | O_WRONLY, 0644); // write cache
        if (cacheFile < 0) {
            printf("Server: cacheFile open error");
            return;
        }
        while ((len = read(socket_fd, buf, sizeof(buf))) > 0) {	//response msg
           alarm(0); //stop alarm
           write(client_fd, buf, len);
           write(cacheFile, buf, len);
           write(STDOUT_FILENO, buf, len);
           bzero(buf, sizeof(buf));
        }
        close(socket_fd);
        close(cacheFile);
    }
    close(client_fd);
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
    int socket_fd;
    int opt = 1;
    struct sockaddr_in wserver_addr;
    struct hostent* hent;
    char* dotted;
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {	// create socket
        printf("Server: can't create socket.\n");
        return -1;
    }
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
    while ((hent = (struct hostent*)gethostbyname(oURL)) == NULL) sleep(1);
    dotted = inet_ntoa(*((struct in_addr*)hent->h_addr_list[0]));

    bzero((char*)&wserver_addr, sizeof(wserver_addr));
    wserver_addr.sin_family = AF_INET;
    wserver_addr.sin_addr.s_addr = inet_addr(dotted); //IP ADDR
    wserver_addr.sin_port = htons(80);

    printf("connect: %s\n", dotted);
    while (connect(socket_fd, (struct sockaddr*)&wserver_addr, sizeof(wserver_addr)) < 0) sleep(1);
    write(socket_fd, buf, strlen(buf)); //request msg

    return socket_fd;
}
