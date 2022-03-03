#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t status;
    status = fork();
    switch (status)
    {
    case -1: perror("erreur de création"); return -1;
    case 0:
    switch (fork())
    {
    case -1: perror("erreur de création intermédiare"); return 1;
        break;
    case 0:
    printf("Precessus [%d], Mon père : [%d] \n", getpid(), getppid());
    sleep(5);
    printf("Precessus [%d], Mon père : [%d] \n", getpid(), getppid());
    default:
        break;
        return 0;
    }
    
    default:
        break;
    }
    return 0;
}
