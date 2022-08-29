//////////////////////////////////////////////////////////////////////////
// File Name	: myProxy.h						//
// Date         : 2021/05/30                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #3-2 (thread)    //
// Description	: include header file 					//
//                 define macro (BUFFSIZE, PORTNO)			//
//                 function declaration (svr.c, myFunc.c)		//
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //write, read, close
#include <sys/types.h> //fork
#include <sys/wait.h> //waitpid
#include <fcntl.h>//creat
#include <sys/socket.h> //socket
#include <netinet/in.h>
#include <signal.h>
#include <arpa/inet.h>
#include <netdb.h> //gethostbyname
#include <time.h>
#include <sys/ipc.h> //semaphore
#include <sys/sem.h> //semaphore
#include <pthread.h> //thread

#define BUFFSIZE	1024
#define PORTNO		40000

int client_fd, server_fd;
int  processCount;
FILE* logFp;
time_t startTime, endTime;
pid_t mainPid; //main_svr pid
int semid; //semaphore

char* optr, *hptr;
pthread_t tid;

union semun { //semctl()
    int val;
    struct semid_ds* buf;
    unsigned short int* array;
}arg;

// svr.c
void main_svr(void);
void sub_svr(struct sockaddr_in client_addr);
int wserver_request(char* buf, char* oURL);

//myFunc.c
char* getHomeDir(char* homeDir);
void makeCacheDir(char* cacheDir);
void getCachePath(char* hURL, char* cacheDir, char* dirName, char* fileName);
void openLogfile(void);
void* writeLogfile(void* hitptr);
void getOURL(char* buf, char* oURL);
char* sha1_hash(char* oURL, char* hURL);
int isHit(char* dirName, char* hURL);
void sigchld_handler(void);
void sigalrm_handler(void);
void sigint_handler(void);
void p(int semid);
void v(int semid);
