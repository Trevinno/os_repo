#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main()
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
 
/*  Create an unnamed socket for the server.  */
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
 
/*  Name the socket.  */
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
 
/*  Create a connection queue and wait for clients.  */
    listen(server_sockfd, 5);
    while(1) {
        char ch[50];

/*  Accept a connection.  */
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
 
/*  We can now read/write to client on client_sockfd.  */
	read(client_sockfd, &ch, 50);
	FILE *archivo;
	char caracter;
	archivo=fopen("log.txt","r+");
	while (feof(archivo) == 0)
	{
		caracter = fgetc(archivo);
		printf("%c",caracter);
	}
	fprintf(archivo, ch);
	
	fprintf(archivo,"\n");
        fclose(archivo);
	
        write(client_sockfd, &ch, 50);
        close(client_sockfd);
    }
}
