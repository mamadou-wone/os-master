#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define POSIX_SOURCE 1


void sig_handler(int sig){
    if(sig == SIGPIPE)
        printf("ecriture dans un tube sans lecture .\n");
}

int main(int argc, char const *argv[])
{
    int tubeDesc[2];
    signal(SIGPIPE, sig_handler);
    if(pipe(tubeDesc) == -1){
        perror("Erreur creation pipe");
        exit(1);
    }
    close(tubeDesc[0]);

    if (write(tubeDesc[1], "x", 1) == -1)
    {
        perror("Erreur de write");
    }
    
    return EXIT_SUCCESS;
}
