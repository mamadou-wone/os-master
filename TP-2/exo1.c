//   ___       __   ________  ________   _______
//  |\  \     |\  \|\   __  \|\   ___  \|\  ___ \     
//  \ \  \    \ \  \ \  \|\  \ \  \\ \  \ \   __/|
//   \ \  \  __\ \  \ \  \\\  \ \  \\ \  \ \  \_|/__
//    \ \  \|\__\_\  \ \  \\\  \ \  \\ \  \ \  \_|\ \ 
//     \ \____________\ \_______\ \__\\ \__\ \_______\
//      \|____________|\|_______|\|__| \|__|\|_______|
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define DELAI 1

void traitement(int numero_signal)
{
    printf("\n Reception du Signal %d => ", numero_signal);
    switch (numero_signal)
    {
    case SIGTSTP:
        printf("Je m'endors....\n");
        kill(getpid(), SIGSTOP);
        printf("Je me réveille !\n");
        signal(SIGTSTP, traitement);
        break;
    case SIGINT:
        while (1)
        {
            printf("-_-");
        }

    case SIGTERM:
        printf("Fin du programme.\n");
        exit(EXIT_SUCCESS);
        break;
    case SIGUSR1:
        printf("Signal(SIGUSR1).\n");
        kill(getpid(), SIGUSR2);
        break;
    case SIGUSR2:
        printf("Signal(SIGUSR2).\n");
        kill(getpid(), SIGUSR1);
        break;
    case SIGKILL:
        printf("Signal(SIGKILL): Je refuse de mourrir !.\n");

        break;
    }
}

int main(void)
{
    printf("Mon PID est %d => ", getpid());
    signal(SIGTSTP, traitement);
    signal(SIGINT, traitement);
    signal(SIGTERM, traitement);
    signal(SIGUSR1, traitement);
    signal(SIGUSR2, traitement);
    signal(SIGKILL, traitement); // SIGKILL

    printf("Attente de reception d'un signal \n");

    while (1)
    {
        sleep(DELAI);
        printf("🤡🦍🦧🎃");
        fflush(stdout);
    }
    printf("fin\n");
    exit(EXIT_SUCCESS);
}
