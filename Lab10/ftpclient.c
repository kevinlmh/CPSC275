/*
 *  ftpclient.c - Internet domain, connection-based client
 *  
 *  Author: Luke Bradford-Winkler and Kevin Liu
 *  Date: Nov 24 2014
 *
 *  Run it with:
 *
 *     $ ./ftpclient <server>
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	char buf[BUFSIZ];
	int server_sockfd, len;
	struct sockaddr_in server_address;
	struct hostent *host;		/* the host (server) */
	char cmd[10], filename[50];

	if (argc != 2) {
		fprintf(stderr, "usage: %s server\n", argv[0]);
		exit(1);
	}
	host = gethostbyname(argv[1]);
	if (host == (struct hostent *) NULL) {
		perror("gethostbyname ");
		exit(2);
	}

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	memcpy(&server_address.sin_addr, host->h_addr, host->h_length);
	server_address.sin_port = htons(6996);

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(3);
	}

	if (connect(server_sockfd, (struct sockaddr *) &server_address, 
   	    sizeof(server_address)) < 0) {
		perror("connect error");
		exit(4);
	}
	while(1) {
		write(STDOUT_FILENO, "> ", 3);
		if ((len=read(STDIN_FILENO, buf, BUFSIZ)) > 0) {
			char cmd[10], filename[50];
			sscanf(buf, "%s %s", cmd, filename);	
			//printf("client: cmd = %s, filename = %s\n", cmd, filename);
			if (strcmp(cmd, "put") == 0) {
				write(server_sockfd, buf, BUFSIZ);
				int filefd = open(filename, O_RDONLY);	
				while ((len=read(filefd, buf, 1)) > 0) {
					write(server_sockfd, buf, 1);
				}
				*buf = 0;
				write(server_sockfd, buf, 1);
				close(filefd);
			} else if (strcmp(cmd, "get") == 0) {
				write(server_sockfd, buf, BUFSIZ);
				char sfilename[100] = "from_server_";
				strcat(sfilename, filename);
				int filefd = creat(sfilename, S_IRUSR | S_IWUSR);
				while((len=read(server_sockfd, buf, 1)) > 0) {
					if (*buf != 0)
						write(filefd, buf, len);	
					else break;
				}	
				close(filefd);
			} else if (strcmp(cmd, "bye") == 0) {
				break;
			}
		}
	}
	close(server_sockfd);
	exit(0);
}
