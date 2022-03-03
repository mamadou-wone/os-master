#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int glob = 1;

int main()
{
    int loc = 1;

    switch (fork())
    {
    case -1:
        perror(" Creation de processus ");
        return -1;
    case 0:
        glob++;
        loc++;
        printf("Fils : (%d, %d)\n", glob, loc);
        break;
    default:
        sleep(1);
        printf("Pere : (%d, %d)\n", glob, loc);
    }
    printf("[%d] Je termine\n", getpid());

    return 0;
}