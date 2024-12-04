#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 30
void erroe_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int servsock;
    struct sockaddr_in serv_addr;
    // char message[BUF_SIZE];
    char msg1[] = "hi";
    char msg2[] = "i'm udp host client";
    char msg3[] = "nice to meet you";


    servsock = socket(PF_INET, SOCK_DGRAM, 0);
    if(servsock == -1)
        erroe_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    sendto(servsock, msg1, sizeof(msg1), 0, 
        (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    sendto(servsock, msg2, sizeof(msg2), 0, 
        (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    sendto(servsock, msg3, sizeof(msg3), 0, 
        (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    close(servsock);
    printf("closeed\n");
    return 0;
}
