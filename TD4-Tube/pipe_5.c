#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void grandson(int write_gson[2], int read_tube_fgs[2], int write_tube_fgs[2], int read_gson[2])
{
    int tmp;
    if (close(write_gson[1]) == -1 || close(write_tube_fgs[1]) == -1)
    {
        perror("GrandSon: Error while closing pipe on writting");
        exit(EXIT_FAILURE);
    }

    if(close(read_tube_fgs[0]) == -1 || close(read_gson[0]) == -1)
    {
        perror("GrandSon: Error while closing pipe on reading");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= 5; i++)
    {
        if (read(write_gson[0], &tmp, sizeof(int)) == -1)
        {
            perror("GrandSon: Error while reading from pipe");
            exit(EXIT_FAILURE);
        }
        printf("\nGrandSon[%d]: Received from my Father[%d] -->[%d]\n", getpid(), getppid(), tmp);
        sleep(1);
    }

    for (int i = 1; i <= 5; i++)
    {
        int j = i * 2;
        if(write(read_tube_fgs[1], &j, sizeof(int)) == -1)
        {
            perror("GrandSon: Error while writing to pipe");
            exit(EXIT_FAILURE);
        }
        printf("\nGrandSon[%d]: Sent to my Grand-Father -->[%d]\n", getpid(), j);
        sleep(1);
        if(read(write_tube_fgs[0], &tmp, sizeof(int)) == -1)
        {
            perror("GrandSon: Error while reading from pipe");
            exit(EXIT_FAILURE);
        }
        printf("\nGrandSon[%d]: Received from my Grand-Father -->[%d]\n", getpid(), tmp);
        sleep(1);
        j = tmp - 1;
        if(write(read_gson[1], &j, sizeof(int)) == -1)
        {
            perror("GrandSon: Error while writing to pipe");
            exit(EXIT_FAILURE);
        }
        printf("\nGrandSon[%d]: Sent to my Father[%d] -->[%d]\n", getpid(), getppid(), j);
        sleep(1);
    }
    
    if (close(write_gson[0]) == -1 || close(write_tube_fgs[0]) == -1)
    {
        perror("GrandSon: Error while closing pipe on reading");
        exit(EXIT_FAILURE);
    }
    
    if(close(read_tube_fgs[1]) == -1 || close(read_gson[1]) == -1)
    {
        perror("GrandSon: Error while closing pipe on writting");
        exit(EXIT_FAILURE);
    }
    
    printf("GrandSon[%d]: End of the program\n", getpid());
    exit(EXIT_SUCCESS);
}

void son(int write_tube[2], int read_tube_fgs[2], int write_tube_fgs[2], int read_tube[2])
{
    int tmp, write_gson[2], read_gson[2];
    pid_t pid;

    if (pipe(write_gson) == -1 || pipe(read_gson) == -1)
    {
        perror("Son: Error while creating pipe\n");
        exit(EXIT_FAILURE);
    }

    if((pid = fork()) == -1){
        perror("Son: Error while forking\n");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0){
        grandson(write_gson, read_tube_fgs, write_tube_fgs, read_gson);
    }

    if(close(write_gson[0]) == -1 || close(read_tube[0]) == -1){
        perror("Son: Error while closing pipe on reading\n");
        exit(EXIT_FAILURE);
    }

    if (close(write_tube[1]) == -1 || close(read_gson[1]) == -1)
    {
        perror("Son: Error while closing pipe on writting");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= 5; i++)
    {
        if (read(write_tube[0], &tmp, sizeof(int)) == -1)
        {
            perror("Son: Error while reading from pipe");
            exit(EXIT_FAILURE);
        }
        printf("Son[%d]: Received from my Father[%d] -->[%d]\n", getpid(), getppid(), tmp);
        sleep(1);
    }

    for (int i = 1; i <= 5; i++)
    {
        int j = i + 1;
        if (write(write_gson[1], &j, sizeof(int)) == -1)
        {
            perror("Son: Error while writting to pipe");
            exit(EXIT_FAILURE);
        }
        printf("Son[%d]: Sending to  GrandSon[%d] -->[%d]\n", getpid(), pid, j);
        sleep(1);
    }

    for (int i = 1; i <= 5; i++)
    {
        if (read(read_gson[0], &tmp, sizeof(int)) == -1)
        {
            perror("Son: Error while reading from pipe");
            exit(EXIT_FAILURE);
        }
        printf("Son[%d]: Received from GrandSon[%d] -->[%d]\n", getpid(), pid, tmp);
        sleep(1);
        int j = tmp - 1;
        if(write(read_tube[1], &j, sizeof(int)) == -1)
        {
            perror("Son: Error while writing to pipe");
            exit(EXIT_FAILURE);
        }
        printf("Son[%d]: Sending to my Father[%d] -->[%d]\n", getpid(), getppid(), j);
        sleep(1);
    }
    

    if(close(write_gson[1]) == -1 || close(read_tube[1]) == -1){
        perror("Son: Error while closing pipe on writting\n");
        exit(EXIT_FAILURE);
    }

    if (close(write_tube[0]) == -1 || close(read_gson[0]) == -1)
    {
        perror("Son: Error while closing pipe on reading");
        exit(EXIT_FAILURE);
    }
    if(waitpid(pid, NULL, 0) == -1)
    {
        perror("Son: Error while waiting for the child process");
        exit(EXIT_FAILURE);
    }
    printf("Son[%d]: End of the program\n", getpid());
    exit(EXIT_SUCCESS);
}

void father()
{
    int write_tube[2], read_tube[2], read_tube_fgs[2], write_tube_fgs[2], tmp;
    pid_t pid;

    if (pipe(write_tube) == -1 || pipe(read_tube_fgs) == -1 || pipe(write_tube_fgs) == -1 || pipe(read_tube) == -1)
    {
        perror("Erreur while wreating the tube ! \n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Error during son creation! \n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        son(write_tube, read_tube_fgs, write_tube_fgs, read_tube);
    }

    if (close(write_tube[0]) == -1 || close(write_tube_fgs[0]) == -1)
    {
        perror("Error while closing pipe on reading ! \n");
        exit(EXIT_FAILURE);
    }

    if(close(read_tube[1]) == -1 || close(read_tube_fgs[1]) == -1){
        perror("Father: Error while closing pipe on writting ! \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i <= 5; i++)
    {
        if (write(write_tube[1], &i, sizeof(pid)) == -1)
        {
            perror("Error while writing on the pipe ! \n");
            exit(EXIT_FAILURE);
        }
        printf("Father[%d]: integer sent to son[%d] --> [%d]\n", getpid(), pid, i);
        sleep(1);
    }

    for (int i = 1; i <= 5; i++)
    {
        if(read(read_tube_fgs[0], &tmp, sizeof(int)) == -1){
            perror("Error while reading from the pipe ! \n");
            exit(EXIT_FAILURE);
        }
        printf("\nFather[%d]: Received from GrandSon --> [%d]\n", getpid(), tmp);
        sleep(1);
        int j = tmp - 1;
        if (write(write_tube_fgs[1], &j, sizeof(int)) == -1)
        {
            perror("Error while writing on the pipe ! \n");
            exit(EXIT_FAILURE);
        }
        printf("Father[%d]: send to my GrandSon -->[%d] ", getpid(), j);
        sleep(1);

        if(read(read_tube[0], &tmp, sizeof(int)) == -1){
            perror("Error while reading from the pipe ! \n");
            exit(EXIT_FAILURE);
        }
        printf("\nFather[%d]: Received from son[%d] --> [%d]\n", getpid(), pid,  tmp);
        sleep(1);
    }

    if (close(write_tube[1]) == -1 || close(write_tube_fgs[1]) == -1)
    {
        perror("Error while closing pipe on writing ! \n");
        exit(EXIT_FAILURE);
    }

    if(close(read_tube_fgs[0]) == -1 || close(read_tube[0]) == -1){
        perror("Error while closing pipe on reading ! \n");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("Error while waiting for son ! \n");
        exit(EXIT_FAILURE);
    }

    printf("Father[%d]: finished\n", getpid());
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    father();

    return 0;
}
