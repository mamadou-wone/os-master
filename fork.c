#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("avant fork \n");
    // fflush(stdout);
    fork();
    printf("apres fork \n");
    fork();
    printf("apres fork2 \n");
    return 0;
}
