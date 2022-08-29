//////////////////////////////////////////////////////////////////////////
// File Name	: myProxy.h						//
// Date		: 2021/05/04						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #2-2			//
//			(Construction Proxy Connection)			//
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

#define BUFFSIZE	1024
#define PORTNO		40000

// svr.c
void main_svr(void);
void sub_svr(int client_fd);

//myFunc.c
char* getHomeDir(char* homeDir);
void makeCacheDir(char* cacheDir);
void getCachePath(char* hURL, char* cacheDir, char* dirName, char* fileName);
void getOURL(int client_fd, char* oURL);
char* sha1_hash(char* oURL, char* hURL);
int isHit(char* dirName, char* hURL);
void handler(void);
