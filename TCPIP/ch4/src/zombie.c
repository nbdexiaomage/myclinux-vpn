#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    __pid_t pid = fork();
    if (pid == 0)
    {
        printf("i'm child process\n");
    } else
    {
        printf("child process: %d\n", pid);
        sleep(30);
    }

    if (pid == 0)
        printf("child proess end\n");
    else
        printf("parent process end\n");
    
    return 0;
}
