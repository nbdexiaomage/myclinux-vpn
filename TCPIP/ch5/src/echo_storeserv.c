#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/socket.h>
#define BUF_SIZE 30

void erroe_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("removed proc id: %d\n", pid);
}

int main(int argc, char const *argv[])
{
    int fds[2];
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_adsz;

    pid_t pid;
    struct sigaction act;
    char buf[BUF_SIZE];
    int str_len, state;

    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    state = sigaction(SIGCHLD, &act, 0);

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        erroe_handling("socket error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        erroe_handling("bind error");

    if(listen(serv_sock, 5) == -1)
        erroe_handling("listen error");
    
    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        FILE* fp = fopen("echomsg.txt", "wt");
        char msgbuf[BUF_SIZE];
        int i, len;
        for (i = 0; i < 10; i++)
        {
            len = read(fds[0], msgbuf, BUF_SIZE);
            fwrite((void*)msgbuf, 1, len, fp);
        }
        fclose(fp);
        return 0;
    }
    
    while (1)
    {
        clnt_adsz = sizeof(clnt_addr);
        clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_adsz);
        if (clnt_sock == -1)
            continue;
        else
            printf("client connect...\n");
        pid = fork();
        if (pid == -1)
        {
            close(clnt_sock);
            continue;
        }
        if (pid == 0)
        {
            close(serv_sock);
            while((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)
            {
                write(clnt_sock, buf, str_len);
                write(fds[1], buf, str_len);
            }
            close(clnt_sock);
            puts("client disconnected...");
            return 0;
        } else
        {
            close(clnt_sock);
        }
    }
    close(serv_sock);
    
    return 0;
}