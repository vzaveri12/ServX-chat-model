#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main()
{
    int listenfd, connfd = 0;
    struct sockaddr_in serv_addr;
    char recv_buffer[1024];
    char send_buffer[1024];

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(recv_buffer, '0', sizeof(recv_buffer));
    memset(send_buffer, '0', sizeof(send_buffer));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (listen(listenfd, 10) < 0){
        printf("Failed to listen\n");
        return 1;
    }
    printf("Socket Server Listening\n");

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    printf("Socket server accepted connection\n");
    recv(connfd, recv_buffer, strlen(recv_buffer), 0);
    printf("Recieved from Client: %s", recv_buffer);

    strcpy(send_buffer, "Hello Client!");

    send(connfd, send_buffer, strlen(send_buffer), 0);
    close(connfd);

    return 0;
    
}