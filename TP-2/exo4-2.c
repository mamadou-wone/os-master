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

int check_number(int signal)
{
    int signals[] = {2, 3, 10, 12, 15, 19};
    for (int i = 0; i < sizeof(signals); i++)
    {
        if (signal == signals[i])
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc == 3)
    {
        int pid = atoi(argv[1]);
        int signal_number = atoi(argv[2]);
        if (pid <= 0 || !check_number(signal_number))
        {
            printf("Vérifier les arguments passés 🥸 \n");
            exit(0);
        }
        else
        {
            char response[1];
            printf("Voulez vous tuer le procesus %d  🪓🔪 y/n ?\n", pid);
            scanf("%s", response);
            if (strcmp(response, "y") == 0)
            {
                kill(pid, signal_number);
                printf("Fin du processus 😮‍💨 \n");
                exit(0);
            }
        }
    }

    return 0;
}
