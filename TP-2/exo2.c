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
#include <sys/wait.h>

void treatment(int signal_number)
{
    if (signal_number == SIGUSR1)
    {
        printf("Le signal SIGUSR1 %d a été reçu je vais me m'arreter 😮‍💨🚬 \n", signal_number);
        exit(EXIT_SUCCESS);
    }
}

int main(void)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Je suis le fils mon pid est 👶 %d\n", getpid());
        signal(SIGUSR1, treatment);
        pause();
    }
    else
    {
        sleep(1);
        printf("Je suis le père mon pid est 🧔 %d \n", getpid());
        sleep(2);
        printf("Je vais tuer dans 5 secondes mon fils  avec le pid %d 🔪🪓 \n", pid);
        sleep(5);
        kill(pid, SIGUSR1);
    }
}
