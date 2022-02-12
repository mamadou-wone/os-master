#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id;
    id = fork();
    printf(" i d = %d , p i d = %d , ppid = %d \ n ", id, getpid(), getppid());
    return 0;
}
