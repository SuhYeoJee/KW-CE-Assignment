//////////////////////////////////////////////////////////////////////////
// File Name	: svr.c							//
// Date		: 2021/04/27						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #2-1(socket programming)//
// Description	: create and bind sorket				//
//	wait client -> client connect -> fork()				//
//	main process: wait client again					//
//	sub process: get URL input(buf) and find cache file		//
//		write log(logfile), result(buf)				//
//////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <pwd.h>
#include <openssl/sha.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>

#define BUFFSIZE	1024
#define PORTNO		40000

static void handler(void){
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0);
}

void main_svr(void);
void sub_svr(int client_fd);

void getCachePath(char* hURL, char* cacheDir, char* dirName, char* fileName);
void makeDir(char* homeDir, char* cacheDir, char* logDir, char* logFile);
char* getHomeDir(char* homeDir);
char* sha1_hash(char* oURL, char* hURL);
int isHit(char* dirName, char* hURL);
void writeLogfile(int hit, FILE* logFp, pid_t pid, char* oURL, char *hURL, struct tm* tp);


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
    int socket_fd, client_fd;
    int len, len_out;
    char buf[BUFFSIZE];
    pid_t pid;

    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Server: Can't open stream socket.\n");
        return;
    }

    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORTNO);

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("Server: Can't bind local address.\n");
        return;
    }

    listen(socket_fd, 5);	//listen
    signal(SIGCHLD, (void*)handler); //when sub process return

    while (1) {
        bzero((char*)&client_addr, sizeof(client_addr));
        len = sizeof(client_addr);
        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &len); //accept
        if (client_fd < 0) {
            printf("Server: accept failed.\n");
            return;
        }

        printf("[%d: %d] client was connected.\n", client_addr.sin_addr.s_addr, client_addr.sin_port);
        pid = fork();
        if (pid == -1) {	//fork err
            close(client_fd);
            close(socket_fd);
            continue;
        }
        if (pid == 0) {		//sub process
            sub_svr(client_fd);		
            printf("[%d: %d] client was disconnected.\n", client_addr.sin_addr.s_addr, client_addr.sin_port);
            close(client_fd);
            return;
        }
        close(client_fd); //main process
    }
    close(socket_fd);
    return;
}


//////////////////////////////////////////////////////////
// sub_svr						//
// =====================================================//
// Input: int client_fd	- socket (connected with client)//
// Output: void						//
// Purpose: create and bind sorket, connect with client	//
//		get URL input(buf) and find cache file	//
//		write log(logfile), result(buf)		//
//////////////////////////////////////////////////////////

void sub_svr(int client_fd) {
    int len_out;
    FILE* logFp;
    char oURL[BUFFSIZE], hURL[41];
    char homeDir[40], cacheDir[40], logDir[40], logFile[40];
    char dirName[45], fileName[81];
    int hitCount = 0, missCount = 0, hit=0;
    time_t startTime, endTime, nowTime;
    struct tm* tp;
    pid_t pid;

    makeDir(homeDir, cacheDir, logDir, logFile); //make cache/logDir, log path
    logFp = fopen(logFile, "at");		//open logfile.txt	

    pid = getpid();		//sub svr process id
    startTime = time(NULL);			//start time

    while ((len_out = read(client_fd, oURL, BUFFSIZE)) > 0) { //read
        if (!strncmp(oURL, "bye", 3)) break;
        oURL[len_out - 1] = '\0';

        time(&nowTime);	//get now time
        tp = localtime(&nowTime);

        sha1_hash(oURL, hURL);		//get hash
        getCachePath(hURL, cacheDir, dirName, fileName);

        if (hit = isHit(dirName, hURL)) {	//[HIT]
            hitCount++;
            write(client_fd,"HIT\n", 5); //send result to cli
        }
        else {		//[MISS]
            missCount++;
            creat(fileName,0644);	//[MISS] make cache file
            write(client_fd, "MISS\n",6); //send result to cli
        }
        writeLogfile(hit, logFp, pid, oURL, hURL, tp);
    }
    endTime = time(NULL);		//end Time
    fprintf(logFp, "[Terminated] ServerPID: %d | run time: %d sec, #request hit: %d, miss: %d\n", //write logfile
        pid, endTime - startTime, hitCount, missCount);
    fclose(logFp);
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
// makeDir						//
// =====================================================//
// Input: char* homeDir -> NULL->"~"			//
// char* cacheDir -> NULL->"~/cache"			//
// char* logDir -> NULL->"~/logfile"			//
// char* logFile -> NULL->"~/logfile/logfile.txt"	//
// Output: void						//
// Purpose: get path (home, cache,log dirctory,logfile)	//	
//	make dirctory (cache, log dirctory) 		//
//////////////////////////////////////////////////////////

void makeDir(char* homeDir, char* cacheDir, char* logDir, char* logFile) {
    getHomeDir(homeDir);		//get home dirctory

    strcpy(cacheDir, homeDir);		//get cache dirctory
    strcat(cacheDir, "/cache");
    mkdir(cacheDir, S_IRWXU | S_IRWXG | S_IRWXO); //make cache dir

    strcpy(logDir, homeDir);		//get logfile dirctory
    strcat(logDir, "/logfile");
    mkdir(logDir, S_IRWXU | S_IRWXG | S_IRWXO);	//make logfile dir

    strcpy(logFile, logDir);		//get logfile path
    strcat(logFile, "/logfile.txt");
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

void writeLogfile(int hit, FILE* logFp, pid_t pid, char* oURL, char *hURL, struct tm* tp) {
    if (hit == 1) {
        fprintf(logFp, "[HIT] ServerPID: %d | %.3s/%s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n", //write logfile
            pid, hURL, hURL + 3,
            1900 + tp->tm_year, tp->tm_mon, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
            fprintf(logFp, "[HIT] %s\n", oURL);
    }
    else if (hit == 0) {
        fprintf(logFp, "[MISS] ServerPID: %d | %s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n", //write logfile
            pid, oURL, 1900 + tp->tm_year, tp->tm_mon, tp->tm_mday, tp->tm_hour, tp->tm_min, tp->tm_sec);
    }
    fflush(logFp);
}
