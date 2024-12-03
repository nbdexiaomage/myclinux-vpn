#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void error_messagehandling(char* message)
{
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}

int main(int argc, char* argv[])
{
    int sock, str_len;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    char result[BUF_SIZE];

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_messagehandling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_messagehandling("connect error");
    
    while(1)
    {
        fputs("input message(op to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        write(sock, message, strlen(message));
        if(!strcmp(message, "+\n") || !strcmp(message, "-\n") || 
            !strcmp(message, "*\n") || !strcmp(message, "/\n"))
            break;
    }
    str_len = read(sock, result, BUF_SIZE - 1);
    result[str_len] = 0;
    printf("result from server: %s\n", result);
    close(sock);
    return 0;
}