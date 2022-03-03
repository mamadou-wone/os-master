#include <stdio.h>
#include <unistd.h>

// int main(int argc, char const *argv[])
// {
//     printf("wone");
//     execl("/bin/ls", "ls", NULL);
//     printf("Je ne suis pas mort \n");
//     return 0;
// }

int main(int argc, char const *argv[])
{
    if (fork() == 0) execl("/bin/ls", "ls", NULL);
    else
    {
        sleep(2);
        printf("Je ne suis pas mort \n");
    }
    return 0;
}
