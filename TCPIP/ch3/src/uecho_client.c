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
    int str_len;
    char message[BUF_SIZE];
    struct sockaddr_in serv_addr, from_addr;
    socklen_t adr_size;

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1)
        erroe_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while (1)
    {
        fputs("input message(q to quit):", stdout);
        fgets(message, sizeof(message), stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        sendto(sock, message, strlen(message), 0, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
        adr_size = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*) &from_addr, &adr_size);
        message[str_len] = 0;
        printf("message from server: %s", message);
    }
    close(sock);
    return 0;
}
