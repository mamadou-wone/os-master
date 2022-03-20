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

void handler(int signal_number)
{
    switch (signal_number)
    {
    case SIGUSR1:
        printf("\nReception du signal SIGUSR1 🔥 n° = %d\n", signal_number);
        break;
    case SIGUSR2:
        printf("\nReception du signal SIGUSR2 🦫 n° = %d\n", signal_number);
        break;
    }
}

int main(int argc, char const *argv[])
{
    printf("En attente d'un signal 🌜 et mon PID est %d\n", getpid());
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    pause();
    while (1)
    {
        printf("🌭 🍔 🍟 ");
        sleep(1);
        fflush(stdout);
    }

    return 0;
}
