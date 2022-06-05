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

int main(int argc, char **argv)
{
    int fd_write;
    int output = mkfifo(argv[1], S_IRUSR | S_IWUSR);
    printf("errno: %d\n ", errno);
    switch (errno)
    {
    case EPERM:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOENT:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ESRCH:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EINTR:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EIO:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENXIO:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case E2BIG:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOEXEC:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EBADF:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ECHILD:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EAGAIN:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOMEM:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EACCES:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EFAULT:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOTBLK:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EBUSY:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EEXIST:
    {
        perror("Oups mkfifo 😵!");
        exit(1);
    }
    break;
    case EXDEV:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENODEV:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOTDIR:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EISDIR:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EINVAL:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENFILE:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EMFILE:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOTTY:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ETXTBSY:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EFBIG:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ENOSPC:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ESPIPE:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EROFS:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EMLINK:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EPIPE:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case EDOM:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    case ERANGE:
        perror("Oups mkfifo 😵!");
        exit(1);
        break;
    default:
        break;
    }

    // if (mkfifo(argv[1], S_IRUSR | S_IWUSR) == EEXIST)
    // {
    //     perror("mkfifo");
    //     exit(1);
    // }
    // else
    // {
    //     if ((fd_write = open(argv[1], O_WRONLY)) == -1)
    //     {
    //         perror("open");
    //         exit(1);
    //     }
    // }
    if ((fd_write = open(argv[1], O_WRONLY)) == -1)
    {
        perror("open");
        exit(1);
    }
    int i;
    if ((n = write(fd_write, argv[2], 0)) == -1)
    {
        perror("write");
        exit(1);
    }
    close(fd_write);
    return EXIT_SUCCESS;
}