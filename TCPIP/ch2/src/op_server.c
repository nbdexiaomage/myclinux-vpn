#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#define BUF_SIZE 1024
#define ARRAY_SIZE 256
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
    int count = 0;
    int result;
    int array[ARRAY_SIZE];
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
        count = 0;
        while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
        {
            message[str_len] = 0;
            int flag = (!strcmp(message, "+\n") || !strcmp(message, "-\n") || 
                !strcmp(message, "*\n") || !strcmp(message, "/\n"));
            if (count > 1 && flag)
            {
                result = array[0];
                if (!strcmp(message, "+\n"))
                {
                    for (size_t i = 1; i < count; i++)
                        result += array[i];
                }
                if (!strcmp(message, "-\n"))
                {
                    for (size_t i = 1; i < count; i++)
                        result -= array[i];
                }
                if (!strcmp(message, "*\n"))
                {
                    for (size_t i = 1; i < count; i++)
                        result *= array[i];
                }
                if (!strcmp(message, "/\n"))
                {
                    for (size_t i = 1; i < count; i++)
                        result /= array[i];
                }
                int change_len = snprintf(message, sizeof(message), "%d", result);
                write(clnt_sock, message, change_len);
            } else
            {
                array[count] = atoi(message);
                count++;
            }
        }
        
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}