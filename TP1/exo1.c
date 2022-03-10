#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// int main(int argc, char const *argv[])
// {
//     int p1, p2, p3;
//     p1 = fork();
//     p2 = getpid();
//     p3 = getppid();
//     printf("p1=%d - p2=%d - p3=%d\n", p1, p2, p3);
//     return 0;
// }


// #define N 10
// int main(int argc, char const *argv[])
// {
//     int i = 1;
//     while (fork() == 0 && i <= N) i++;
//     printf("%d\n",i);
//     return 0;
// }


// int main(int argc, char const *argv[])
// {
//     int pid[3], i;
//     for (i = 0; i < 3; i++)
//     {
//         pid[i] = fork();
//     }
//     printf("%d %d %d", pid[0], pid[1], pid[2]);
//     return 0;
// }


int main(int argc, char const *argv[])
{
    pid_t valeur, valeur1;
    printf("Affichage 1 --> Processus pere [%d]: mon pere à moi est [%d] \n", getpid(), getppid());
    valeur = fork();
    printf("Affichage 2 --> retour fork [%d] - Processus fils [%d]; mon père est [%d] \n", valeur, getpid(), getppid());
    valeur1 = fork();
    printf("Affichage 3 --> retour fork [%d] - Processus fils [%d]; mon père est [%d] \n", valeur1, getpid(), getppid());
    return 0;
}
