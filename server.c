#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define PORT 8080
#define MAX_USERS 10

struct user
{
    char username[32];
    char password[32];
};

void registerUser(struct user *userInfo);

int main()
{
    int listenfd, connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[32];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (listen(listenfd, 10) < 0)
    {
        printf("Failed to listen\n");
        return 1;
    }
    printf("Socket Server Listening\n");

    int option;
    int total, usersOnline = 0;
    struct user *userInfo, *ptr;
    userInfo = (struct user *)malloc(sizeof(struct user) * MAX_USERS);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        printf("Socket server accepted connection\n");

        printf("\nWelcome to the Chatroom!\n");
        printf("Type q to quit // Type pm to privately message\n");
        printf("1. Login\n");
        printf("2. Register\n");

        //printf("\nOption:");
        scanf("%d", &option);

        if (option == 1)
        {
            strcpy(sendBuff, "Not implemented yet. Come back later!");
            send(connfd, sendBuff, sizeof(sendBuff), 0);
            break;
        }

        else if (option == 2)
        {
            if (total >= 10)
            {
                strcpy(sendBuff, "Sorry, the server is full!\n");
                send(connfd, sendBuff, sizeof(sendBuff), 0);
                break;
            }
            registerUser(userInfo);
            char str[32];
            sprintf(str, "%s has been registered!\n", userInfo->username);
            send(connfd, str, sizeof(str), 0);
            total++;
            userInfo++;
            continue;
        }

        else{
            printf("Not a valid option. Please try again!\n");
            continue;
        }
    }
    close(connfd);
    return 0;
}

void registerUser(struct user *userInfo)
{
    FILE *userFile;
    userFile = fopen("users.txt", "a");

    printf("Registering a user...");
    printf("\nEnter your username: ");
    fgets(userInfo->username, 32, stdin);
    getchar();
    fprintf(userFile, "%s", userInfo->username);
    userInfo++;
}