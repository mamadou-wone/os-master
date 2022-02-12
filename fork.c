#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("avant fork\n");
    fork();
    printf("apres fork\n");
    return 0;
}