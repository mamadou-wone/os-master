#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void son(int read_tube[2])
{
    int tmp, i;
    if(close(read_tube[1]) == -1)
    {
        perror("Son: Error closing tube on writte mode");
        exit(1);
    }

    for(i = 0; i < 5; i++)
    {
        if(read(read_tube[0], &tmp, sizeof(int)) == -1)
        {
            perror("Son: Error reading from tube");
            exit(1);
        }
        printf("Son[%d]: receive from my father[%d] %d\n",getpid(), getppid(), tmp);
        sleep(1);
    }

    if(close(read_tube[0]) == -1)
    {
        perror("Son: Error closing tube on read mode");
        exit(1);
    }
    printf("Son[%d]: End\n", getpid());
    exit(EXIT_SUCCESS);
}

void father()
{
    int tube[2], i;
    pid_t pid;

    if (pipe(tube) == -1)
    {
        perror("Father: Father: Error creating pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Father: Error creating child process");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        son(tube);
    }

    if (close(tube[0]) == -1)
    {
        perror("Error while closing pipe on reading ! \n");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < 5; i++)
    {
        if(write(tube[1], &i, sizeof(int)) == -1)
        {
            perror("Father: Error writing to pipe");
            exit(EXIT_FAILURE);
        }
        printf("Father[%d]: send to my son[%d] %d\n", getpid(), pid, i);
        sleep(1);
    }    
    if(close(tube[1]) == -1)
    {
        perror("Father: Error closing pipe on write !");
        exit(EXIT_FAILURE);
    }
    if(waitpid(pid, NULL, 0) == -1)
    {
        perror("Father: Error waiting for child process");
        exit(EXIT_FAILURE);
    }
    printf("Father[%d]: child process %d terminated\n", getpid(), pid);
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    father();
    return 0;
}
