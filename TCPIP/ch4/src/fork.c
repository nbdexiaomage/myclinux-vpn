#include <stdio.h>
#include <unistd.h>

int gval = 10;
int main(int argc, char const *argv[])
{
    __pid_t pid;
    int lval = 20;
    lval += 5;
    pid = fork();

    if (pid == 0)
    {
        gval += 2;
        lval += 2;
    }else
    {
        gval -= 2;
        lval -= 2;
    }

    if (pid == 0)
        printf("child process [%d, %d]\n", gval, lval);
    else
        printf("parent process [%d, %d]\n", gval, lval);
    return 0;
}
