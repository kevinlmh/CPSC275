/*
 *  ftpserver.c - Internet domain, connection-based server
 *
 *  Author: Luke Bradford-Winkler and Kevin Liu
 *  Date: Nov 24 2014
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
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
	char buf[BUFSIZ];
	int server_sockfd, client_sockfd, client_len;
	struct sockaddr_in client_address, server_address;
	int len, i;

	if ((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		exit(1);
	}
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(6996);

	if (bind(server_sockfd, (struct sockaddr *) &server_address, 
	    sizeof(server_address)) < 0) {
		perror("bind error");
		close(server_sockfd);
		exit(2);
	}
	if (listen(server_sockfd, 5) < 0) {
		perror("listen error");
		exit(3);
	}
	client_len = sizeof(client_address);
	if ((client_sockfd = accept(server_sockfd, 
	    (struct sockaddr *) &client_address, &client_len)) < 0) {
		perror("accept error");
		close(server_sockfd);
		exit(4);
	}
	while ((len=read(client_sockfd, buf, BUFSIZ)) > 0) {
		char cmd[10], filename[20];
		sscanf(buf, "%s %s", cmd, filename);
		//printf("server: cmd = %s, filename = %s\n", cmd, filename);
		if (strcmp(cmd, "put") == 0) {
			char sfilename[100] = "from_client_";
			strcat(sfilename, filename);
			int filefd = creat(sfilename, S_IRUSR | S_IWUSR);
			while((len=read(client_sockfd, buf, 1)) > 0) {
				if (*buf != 0)
					write(filefd, buf, len);	
				else break;
			}	
			close(filefd);
		} else if (strcmp(cmd, "get") == 0) {
			char sfilename[100] = "from_client_";
			strcat(sfilename, filename);
			int filefd = open(sfilename, O_RDONLY);
			while ((len=read(filefd, buf, 1)) > 0) {
				write(client_sockfd, buf, 1);
			}
			*buf = 0;
			write(client_sockfd, buf, 1);
			close(filefd);
		}
	}
	close(client_sockfd);
}
