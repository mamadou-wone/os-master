#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    pid_t status;
    status = fork();
    switch (status)
    {
    case -1:
        perror(" C r e at i o n de p rocessus ");
        return -1;
    case 0:
        printf("[%d ] Je v ien s de n a i t r e \ n ", getpid());
        printf("[%d ] Mon pere %d \ n ", getpid(), getppid());
        break;
    default:
        printf("[%d ] J \ ’ a i engendre \ n ", getpid());
        printf("[%d ] Mon f i l s e st %d \ n ", getpid(), status);
    }
    printf("[%d ] Je te rmine \ n ", getpid());
    exit(EXIT_SUCCESS);
}