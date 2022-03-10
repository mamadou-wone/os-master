#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

// Create 5 Processus
void createProcessus()
{
    for (int i = 0; i < 5; i++)
    {
        if (fork() == 0)
        {
            printf("Mon numéro est [%d] et mon pid = [%d]\n", i, getpid());
            exit(0);
        }
    }
}

// Display Processus Info
void parler(int i)
{
    printf("Mon numéro est [%d] , mon pid = [%d] et le ppid de mon père est ppid = [%d]\n", i, getpid(), getppid());
    exit(i);
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        int n = atoi(argv[1]);
        if (n <= 0)
        {
            printf("L'argument passé doit être positif :( \n");
            exit(0);
        }
        
        int sonsTable[n];
        pid_t pid = 0;
        int status;
        for (int i = 0; i < n; i++)
        {
            if ((pid = fork() ) == 0)
            {
                parler(i);
            }else{
                sonsTable[i] = pid;
            }
        }
        sleep(5);
        for (int i = 2; i < n; i++)
        {
            printf("Pid du fils [%d] = [%d] \n", i, sonsTable[i]);
        waitpid(sonsTable[i], &status, 0);
        if (WIFEXITED(status))
            printf("Le fils termine normalement: status = %d\n", WEXITSTATUS(status));
        else
            printf("fils termine anormalement\n");
        } 
    }
    else
    {
        printf("Le programme accepte exactement un seul argument !\n");
    }
    
    return 0;
}
