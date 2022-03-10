#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

void parler(){
    printf("Mon pid = [%d] et le ppid de mon père est ppid = [%d]\n", getpid(), getppid());
    // sleep(5);
    while (1)
    {
        printf(". ");
        fflush(stdout);
        sleep(1);
    }
    
    // exit(27);
}

int main(int argc, char const *argv[])
{
    
    // if (fork() == 0)
    // {
    //     printf("pid: [%d]", getpid());
    //     exit(0);
    // }
    // t =  wait(NULL);
    // printf("t: %d ", t);
    // pid_t pid;
    // int status;
    // pid = fork();

    pid_t t = fork();
    int status;
    switch (t)
    {
    case -1:
        exit(-1);
        break;
    case 0:
        parler();
    default:
        printf("Pere [%d]: a cree processus [%d]\n ", getpid(), t);
       while (1)
       {
           
       }
       
        // wait(&status);
        // if (WIFEXITED(status))
        //     printf("Le fils termine normalement: status = %d\n", WEXITSTATUS(status));
        // else
        //     printf("fils termine anormalement\n");
        // if (WIFSIGNALED(status))
        //     printf("Le fils termine anormalement: numéro du signal = %d\n", WTERMSIG(status));
        // else
        //     printf("fils termine normalement\n");

        break;
    }
    return 0;
}
