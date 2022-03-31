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
        sleep(5);
        kill(getppid(), SIGUSR2);
        // exit(EXIT_SUCCESS);
        break;
    case SIGUSR2:
        printf("Processus de pip[%d] recoit le signal SIGUSR2[%d] \n", getpid(), sig_number);
        // exit(EXIT_SUCCESS);
        break;
    }
}

void handler_f(int sig_number)
{
    switch (sig_number)
    {
    case SIGUSR1:
        printf("Processus de pip[%d] recoit le signal SIGUSR1[%d] \n", getpid(), sig_number);
        sleep(5);
        kill(getppid(), SIGUSR1);
        break;
    }
}



void g_son(int tube_fp[2], int tube_fp_r[2])
{
    int i, tmp, pf;
    signal(SIGUSR1, handler_f);
    printf("Petit-Fils de pid[%d] et mon pere est [%d]\n", getpid(), getppid());
    if (close(tube_fp_r[0]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_fp[1]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    sleep(3);
    printf("FIls[%d]: Attente de reception du signal SIGUSR1\n", getpid());
    
    
    kill(getppid(), SIGUSR1);

    for (i = 1; i <= 5; i++)
    {
        if (read(tube_fp[0], &tmp, sizeof(int)) == -1)
        {
            perror("Petit-Fils: Erreur lors de la lecture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("Petit-fils[%d] Entier reçu de mon pere[%d] --> [%d]\n", getpid(), getppid(), tmp);
        sleep(1);
        int j = tmp - 1;
        if (write(tube_fp_r[1], &j, sizeof(int)) == -1)
        {
            perror("Petit-Fils: Erreur lors de l'ecriture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("Petit-fils[%d] Entier envoyé à mon pere[%d] --> [%d]\n", getpid(), getppid(), j);
        sleep(1);
    }

    if (close(tube_fp_r[1]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_fp[0]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }
    printf("Petit-Fils[%d] terminé\n", getpid());
    while (1)
    {
        printf("*");
        fflush(stdout);
        sleep(1);
    }
}

void son(int tube[2], int tube_r[2])
{
    pid_t pid, pid_m;
    int i, tpm, tube_fp[2], tube_fp_r[2], pf, status;
    signal(SIGUSR1, handler);
    printf("Fils de pid[%d] et mon pere est [%d]\n", getpid(), getppid());
    // sleep(5);
    // kill(getppid(), SIGUSR2);
    sleep(2);
    if (pipe(tube_fp) == -1 || pipe(tube_fp_r) == -1)
    {
        perror("Fils: Erreur lors de la creation du tube\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Fils: Erreur lors de la création du fils\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_r[0]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (tube_fp[0] == -1)
    {
        perror("Fils: erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        g_son(tube_fp, tube_fp_r);

    if (close(tube_fp_r[1]) == -1)
    {
        perror("Fils: erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[1]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    pause();

    for (i = 1; i <= 5; i++)
    {
        if (read(tube[0], &tpm, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de la lecture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("fils[%d] Entier reçu de mon pere[%d] --> [%d]\n", getpid(), getppid(), tpm);
        sleep(1);
        int j = i * 2;
        if (write(tube_fp[1], &j, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de l'ecriture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("fils[%d] Entier envoyé à mon fils[%d] --> [%d]\n\n\n\n", getpid(), pid, j);
        sleep(1);

        if (read(tube_fp_r[0], &pf, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de la lecture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("fils[%d] Entier reçu de mon fils[%d] --> [%d]\n", getpid(), pid, pf);
        sleep(1);
        j--;
        if (write(tube_r[1], &j, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de l'ecriture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("fils[%d] Entier envoyé à mon pere[%d] --> [%d]\n", getpid(), getppid(), j);
        sleep(1);
    }

    if (tube_fp[1] == -1 || close(tube_r[1]) == -1)
    {
        perror("Fils: erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[0]) == -1 || close(tube_fp_r[0]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    printf("Fils[%d] attente de 3s pour kill mon fils\n", getpid());
    sleep(3);
    kill(pid, SIGKILL);
    // if (waitpid(pid, NULL, 0) == -1)
    // {
    //     perror("Fils: Erreur lors de l'attente de mon fils\n");
    //     exit(EXIT_FAILURE);
    // }
    if ((pid_m = wait(&status)) == -1)
    {
        perror("Fils: Erreur lors de l'attente de mon fils\n");
        exit(EXIT_FAILURE);
    }
    if (WIFSIGNALED(status))
    {
        printf("Fils[%d] mon fils[%d] est mort le un signal[%d]\n", getpid(), pid_m, WTERMSIG(status));
    }
    printf("Fils[%d] attente de 5s pour me suicider\n", getpid());
    sleep(5);
    kill(getpid(), SIGKILL);
}

void father()
{
    pid_t pid, pid_m;
    int tube[2], i, tube_r[2], tmp, status;
    signal(SIGUSR2, handler);
    if (pipe(tube) == -1 || pipe(tube_r) == -1)
    {
        perror("Pere: erreur lors de la création du tube \n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        printf("Pere: erreur lors de la création du fils\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        son(tube, tube_r);

    if (close(tube_r[1]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[0]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    pause();
    for (i = 1; i <= 5; i++)
    {
        if (write(tube[1], &i, sizeof(int)) == -1)
        {
            perror("Pere erreur lors de l'ecriture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("Pere[%d]: entier envoye a mon fils[%d] --> [%d]\n", getpid(), pid, i);
        sleep(1);

        if (read(tube_r[0], &tmp, sizeof(int)) == -1)
        {
            perror("Pere erreur lors de la lecture d'un entier \n");
            exit(EXIT_FAILURE);
        }
        printf("Pere[%d]: entier recu de mon fils[%d] --> [%d]\n", getpid(), pid, tmp);
        sleep(1);
    }

    if (close(tube[1]) == -1)
    {
        perror("Pere; Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    // if (waitpid(pid, NULL, 0) == -1)
    // {
    //     perror("Pere: erreur lors de l'attente de mon fils \n");
    //     exit(EXIT_FAILURE);
    // }

    printf("Pere[%d] termine \n", getpid());
    if ((pid_m = wait(&status)) == -1)
    {
        perror("Pere: Erreur lors de l'attente de mon fils\n");
        exit(EXIT_FAILURE);
    }
    if (WIFSIGNALED(status))
    {
        printf("Pere[%d] mon fils[%d] est mort et le un signal[%d] est responsable\n", getpid(), pid_m, WTERMSIG(status));
    }
    kill(getpid(), SIGKILL);
}

int main(int argc, char const *argv[])
{
    father();

    return EXIT_SUCCESS;
}
