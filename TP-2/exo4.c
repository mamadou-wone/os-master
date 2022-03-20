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

#define password "amir"

void treatment(int sig)
{
    switch (sig)
    {
    case SIGINT:
        printf("\nReception signal SIGINT = [%d ⛔️] dans le processus de pid %d\n", sig, getpid());
        char user_passwd[6];
        printf("Enter you password 🔐\n");
        scanf("%s", user_passwd);
        if (strcmp(user_passwd, password) == 0)
        {
            printf("Fin du programme 😵‍💫\n");
            signal(SIGINT, SIG_DFL);
            kill(getpid(), SIGINT);
        }
        else
        {
            printf("Le mot de passe ne correspond pas ❌\n");
        }
        break;
    }
}

int main(int argc, char const *argv[])
{
    printf("En attente de signal 🤌 \n");
    signal(SIGINT, treatment);
    while (1)
    {
        printf("🍓");
        sleep(1);
        fflush(stdout);
    }

    return 0;
}
