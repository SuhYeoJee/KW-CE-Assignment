//////////////////////////////////////////////////////////////////////////
// File Name    : myFunc.c                                              //
// Date         : 2021/05/30                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #3-2 (thread)    //
// Description  : function definition					//
//      (1) Directory: getHomeDir, makeCacheDir, getCachePath,          //
//      (2) Logfile: openLogfile, writeLogfile                          //
//      (3) Read request message: getOURL				//
//      (4) hashing: sha1_hash						//
//      (5) cache: isHit						//
//      (6) signal handler: SIGCHLD, SIGALRM, SIGINT handler		//
//      (7) semaphore: p, v                                             //
//////////////////////////////////////////////////////////////////////////

#include "myProxy.h"

#include <pwd.h> //getHomeDir
#include <openssl/sha.h> //sha1_hash
#include <sys/stat.h>//file access permission
#include <dirent.h>


//////////////////////////////////////////////////////////
// getHomeDir						//
// =====================================================//
// Input: char* homeDir ->NULL ->"~"			//
// Output: char* - homeDir 				//
// Purpose: get home dirctory 				//
//////////////////////////////////////////////////////////
char* getHomeDir(char* homeDir) {
    struct passwd* usr_info = getpwuid(getuid());
    strcpy(homeDir, usr_info->pw_dir);
    return homeDir; // home dir string
}

//////////////////////////////////////////////////////////
// makeCacheDir						//
// =====================================================//
// Input: char cacheDir					//
// char* cacheDir -> NULL->"~/cache"			//
// Output: void						//
// Purpose: get CacheDir				//
//////////////////////////////////////////////////////////
void makeCacheDir(char* cacheDir) {
    char homeDir[40] = { 0 };
    getHomeDir(homeDir);		//get home directory

    strcpy(cacheDir, homeDir);		//get cache directory
    strcat(cacheDir, "/cache");
    mkdir(cacheDir, S_IRWXU | S_IRWXG | S_IRWXO); //make cache dir
}

//////////////////////////////////////////////////////////
// getCachePath						//
// =====================================================//
// Input: char* hURL -> hashed URL			//
// char* cacheDir -> "~/cache"				//
// char*dirName -> NULL->"~/cache/hURL[0:2]"		//
// char* fileName -> NULL->"~/cache/hURL[0:2]/hURL[2:]"	//
// Output: void						//
// Purpose: get path (cache dir, file)			//
//////////////////////////////////////////////////////////
void getCachePath(char* hURL, char* cacheDir, char* dirName, char* fileName) {
    strcpy(dirName, cacheDir);	//get directory name
    strcat(dirName, "/");
    strncat(dirName, hURL, 3); //first 3 char

    strcpy(fileName, dirName);	//get file name
    strcat(fileName, "/");
    strcat(fileName, hURL + 3); // after directory name
}

//////////////////////////////////////////////////////////
// openLogfile						//
// =====================================================//
// Input: void			//
// Output: void 				//
// Purpose: make logfile dir and open logfile.txt	//
//     (global) FILE* logFp = logfile.txt
//////////////////////////////////////////////////////////
void openLogfile(void) {
    char homeDir[40], logDir[40], logFile[40];
    getHomeDir(homeDir);    //get home directory

    strcpy(logDir, homeDir);		//get logfile dirctory
    strcat(logDir, "/logfile");
    mkdir(logDir, S_IRWXU | S_IRWXG | S_IRWXO);	//make logfile dir

    strcpy(logFile, logDir);		//get logfile path
    strcat(logFile, "/logfile.txt");

    logFp = fopen(logFile, "at"); //open or create logFile
    return;
}


//////////////////////////////////////////////////////////
// writeLogfile						//
// =====================================================//
// Input: void* hitptr - return value of isHit: HIT(1), MISS(0)
// Output: void* 				//
// Purpose: write logfile.txt
//          *critical section, thread
//           sleep (5) for test
//////////////////////////////////////////////////////////
void* writeLogfile (void * hit) {
    time_t nowTime;
    struct tm* tp;

    time(&nowTime);	//get time
    tp = localtime(&nowTime);

    if (*(int*)hit) { //[HIT]
        fprintf(logFp, "[HIT] %.3s/%s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n",
            hptr, hptr + 3,
            1900 + tp->tm_year, tp->tm_mon, tp->tm_mday,
            tp->tm_hour, tp->tm_min, tp->tm_sec);
        fprintf(logFp, "[HIT] %s\n", optr);
    }
    else { //[MISS]
        fprintf(logFp, "[MISS] %s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n",
            optr, 1900 + tp->tm_year, tp->tm_mon, tp->tm_mday,
            tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    sleep(5);
}

//////////////////////////////////////////////////////////
// getOURL						//
// =====================================================//
// Input: int client_fd, char* oURL			//
// char* oURL: NULL -> request oURL 			//
// Output: void					    	//
// Purpose: read request and get oURL			//
//////////////////////////////////////////////////////////
void getOURL(char* buf, char* oURL) {
    char method[20] = { 0, };
    char url[BUFFSIZE] = { 0, };
    char* tok = NULL;
    tok = strtok(buf, " ");
    strcpy(method, tok);
    if (strcmp(method, "GET") == 0) { // http GET msg
        strtok(NULL, "/");
        tok = strtok(NULL, " ");
        if (tok[0] == '/') tok = tok + 1;   // remove '/'
        if (tok[strlen(tok) - 1] == '/')tok[strlen(tok) - 1] = '\0';
        strcpy(url, tok);
    }
    else strcpy(url, "\0"); //don't use

    strcpy(oURL, url);
    return;
}

//////////////////////////////////////////////////////////
// sha1_hash						//
// =====================================================//
// Input: char* oURL -> input URL 			//
// char* hURL -> NULL -> hashed URL			//
// Output: char* - hURL					//
// Purpose: get hashed URL 				//
//////////////////////////////////////////////////////////
char* sha1_hash(char* oURL, char* hURL) {
    unsigned char hashed_160bits[20];
    char hashed_hex[41];
    int i;

    SHA1(oURL, strlen(oURL), hashed_160bits);

    for (i = 0; i < sizeof(hashed_160bits); i++)
        sprintf(hashed_hex + i * 2, "%02x", hashed_160bits[i]);

    strcpy(hURL, hashed_hex);
    return hURL;
}


//////////////////////////////////////////////////////////
// isHit						//
// =====================================================//
// Input: char* dirName -> "~/cache/hURL[0:2]		//
//		char* hURL -> hashed URL		//
// Output: int - 0 MISS					//
//		 1 HIT					//
// Purpose: check HIT or MISS				//
//////////////////////////////////////////////////////////
int isHit(char* dirName, char* hURL) {
    DIR* pDir;
    struct dirent* pFile;

    pDir = opendir(dirName);
    if (pDir == NULL) {		//[MISS] make directory
        umask(0000);
        mkdir(dirName, S_IRWXU | S_IRWXG | S_IRWXO);
    }
    else {				//read pDir	
        for (pFile = readdir(pDir); pFile; pFile = readdir(pDir)) {
            if (strcmp(pFile->d_name, hURL + 3) == 0)   return 1;	//[HIT] 
        }
    }
    closedir(pDir);
    return 0; //[MISS]
}

//////////////////////////////////////////////////////////
// sigchld_handler						//
// =====================================================//
// Input: void 						//
// Output: void						//
// Purpose: sigchld handler (reap process)		//
//////////////////////////////////////////////////////////
void sigchld_handler(void) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0); //reap sub process
}

//////////////////////////////////////////////////////////
// sigalrm_handler						//
// =====================================================//
// Input: void 						//
// Output: void						//
// Purpose: SIGALRM handler                             //
//          send time out message to client             //
//          terminate sub process                       //
//////////////////////////////////////////////////////////
void sigalrm_handler(void) {
    char response_header[BUFFSIZE];
    char response_message[BUFFSIZE];

    sprintf(response_message,
        "<h1>TIME OUT</h1><br>");

    sprintf(response_header,
        "HTTP/1.0 200 OK\r\n"
        "Server:simple web server\r\n"
        "Content-length:%lu\r\n"
        "Content-type:text/html\r\n\r\n", strlen(response_message));

    write(client_fd, response_header, strlen(response_header)); //send TIMEOUT msg to client
    write(client_fd, response_message, strlen(response_message));
    raise(SIGINT);
}

//////////////////////////////////////////////////////////
// sigint_handler						//
// =====================================================//
// Input: void 						//
// Output: void						//
// Purpose: sigchld handler		//
//      write logfile and exit
//////////////////////////////////////////////////////////
void sigint_handler(void) {
    if ((logFp)&&(mainPid==getpid())) { // main process write logfile
        endTime = time(NULL);		//end Time
        fprintf(logFp, "**SERVER** [Terminated] run time: %d sec, #sub process: %d\n",
            (int)(endTime - startTime), processCount);
        fclose(logFp); //close file
    }
    exit(0);
}


//////////////////////////////////////////////////////////
// p						        //
// =====================================================//
// Input: int semid: semaphore id			//
// Output: void						//
// Purpose: before critical section, wait semaphore     //
//////////////////////////////////////////////////////////
void p(int semid) {
    struct sembuf pbuf; //set semop
    pbuf.sem_num = 0;
    pbuf.sem_op = -1;
    pbuf.sem_flg = SEM_UNDO;
    if ((semop(semid, &pbuf, 1)) == -1) { // wait semaphore
        printf("server: p() semop failed\n");
        exit(1);
    }
}

//////////////////////////////////////////////////////////
// v					        	//
// =====================================================//
// Input: int semid: semaphore id			//
// Output: void						//
// Purpose: after critical section, return semaphore    //
//////////////////////////////////////////////////////////
void v(int semid) {
    struct sembuf vbuf; //set semop
    vbuf.sem_num = 0;
    vbuf.sem_op = 1;
    vbuf.sem_flg = SEM_UNDO;
    if ((semop(semid, &vbuf, 1)) == -1) { //return semaphore
        printf("server: v() semop failed\n");
        exit(1);
    }
}
