#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
void fils(int tube[2], int tube_pf[2])
{
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
        printf("Fils: entier envoye à mon papa : %d\n", tmp);
    }

    if (close(tube[0]) == -1 || close(tube_pf[1]) == -1)
    {
        perror("Fils : erreur lors de la fermeture du tube en lecture");
        exit(EXIT_FAILURE);
    }
    printf("Fils termine. \n");

    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    int tube[2], tube_fp[2], i, lp;

    if (pipe(tube) == -1 || pipe(tube_fp) == -1)
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
        fils(tube, tube_fp);

    if (close(tube[0]) == -1 || close(tube_fp[1]) == -1)
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
        if (read(tube_fp[0], &lp, sizeof(int)) == -1)
        {
            perror("Pere : erreur lors de la lecture d'un entier dans le tube'");
            exit(EXIT_FAILURE);
        }
        printf("Pere: entier lu : %d\n", lp);
        sleep(1);
    }

    if (close(tube[1]) == -1 || close(tube_fp[0]) == -1)
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
