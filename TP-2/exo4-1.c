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
            printf("L'argument passé doit être positif 🥸  \n");
            exit(0);
        }
        else
        {
            char response[1];
            printf("Voulez vous tuer le procesus %d  🪓🔪  y/n ?\n", pid);
            scanf("%s", response);
            if (strcmp(response, "y") == 0)
            {

                kill(pid, SIGKILL);
                printf("Fin du processus 😮‍💨 \n");
                exit(0);
            }
        }
    }

    return 0;
}
