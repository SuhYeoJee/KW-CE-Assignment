//////////////////////////////////////////////////////////////////////////
// File Name	: proxy_cache.c						//
// Date		: 2021/04/09						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #1-3 (proxy server)	//
// Description	: get URL hash and find cache. write logfile		//
//		main process: get CMD input and fork sub process	//
//		sub process: get URL input and find cache file		//
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

void sub_proxy_cache(FILE* logFp, char* cacheDir);
void getCachePath(char* hURL, char* cacheDir, char* dirName, char* fileName);
void makeDir(char* homeDir, char* cacheDir, char* logDir, char* logFile);
char* getHomeDir(char* homeDir);
char* sha1_hash(char* oURL, char* hURL);
int isHit(char* dirName, char* hURL);
void main_proxy_cache(void);

int main(void){
	main_proxy_cache();
	return 0;
}


//////////////////////////////////////////////////////////
// main_proxy_cache					//
// =====================================================//
// Input: void						//
// Output: void						//
// Purpose: get CMD input, fork sub process, write log	//
// CMD: input, quit					//
//////////////////////////////////////////////////////////

void main_proxy_cache(void) {
	char inCMD[10];
	char homeDir[40], cacheDir[40], logDir[40], logFile[40];
	int processCount = 0, status;
	pid_t mainPid, pid;
	FILE* logFp;
	time_t startTime, endTime;

	mainPid = getpid();		//main pid
	startTime = time(NULL);			//start time

	makeDir(homeDir, cacheDir, logDir, logFile); //make cache/logDir, log path
	logFp = fopen(logFile, "at");		//open logfile.txt	

	while (1) {
		printf("[%d]input CMD> ",mainPid);		//get URL
		scanf("%s", inCMD);
		if (!strcmp(inCMD, "quit")) break; //quit
		else if (!strcmp(inCMD, "connect")) {
			if ((pid = fork()) < 0) {	//fork
				printf("fork err\n");
				break;	//fork err
			}
			else if (pid == 0) {	//sub process
				sub_proxy_cache(logFp, cacheDir);
				return;
			}
			processCount++;		//main process
			if ((pid = waitpid(pid, &status, 0)) < 0) {
				printf("waitpid err\n");
				break;//waitpid error
			}
		}
		else printf("CMD err\n");	//cmd err
	}
	//quit
	endTime = time(NULL);		//end Time
	fprintf(logFp, "**SERVER** [Terminated] run time: %d sec, #sub process: %d\n",
		endTime - startTime, processCount);

	fclose(logFp);
	return;
}


//////////////////////////////////////////////////////////
// sub_proxy_cache					//
// =====================================================//
// Input: FILE* logFp -> logfile			//
//		char * cacheDir	-> "~/cache"		//
// Output: void						//
// Purpose: get Hash, check HIT or MISS			//
//		make cache file, write logfile		//
//////////////////////////////////////////////////////////

void sub_proxy_cache(FILE* logFp, char * cacheDir){
	char oURL[40], hURL[41];	
	char dirName[45], fileName[81];
	int hitCount = 0, missCount = 0;
	time_t startTime, endTime, nowTime;
	struct tm *tp;
	pid_t pid;

	pid = getpid();
	startTime = time(NULL);			//start time

	while(1){
		printf("[%d]input URL> ",pid);		//get URL
		scanf("%s",oURL);
		
		time(&nowTime);	//get time
		tp = localtime(&nowTime);		

		if(!strcmp(oURL, "bye")) break;

		sha1_hash(oURL,hURL);		//get hash
		getCachePath(hURL, cacheDir, dirName, fileName);

		//write logfile
		if(isHit(dirName, hURL)){	//[HIT]
			hitCount++;
			fprintf(logFp,"[HIT] %.3s/%s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n",
				hURL,hURL+3, 
				1900 + tp->tm_year, tp->tm_mon, tp->tm_mday,
				tp->tm_hour, tp->tm_min, tp->tm_sec);
			fprintf(logFp,"[HIT] %s\n",oURL);
		}
		else {		//[MISS]
			missCount++;
			creat(fileName);	//[MISS] make cache file
			fprintf(logFp,"[MISS] %s - [%.4d/%.2d/%.2d, %.2d:%.2d:%.2d]\n",
				oURL, 1900 + tp->tm_year, tp->tm_mon, tp->tm_mday,
				tp->tm_hour, tp->tm_min, tp->tm_sec);
		}
	}	
	
	endTime = time(NULL);		//end Time
	fprintf(logFp,"[Terminated] run time: %d sec, #request hit: %d, miss: %d\n",
		endTime - startTime, hitCount, missCount); 

	fclose(logFp);
	return;
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
			if (strcmp(pFile->d_name, hURL + 3) == 0) {
				return 1;	//[HIT] 
			}
		}
	}
	closedir(pDir);
	return 0; //[MISS]
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

void getCachePath(char* hURL, char* cacheDir, char*dirName, char* fileName) {
	strcpy(dirName, cacheDir);	//get directory name
	strcat(dirName, "/");
	strncat(dirName, hURL, 3);

	strcpy(fileName, dirName);	//get file name
	strcat(fileName, "/");
	strcat(fileName, hURL + 3);
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

