#include "header.h"

void setenvv(char *text)
{
    char *args[1000];
    int i = 0;
    for (int k = 0; k < 1000; k++)
    {
        args[k] = "";
    }

    args[i] = strtok(text, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if (i == 0 || i > 2)
    {
        printf("Too few arguments or too much arguments\n");
        return;
    }
    if (i == 1)
    {
        setenv(args[0], "", 1);
        return;
    }
    setenv(args[0], args[1], 1);
}

void unsetenvv(char *text)
{
    char *args[1000];
    int i = 0;
    for (int k = 0; k < 1000; k++)
    {
        args[k] = "";
    }

    args[i] = strtok(text, " ");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
    if (i == 0 || i > 1)
    {
        printf("Too few arguments or too much arguments\n");
        return;
    }

    unsetenv(args[0]);
}

void bg(char *text)
{
    char *token[1000];
    int i = 0;
    token[i] = strtok(text, " ");
    while (token[i] != NULL)
    {
        i++;
        token[i] = strtok(NULL, " ");
    }
    if (i != 1)
    {
        printf("too few arguments or too many arguments\n");
        return;
    }
    int p_no = atoi(token[0]);
    int pid;
    if (p_no > p_cnt || p_no < 0)
    {
        printf("no job exists\n");
        return;
    }
    //  printf("p_no:%d", p_no);
    for (int counter = 1; counter <= p_cnt; counter++)
    {
        if (p_no == counter)
        {
            pid = p_arr[counter].pid;
            break;
        }
    }
    kill(pid, 18);
}

void fg(char *text)
{
    char *token[1000];
    int i = 0;
    token[i] = strtok(text, " ");
    while (token[i] != NULL)
    {
        i++;
        token[i] = strtok(NULL, " ");
    }
    if (i != 1)
    {
        printf("too few arguments or too many arguments\n");
        return;
    }
    int p_no = atoi(token[0]);
    int pid;
    char pid_name[1000];
    if (p_no > p_cnt || p_no < 0)
    {
        printf("no job exists\n");
        return;
    }
    //  printf("p_no:%d", p_no);
    for (int counter = 1; counter <= p_cnt; counter++)
    {
        if (p_no == counter)
        {
            pid = p_arr[counter].pid;
            strcpy(pid_name, p_arr[counter].name);
            break;
        }
    }
    for_proc = pid;
    strcpy(for_proc_name, pid_name);
    for (int j = pid; j <= p_cnt; j++)
    {
        strcpy(p_arr[j].name, p_arr[j + 1].name);
        p_arr[j].pid = p_arr[j + 1].pid;
    }
    p_cnt--;
    int status;
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(0, pid);
    kill(pid, 18);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpgrp());
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
}