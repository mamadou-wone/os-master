#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t id = 0;
    printf("Processus Pere [%d]", getgid());
    if (fork() == 0)
    {
        printf("Processus Enfant [%d]: mon pere est %d\n", getpid(), getppid());
        exit(0);
    }
    id = wait(NULL);
    printf("Processus pere [%d]: mon Enfant [%d] est mort\n", getgid(), id);    
    return 0;
}
