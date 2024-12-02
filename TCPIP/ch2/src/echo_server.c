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
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int str_len;
    socklen_t clnt_addr_len;
    char message[BUF_SIZE];

    int serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_messagehandling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_messagehandling("bind error");
    
    if(listen(serv_sock, 5) == -1)
        error_messagehandling("listen error");
    
    clnt_addr_len = sizeof(clnt_addr);

    for (int i = 0; i < 5; i++)
    {
        int clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_len);
        if(clnt_sock == -1)
            error_messagehandling("accept error");
        else
            printf("connect client %d\n", i + 1);
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
            write(clnt_sock, message, str_len);
        
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}