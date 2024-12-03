#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
void erroe_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int sock;
    char message[BUF_SIZE];
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_adr_size;
    int str_len;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        erroe_handling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        erroe_handling("bind error");

    while(1)
    {
        clnt_adr_size = sizeof(clnt_addr);
        str_len = recvfrom(sock, message, BUF_SIZE - 1, 0, 
            (struct sockaddr*) &clnt_addr, &clnt_adr_size);
        sendto(sock, message, str_len, 0, 
            (struct sockaddr*) &clnt_addr, sizeof(clnt_addr));
    }
    
    
    close(sock);
    
    return 0;
}
