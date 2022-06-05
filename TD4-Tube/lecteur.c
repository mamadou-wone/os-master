#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#define S_BUF 100

int n;
char buffer[S_BUF];

int main(int argc, char const *argv[])
{
    int fd_read = open(argv[1], O_RDONLY);
    switch (errno)
    {
    case EACCES:
        perror("Oups open 😵!");
        exit(1);
        break;
    case EFAULT:
        perror("Error 😵!");
        exit(1);
        break;
    case ENOENT:
        perror("Error 😵!");
        exit(1);
        break;
    default:
        break;
    }

    // if ((fd_read = open(argv[1], O_RDONLY)) == -1)
    // {
    //     perror("Erreur open");
    //     exit(1);
    // }
    if ((n = read(fd_read, buffer, S_BUF)) == -1)
    {
        perror("Erreur lecture");
        exit(1);
    }
    else
    {
        buffer[n] = '\0';
        printf("%s\n", buffer);
    }

    close(fd_read);
    return EXIT_SUCCESS;
}
