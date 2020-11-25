#include "header.h"

void piping(char *text, int i, int size)
{
    //    printf("%i : %s", i, text);
    if (i & 1)
    {
        //  int ret = pipe(mypipe1);
        if (pipe(mypipe1) == -1)
        {
            perror("pipe");
            return;
        }
    }
    else
    {
        int ret = pipe(mypipe2);
        if (ret == -1)
        {
            perror("pipe");
            return;
        }
    }
    int pid = fork();

    if (pid == -1)
    {
        perror("Error in child process\n");
        return;
    }
    if (!pid)
    {
        if (i == 0)
        {
            dup2(mypipe2[1], 1);
        }
        else if (size - 1 == i)
        {
            if ((size - 1) & 1)
            {
                dup2(mypipe2[0], 0);
            }
            else
            {
                dup2(mypipe1[0], 0);
            }
        }
        else
        {
            if (i & 1)
            {
                dup2(mypipe2[0], 0);
                dup2(mypipe1[1], 1);
            }
            else
            {
                dup2(mypipe1[0], 0);
                dup2(mypipe2[1], 1);
            }
        }

        strcpy(cmdline, text);
        redirection();

        exit(0);
    }
    wait(NULL);
    if (i == 0)
    {
        close(mypipe2[1]);
    }
    else if (i == size - 1)
    {
        if ((size - 1) & 1) 
        {
            close(mypipe2[0]);
        }
        else 
        {
            close(mypipe1[0]);
        }
    }
    else 
    {
        if (i & 1)
        {
            close(mypipe2[0]);
            close(mypipe1[1]);
        }
        else
        {
            close(mypipe1[0]);
            close(mypipe2[1]);
        }
    }
}