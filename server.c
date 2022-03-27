#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define PORT 8040
#define PORT 8020

int main()
{
    int listenfd, connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1024];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

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

    strcpy(sendBuff, "Hello Client!");

    send(connfd, sendBuff, sizeof(sendBuff), 0);
    close(connfd);

    return 0;
    
}