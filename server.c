#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

struct userInfo
{
    char username[32];
    int userfd;
};

int main()
{
    int listenfd, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in new_addr;

    socklen_t addr_size;

    char recvBuff[32];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(recvBuff, '0', sizeof(recvBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Failed to bind\n");
        return 1;
    }
    else
    {
        printf("Binded successfully!\n");
    }

    //bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (listen(listenfd, 10) < 0)
    {
        printf("(server.c) Failed to listen\n");
        return 1;
    }
    printf("Socket Server Listening\n");

    int nrecv;
    int count = 0;
    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr *)&new_addr, &addr_size);

        if (fork() == 0)
        {
            close(listenfd);
            count++;
            printf("Socket server accepted connection\n");
            while (1)
            {
                nrecv = recv(connfd, recvBuff, 32, 0);
                recvBuff[nrecv] = '\0';
                if (strcmp(recvBuff, ":exit") == 0)
                {
                    printf("Client[%d] disconnected from the server!\n", count);
                    break;
                }
                else
                {
                    printf("Client[%d]: %s\n", count, recvBuff);
                    send(connfd, recvBuff, sizeof(recvBuff), 0);
                    bzero(recvBuff, sizeof(recvBuff));
                }
            }
            exit(0);
        }
        else
        {
            printf("Parent process terminated\n");
            close(connfd);
            break;
        }
    }

    return 0;
}