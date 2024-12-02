#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_messagehandling(char* message);

int main(int argc, char* argv[])
{
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_len;
    char* message = "hello world";

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
    int clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_len);
    if(clnt_sock == -1)
        error_messagehandling("accpet error");

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_messagehandling(char* message)
{
    fputs(message, stderr);
    fputs("\n", stderr);
    exit(1);
}