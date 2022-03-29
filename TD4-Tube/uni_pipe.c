#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void fils(int tube[2])
{
    printf("Je suis le fils de pid[%d] et mon pere est [%d]\n", getpid(), getppid());
    int tube_pf[2];
    pid_t pid;

    int i, tmp, fl;

    if (close(tube[1]) == -1)
    {
        perror("Fils : erreur lors de la fermeture du tube en ecriture");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++)
    {
        if (read(tube[0], &tmp, sizeof(int)) == -1)
        {
            perror("Fils : erreur lors de la lecture d'un entier depuis le tube");
            exit(EXIT_FAILURE);
        }
        printf("Fils: entier lu : %d\n", tmp);
        sleep(1);
        fl = i * 2;
        if (write(tube_pf[1], &fl, sizeof(int)) == -1)
        {
            perror("Fils : erreur lors de l'ecriture d'un entier depuis le tube");
            exit(EXIT_FAILURE);
        }
        printf("Fils: entier envoye à mon papa : %d\n", fl);
    }

    if (close(tube[0]) == -1 || close(tube_pf[1]) == -1)
    {
        perror("Fils : erreur lors de la fermeture du tube en lecture");
        exit(EXIT_FAILURE);
    }
    printf("Fils termine. \n");

    exit(EXIT_SUCCESS);

    // if (pid == 0)
    // {
    //     int pf;
    //     if (close(tube_pf[1]) == -1)
    //     {
    //         perror("Fils: Erreur lors de la fermeture du tube en ecriture \n");
    //         exit(EXIT_FAILURE);
    //     }
    //     for (int i = 0; i < 5; i++)
    //     {
    //         if (read(tube_pf[0], &pf, sizeof(int)) == -1)
    //         {
    //             perror("Fils: Erreur lors de la lecture d'un entier \n");
    //         }
    //         printf("Petit-Fils[%d]: entier lu de mon père [%d]: %d\n", getpid(), getppid(), pf);
    //         sleep(1);
    //     }
    //     printf("Petit-Fils[%d] ---> Pere[%d] termine. \n", getpid(), getppid());
    // }
}

int main(int argc, char const *argv[])
{
    printf("Processus de pid ---> %d\n", getpid());
    pid_t pid;
    int tube[2], tube_fp[2], i, lp;

    if (pipe(tube) == -1)
    {
        perror("Pere erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Pere erreur lors de la création du fils");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        fils(tube);

    if (close(tube[0]) == -1)
    {
        perror("Pere : erreur lors de la fermeture du tube en lecture");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 5; i++)
    {
        if (write(tube[1], &i, sizeof(int)) == -1)
        {
            perror("Pere : erreur lors de l'ecriture d'un entier dans le tube'");
            exit(EXIT_FAILURE);
        }
        printf("Pere entier envoye: %d\n", i);
        sleep(1);
    }

    if (close(tube[1]) == -1)
    {
        perror("Pere : erreur lors de la fermeture du tube en ecriture");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("Pere: erreur lors de l'attente de la fin du fils");
        exit(EXIT_FAILURE);
    }

    printf("Pere: fils termine.\n");

    return EXIT_SUCCESS;
}
