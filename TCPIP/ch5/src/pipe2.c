#define _XOPEN_SOURCE
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc, char const *argv[])
{
    int fds[2];
    char str1[] = "hello";
    char str2[] = "thank you";
    char buf[BUF_SIZE];
    pid_t pid;
    
    pipe(fds);
    pid = fork();

    if (pid == 0)
    {
        write(fds[1], str1, sizeof(str1));
        sleep(2);
        read(fds[0], buf, BUF_SIZE);
        printf("child output: %s\n", buf);
    } else
    {
        read(fds[0], buf, BUF_SIZE);
        printf("parent output: %s\n", buf);
        write(fds[1], str2, sizeof(str2));
        sleep(3);
    }

    return 0;
}
