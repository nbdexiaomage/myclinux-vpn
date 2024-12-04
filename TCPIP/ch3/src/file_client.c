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
    int serv_sock;
    int read_cnt;
    struct sockaddr_in serv_addr;
    char buf[BUF_SIZE];
    FILE* fp;

    fp = fopen("receive.dat", "wb");
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        erroe_handling("socket error");
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        erroe_handling("connect error");

    while((read_cnt = read(serv_sock, buf, BUF_SIZE)) != 0)
        fwrite((void*)buf, 1, read_cnt, fp);
    
    puts("Receive file data");
    write(serv_sock, "Thank you", 10);
    fclose(fp);
    close(serv_sock);
    
    return 0;
}
