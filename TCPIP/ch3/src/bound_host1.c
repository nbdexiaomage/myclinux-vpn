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
    struct sockaddr_in serv_addr, clnt_addr;
    char message[BUF_SIZE];
    socklen_t clnt_addr_len;

    servsock = socket(PF_INET, SOCK_DGRAM, 0);
    if(servsock == -1)
        erroe_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(servsock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        erroe_handling("bind error");

    for (int i = 0; i < 3; i++)
    {
        sleep(5);
        clnt_addr_len = sizeof(clnt_addr);
        recvfrom(servsock, message, BUF_SIZE, 0, 
            (struct sockaddr*) &clnt_addr, &clnt_addr_len);
        
        printf("message %d %s\n", i+1, message);
    }
    
    close(servsock);
    return 0;
}

