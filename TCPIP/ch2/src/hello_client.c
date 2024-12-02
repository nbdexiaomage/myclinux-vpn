#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_messagehandling(char* message)
{
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}

int main(int argc, char* argv[])
{
    struct sockaddr_in serv_addr;
    char message[100];

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_messagehandling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_messagehandling("connect error");

    int str_len = read(sock, message, sizeof(message)-1);
    if(str_len == -1)
        error_messagehandling("read error");

    printf("message from server: %s\n", message);
    close(sock);
    return 0;
}