//////////////////////////////////////////////////////////////////////////
// File Name	: proxy_cache.c						//
// Date		: 2021/04/06						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #1-2 (proxy server)	//
// Description	: Get hash, Make cache, log Directory and File		//
//////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>

int main(void){
	proxy_cache();
	return 0;
}


//////////////////////////////////////////////////////////
// proxy_cache						//
// =====================================================//
// Input: void						//
// Output: void						//
// Purpose: get Hash, make cache,log Directory and File	//
//////////////////////////////////////////////////////////

void proxy_cache(void){
	char oURL[40], hURL[41];	
	char dirName[45], fileName[81];
	char homeDir[40], cacheDir[40], logDir[40];
	DIR *pDir;
	struct dirent *pFile;
	int IsHit = 0, hitCount = 0, missCount = 0;
	FILE *logFp;
	time_t startTime, endTime, nowTime;
	struct tm *tp;

	startTime = time(NULL);			//start time

	getHomeDir(homeDir);
	strcpy(cacheDir, homeDir);		//get cache dirctory
	strcat(cacheDir,"/cache");
	mkdir(cacheDir, S_IRWXU | S_IRWXG | S_IRWXO ); //make cache dir
	strcat(cacheDir,"/");

	strcpy(logDir, homeDir);		//get logfile dirctory
	strcat(logDir, "/logfile");
	mkdir(logDir, S_IRWXU | S_IRWXG | S_IRWXO );	//make logfile dir
	strcat(logDir, "/logfile.txt");
	logFp = fopen(logDir, "wt");		//open logfile.txt	

	while(1){
		IsHit = 0;
		printf("input URL> ");		//get URL
		scanf("%s",oURL);
		
		time(&nowTime);	//get time
		tp = localtime(&nowTime);		

		if(!strcmp(oURL, "bye")) break;

		sha1_hash(oURL,hURL);		//get hash
		strcpy(dirName, cacheDir);	//get directory name
		strncat(dirName, hURL,3);
		
		strcpy(fileName, dirName);	//get file name
		strcat(fileName, "/");
		strcat(fileName, hURL+3);

		pDir = opendir(dirName);
		if(pDir == NULL) {		//[MISS] make directory
			umask(0000);
			mkdir(dirName, S_IRWXU | S_IRWXG | S_IRWXO );
		}
		else{				//read pDir	
			for(pFile=readdir(pDir);pFile;pFile=readdir(pDir)) {
				if(strcmp(pFile->d_name, hURL+3)==0){
					IsHit = 1;	//[HIT] 
					break;
				}
			}
		}
		closedir(pDir);

		if(IsHit){	//[HIT]
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
