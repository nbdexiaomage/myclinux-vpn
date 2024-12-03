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
    int sock, str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_addr;
    char message[BUF_SIZE];

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
        fputs("input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);

        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
            break;
        
        str_len = write(sock, message, strlen(message));
        recv_len = 0;
        while (recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if(recv_cnt == -1)
                error_messagehandling("read error");
            recv_len += recv_cnt;
        }
        
        message[str_len] = 0;
        printf("message from server: %s", message);
    }
    close(sock);
    return 0;
}