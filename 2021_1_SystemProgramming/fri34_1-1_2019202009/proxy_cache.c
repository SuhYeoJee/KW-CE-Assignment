//////////////////////////////////////////////////////////////////////////
// File Name	: proxy_cache.c						//
// Date		: 2021/03/30						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #1-1 (proxy server)	//
// Description	: Get hash, Make Directory and File			//
//////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main(void){
	proxy_cache();
	return 0;
}


//////////////////////////////////////////////////////////
// proxy_cache						//
// =====================================================//
// Input: void						//
// Output: void						//
// Purpose: get Hash, make Directory and File		//
//////////////////////////////////////////////////////////

void proxy_cache(void){
	char oURL[40], hURL[41];	
	char dirName[45], fileName[81], homeDir[40];	
	DIR *pDir;

	getHomeDir(homeDir);
	strcat(homeDir,"/cache\0");
	mkdir(homeDir, S_IRWXU | S_IRWXG | S_IRWXO );
	strcat(homeDir,"/\0");
	

	while(1){
		printf("input URL> ");		//get URL
		scanf("%s",oURL);
		
		if(!strcmp(oURL, "bye")) break;

		sha1_hash(oURL,hURL);		//get hash
		strcpy(dirName, homeDir);	//get directory name
		strncat(dirName, hURL,3);
		
		pDir = opendir(dirName);
		if(pDir == NULL) {		//make directory
			umask(0000);
			mkdir(dirName, S_IRWXU | S_IRWXG | S_IRWXO );
		}
		strcpy(fileName, dirName);	//get file name
		strcat(fileName, "/\0");
		strcat(fileName, hURL+3);
		creat(fileName);		//make file
	}	
	return;
}
