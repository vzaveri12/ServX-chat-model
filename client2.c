#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8040

int main()
{
    int sockfd = 0;
    char buff[1024];
    memset(buff, '0', sizeof(buff));
    struct sockaddr_in serv_addr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n The socket could not be created \n");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\n Connecting to server...\n");

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed!\n");
        return 1;
    }

    else
    {
        printf("Connection Successful!\n");
    }

    recv(sockfd, buff, strlen(buff), 0);
    printf("Recieved from Server: %s\n", buff);
    close(sockfd);
    return 0;
}
