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

void treatment(int sig)
{
    if (sig == SIGALRM)
    {
        printf("\nReception signal SIGALARM = [%d📢] dans le processus de pid %d\n", sig, getpid());
        printf("Fin du programme \n");
        kill(getpid(), SIGINT);
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGALRM, treatment);
    printf("On attends 5 seconde et on envoie le signal SIGALARM💡\n");
    alarm(5);
    printf("En attente d'un signal 🛀\n");
    while (1)
    {
        printf("🐬");
        sleep(1);
        fflush(stdout);
    }

    return 0;
}
