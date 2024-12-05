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

void read_routine(int sock, char* buf)
{
    while(1)
    {
        int str_len = read(sock, buf, BUF_SIZE);
        if (str_len == 0)
            return;
        buf[str_len] = 0;
        printf("message from server: %s\n", buf);
    }
}

void write_routine(int sock, char* buf)
{
    while(1)
    {
        fgets(buf, BUF_SIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buf, strlen(buf));
    }
}

int main(int argc, char* argv[])
{
    int sock, str_len;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];
    pid_t pid;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_messagehandling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_messagehandling("connect error");
    
    pid = fork();

    if (pid == 0)
        write_routine(sock, message);
    else
        read_routine(sock, message);
    
    close(sock);
    return 0;
}