#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    printf("PID === %d\n", getpid());
    while (1)
    {
        printf("🐣");
        sleep(1);
        fflush(stdout);
    }

    return 0;
}
