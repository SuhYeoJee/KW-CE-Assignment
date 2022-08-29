//////////////////////////////////////////////////////////////////////////
// File Name    : svr.c                                                 //
// Date         : 2021/05/04                                            //
// Os           : Ubuntu 16.04 LTS 64bits                               //
// Author       : Suh YeoJee                                            //
// Student ID   : 2019202009                                            //
// ---------------------------------------------------------------------//
// Title        : System Programming Assignment #2-2                    //
//                      (Construction Proxy Connection)                 //
// Description  : create and bind socket				//
//      wait client -> client connect -> fork()				//
//          main process: wait client connect				//
//          sub process: read HTTP request and get URL data		//
//                      find cache file, send response message		//
//////////////////////////////////////////////////////////////////////////


#include "myProxy.h"

#include <sys/socket.h> //socket
#include <netinet/in.h>
#include <signal.h>

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
    int opt = 1;

    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Server: Can't open stream socket.\n");
        return;
    }
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

        printf("[%d: %d] client was connected.\n", 
            client_addr.sin_addr.s_addr, client_addr.sin_port);
        pid = fork();
        if (pid == -1) {	//fork err
            close(client_fd);
            close(socket_fd);
            continue;
        }
        if (pid == 0) {		//sub process
            sub_svr(client_fd);		
            printf("[%d: %d] client was disconnected.\n",
                client_addr.sin_addr.s_addr, client_addr.sin_port);
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
// Purpose: read HTTP request message			//
//		get URL and find cache file		//
//		send response message (HIT/MISS)	//
//////////////////////////////////////////////////////////
void sub_svr(int client_fd) {
    int len;

    char buf[BUFFSIZE];
    char response_header[BUFFSIZE];
    char response_message[BUFFSIZE];
    
    char oURL[BUFFSIZE], hURL[41], msg[10];
    char cacheDir[40], dirName[40], fileName[100];

    makeCacheDir(cacheDir); //make cache Dir
   
    getOURL(client_fd, oURL); //get req msg, get oURL
    sha1_hash(oURL, hURL);		//get hash

    getCachePath(hURL, cacheDir, dirName, fileName);

    if (isHit(dirName, hURL)) strcpy(msg, "HIT");
    else {
        strcpy(msg, "MISS");
        creat(fileName, 0644);
    }
    printf("%s\n", msg);
    sprintf(response_message,
        "<h1>%s</h1><br>", msg);

    sprintf(response_header,
        "HTTP/1.0 200 OK\r\n"
        "Server:simple web server\r\n"
        "Content-length:%lu\r\n"
        "Content-type:text/html\r\n\r\n", strlen(response_message));

    write(client_fd, response_header, strlen(response_header));
    write(client_fd, response_message, strlen(response_message));

    close(client_fd);

    return;
}
