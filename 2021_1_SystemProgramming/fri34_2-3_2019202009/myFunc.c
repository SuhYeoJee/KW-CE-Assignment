//////////////////////////////////////////////////////////////////////////
// File Name    : myFunc.c                                              //
// Date         : 2021/05/11                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #2-3                    //
//                      (Construction Proxy Connection)                 //
// Description  : function definition					//
//      (1) Directory: getHomeDir, makeCacheDir, getCachePath		//
//      (2) Read request message: getOURL				//
//      (3) hashing: sha1_hash						//
//      (4) cache: isHit						//
//      (5) signal handler: handler, timeOut				//
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
    return homeDir;
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
    getHomeDir(homeDir);		//get home dirctory

    strcpy(cacheDir, homeDir);		//get cache dirctory
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
    strncat(dirName, hURL, 3);

    strcpy(fileName, dirName);	//get file name
    strcat(fileName, "/");
    strcat(fileName, hURL + 3);
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
    if (strcmp(method, "GET") == 0)
    {
        strtok(NULL, "//");
        tok = strtok(NULL, "/");
        strcpy(url, tok);
    }
    else strcpy(url, "\0");

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
            if (strcmp(pFile->d_name, hURL + 3) == 0) 
                return 1;	//[HIT] 
        }
    }
    closedir(pDir);
    return 0; //[MISS]
}

//////////////////////////////////////////////////////////
// handler						//
// =====================================================//
// Input: void 						//
// Output: void						//
// Purpose: signal handler (reap process)		//
//////////////////////////////////////////////////////////
void handler(void) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
}

//////////////////////////////////////////////////////////
// timeOut						//
// =====================================================//
// Input: void 						//
// Output: void						//
// Purpose: SIGALRM handler                             //
//          send time out message to client             //
//          terminate sub process                       //
//////////////////////////////////////////////////////////
void timeOut(void) {
    char response_header[BUFFSIZE];
    char response_message[BUFFSIZE];

    sprintf(response_message,
        "<h1>TIME OUT</h1><br>");

    sprintf(response_header,
        "HTTP/1.0 200 OK\r\n"
        "Server:simple web server\r\n"
        "Content-length:%lu\r\n"
        "Content-type:text/html\r\n\r\n", strlen(response_message));

    write(client_fd, response_header, strlen(response_header));
    write(client_fd, response_message, strlen(response_message));
    write(STDOUT_FILENO, response_header, strlen(response_header));
    write(STDOUT_FILENO, response_message, strlen(response_message));
    raise(SIGINT);
}

