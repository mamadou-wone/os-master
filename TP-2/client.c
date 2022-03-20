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
#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        int pid = atoi(argv[1]);
        if (pid <= 0)
        {
            printf("Le PID doit être positif 🥸 \n");
            exit(0);
        }
        else
        {
            printf("Mon PID est ----> %d\n", getpid());
            printf("*********************************\n");
            printf("Envoie du signal SIUSR1 🔥 au programme de PID [%d]\n", pid);
            sleep(2);
            kill(pid, SIGUSR1);
            sleep(2);
            printf("Envoie du signal SIUSR2 🦫 au programme de PID [%d]\n", pid);
            kill(pid, SIGUSR2);
            printf("Je vais tuer maintenant le processus %d 🚬 ⚰️\n", pid);
            sleep(5);
            kill(pid, SIGKILL);
        }
    }

    return 0;
}
