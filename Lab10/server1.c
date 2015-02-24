/* 
 * server1.c - establishes a simple Unix socket connection with a client 
 * and exchanges a message 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;
    char ch;

	 /* establishes a socket connection with a server */
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
    listen(server_sockfd, 5);
    printf("server waiting\n");
    client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);

	 /* exchange a message */
    read(client_sockfd, &ch, 1);
    ch++;
    write(client_sockfd, &ch, 1);

    close(client_sockfd);
	 exit(0);
}
