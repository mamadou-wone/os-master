#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int rwrite()
{
    int tube[2];
    char buffer[3];

    if (pipe(tube) == -1)
    {
        perror("Pere erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }
    char *pin = "4128\0";
    printf("Writting PIN to pipe...\n");
    write(tube[1], pin, 5);
    printf("Done. \n");
    printf("Reading PIN from pipe...\n");
    read(tube[0], buffer, 3);
    printf("Done. \n");

    printf("PIN from pipe: %s\n", buffer);
    return EXIT_SUCCESS;
}

int rwfork()
{
    int tube[2];
    char *pin;
    char buffer[5];

    if (pipe(tube) == -1)
    {
        perror("Pere erreur lors de la création du tube");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        pin = "4821\0";
        close(tube[0]);
        write(tube[1], pin, 5);
        printf("Generating PIN in child and sending to parent...\n");
        sleep(2);
        exit(EXIT_SUCCESS);
    }

    if (pid > 0)
    {
        wait(NULL);
        close(tube[1]);
        read(tube[0], buffer, 5);
        close(tube[0]);
        printf("Parent received PIN from child: %s\n", buffer);
    }

    return EXIT_SUCCESS;
}

int main(void)
{
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
        // fils(tube, tube_fp);
        printf("Son\n");

    if (pid > 0)
    {
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
    }
    return EXIT_SUCCESS;
}
