#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t id;
    id = fork();
    printf(" id = %d , pid = %d , ppid = %d \n ", id, getpid(), getppid());
    return 0;
}
