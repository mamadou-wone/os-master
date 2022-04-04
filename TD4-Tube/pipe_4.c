#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

void handler(int sig_number)
{
    switch (sig_number)
    {
    case SIGUSR1:
        printf("Processus de pip[%d] recoit le signal SIGUSR1[%d] \n", getpid(), sig_number);
        kill(getppid(), SIGUSR2);
        // exit(EXIT_SUCCESS);
        break;
    case SIGUSR2:
        printf("Processus de pip[%d] recoit le signal SIGUSR2[%d] \n", getpid(), sig_number);
        // exit(EXIT_SUCCESS);
        break;
    }
}

void fils()
{
    pid_t pid;

    if ((pid = fork()) == -1)
    {
        perror("Fils: Erreur lors de la création du petit-fils\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("Petit-FIls de pip[%d] et mon pere est [%d]\n", getpid(), getppid());
        printf("Petit-FIls: je vais avertir mon pere de ma creation\n");
        sleep(5);
        kill(getppid(), SIGUSR1);
    }

    signal(SIGUSR1, handler);
    pause();
    printf("Fils: Fin du programme\n");
    kill(getpid(), SIGKILL);
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    printf("Pere[%d]\n", getpid());
    if ((pid = fork()) == -1)
    {
        perror("Pere:Erreur lors de la création du processus fils\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        fils();
    }
    signal(SIGUSR2, handler);
    pause();
    kill(getpid(), SIGKILL);
    printf("Pere fin du programme\n");
    return 0;
}
