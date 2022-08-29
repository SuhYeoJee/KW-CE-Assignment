//////////////////////////////////////////////////////////////////////////
// File Name	: cli.c							//
// Date		: 2021/04/27						//
// Os		: Ubuntu 16.04 LTS 64bits				//
// Author	: Suh YeoJee						//
// Student ID	: 2019202009						//
// ---------------------------------------------------------------------//
// Title	: System Programming Assignment #2-1(socket programming)//
// Description	: create socket and connect with server			//
//		get URL input, send to server				//
//		receive and print(stdout) result (hit|miss)		//
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFSIZE	1024
#define PORTNO		40000

int cli(void);

int main(void) {
    return cli();
}


//////////////////////////////////////////////////////////
// cli							//
// =====================================================//
// Input: void						//
// Output: int (0:no error	-1: socket err)		//
// Purpose: creatd and connect socket, 			//
// 	send oURL to server, and receive result		//
//////////////////////////////////////////////////////////

int cli(void) {
    int socket_fd, len;
    struct sockaddr_in server_addr;
    char haddr[] = "127.0.0.1";
    char buf[BUFFSIZE];

    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {	// create socket
        printf("can't create socket.\n");
        return -1;
    }

    bzero(buf, sizeof(buf));
    bzero((char*)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(haddr);
    server_addr.sin_port = htons(PORTNO);

    if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {	//connect
        printf("can't connect.\n");
        return -1;
    }

    write(STDOUT_FILENO, "input URL>", 11);
    while ((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {	// stdin - oURL
        if (strncmp(buf, "bye", 3) == 0) break;
        if (write(socket_fd, buf, strlen(buf)) > 0) {	//send oURL to svr
            if ((len = read(socket_fd, buf, sizeof(buf))) > 0) {	//rcv result
                write(STDOUT_FILENO, buf, len);		//print result(HIT/MISS)
                bzero(buf, sizeof(buf));
            }
        }
        write(STDOUT_FILENO, "input URL>", 11);
    }
    close(socket_fd);
    return 0;
}
