#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080

int main()
{
    int sockfd = 0;
    char buff[32];
    memset(buff, '0', sizeof(buff));
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n (client.c) The socket could not be created \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\n Connecting to server...\n");

    // if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    // {
    //     printf("(client.c) Connection Failed!\n");
    //     return 1;
    // }

    // else
    // {
    //     printf("(client.c) Connection Successful!\n");
    // }

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    int count = 0;
    char message[32];
    printf("Welcome to the Chatroom!\n");
    while (1)
    {
        printf("Message: ");
        scanf("%s", message);
        send(sockfd, message, strlen(message), 0);

        if (strcmp(message, ":exit") == 0)
        {
            printf("Disconnected\n");
            close(sockfd);
            break;
        }
        recv(sockfd, buff, strlen(buff), 0);
        printf("%s\n", buff);
    }
    return 0;
}
