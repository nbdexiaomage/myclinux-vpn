#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        printf("removed proc id: %d\n", pid);
        printf("child send: %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0);

    pid = fork();

    if (pid == 0)
    {
        puts("i'm child process");
        sleep(10);
        return 12;
    } else
    {
        printf("child process %d\n", pid);
        pid = fork();
        if (pid == 0)
        {
            puts("I'm child process");
            sleep(10);
            exit(24);
        } else
        {
            printf("child process %d\n", pid);
            for (int i = 0; i < 5; i++)
            {
                puts("Wait...");
                sleep(5);
            }
            
        }
    }
    return 0;
}
