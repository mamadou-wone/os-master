#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void p_fils(int tube[2], int tube_gf[2])
{
    int i, tmp;

    if (close(tube[1]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_gf[0]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= 5; i++)
    {
        if (read(tube[0], &tmp, sizeof(int)) == -1)
        {
            perror("Petit-Fils: Erreur lors de la lecture du tube \n");
            exit(EXIT_FAILURE);
        }
        printf("Petit-fils entier recu ---> %d\n", tmp);
        sleep(1);
        tmp = tmp * 3;
        if (write(tube_gf[1], &tmp, sizeof(int)) == -1)
        {
            perror("Petit-Fils: Erreur lors de l'ecriture du tube \n");
            exit(EXIT_FAILURE);
        }
        printf("Petit-fils entier envoye a mon grand-pere---> %d\n", tmp);
        sleep(1);
    }

    if (close(tube_gf[1]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[0]) == -1)
    {
        perror("Petit-Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    printf("Petit-Fils: Fin du programme\n");

    exit(EXIT_SUCCESS);
}

void fils(int tube[2], int tube_gf[2])
{
    pid_t pid;
    int i, tmp, tube_pf[2];

    if (pipe(tube_pf) == -1)
    {
        perror("Fils: Erreur lors de la creation du tube\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Fils: Erreur lors de la creation du petit-fils\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        p_fils(tube_pf, tube_gf);
    }

    if (close(tube_pf[0]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[1]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= 5; i++)
    {
        if (read(tube[0], &tmp, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de la lecture du tube \n");
            exit(EXIT_FAILURE);
        }
        printf("Fils entier recu ---> %d\n", tmp);
        sleep(1);
        tmp = i * 2;
        if (write(tube_pf[1], &tmp, sizeof(int)) == -1)
        {
            perror("Fils: Erreur lors de l'ecriture du tube \n");
            exit(EXIT_FAILURE);
        }
        printf("Fils entier envoyé vers mon fils---> %d\n", tmp);
        sleep(1);
    }

    if (close(tube_pf[1]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube[0]) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("Fils: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    printf("Fils: Fin du programme\n");

    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    int tube[2], i, tmp, tube_gf[2];
    pid_t pid;

    if (pipe(tube) == -1 || pipe(tube_gf) == -1)
    {
        perror("Pere: Erreur lors de la creation du tube\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1)
    {
        perror("Pere: Erreur lors de la creation du fils\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
        fils(tube, tube_gf);

    if (close(tube[0]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_gf[1]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= 5; i++)
    {
        if (write(tube[1], &i, sizeof(int)) == -1)
        {
            perror("Pere: Erreur lors de l'ecriture du tube en ecriture\n");
            exit(EXIT_FAILURE);
        }
        printf("Pere entier envoyé---> %d\n", i);
        sleep(1);
        if (read(tube_gf[0], &tmp, sizeof(int)) == -1)
        {
            perror("Pere: Erreur lors de la lecture du tube \n");
            exit(EXIT_FAILURE);
        }
        printf("Pere recu de mon petit-fils---> %d\n", tmp);
        sleep(1);
    }

    if (close(tube[1]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en ecriture\n");
        exit(EXIT_FAILURE);
    }

    if (close(tube_gf[0]) == -1)
    {
        perror("Pere: Erreur lors de la fermeture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("Pere: Erreur lors de la lecture du tube en lecture\n");
        exit(EXIT_FAILURE);
    }
    printf("Pere: Fin du programme\n");
    return EXIT_SUCCESS;
}
