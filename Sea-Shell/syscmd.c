#include "header.h"

void backg(char *a[])
{
    p_cnt++;
    pid_t pid;
    pid = fork();
    setpgid(0, 0);
    strcpy(p_arr[p_cnt].name, a[0]);
    p_arr[p_cnt].pid = pid;
    if (pid < 0)
    {
        perror("Error");
        return;
    }
    if (pid == 0)
    {
        if (signal(SIGTSTP, handler))
            ;

        if (execvp(a[0], a) == -1)
        {
            perror("Error");
        }
        exit(0);
    }
}
void foreg(char *a[])
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        perror("Error");
        _exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(a[0], a) == -1)
            printf("Error : Command not found");
        exit(0);
    }
    else
    {
        int status;
        for_proc = pid;
        waitpid(pid, &status, WUNTRACED);
    }
    return;
}
void syscmd(char *text)
{
    //    printf("text:%syo\n", text);
    char *args[1000];
    int i = 0, flag_amp = 0;
    for (int i = 0; i < 1000; i++)
    {
        args[i] = "";
    }

    char *token = strtok(text, " ");
    while (token != NULL)
    {
        if (strcmp(token, "&") == 0)
        {
            flag_amp = 1;
        }
        else
        {
            args[i] = token;
            i++;
        }

        token = strtok(NULL, " ");
    }
    //    printf("\ni:%d", i);
    args[i] = token;

    if (flag_amp == 1)
        backg(args);
    else
        foreg(args);
    // int pid = fork();
    // if (flag_amp == 1)
    //     setpgid(0, 0);
    // if (!pid)
    // {
    //     int r = execvp(args[0], args);
    //     int p = getpid();
    //     if (r == -1)
    //     {
    //         printf("%s: Command not found\n", args[0]);
    //         return;
    //     }
    //     if (strcmp(args[0], "vim") == 0 && flag_amp == 1)
    //     {
    //         kill(p, SIGSTOP);
    //     }
    // }
    // else
    // {
    //     if (flag_amp != 1)
    //     {
    //         for_proc = pid;
    //         strcpy(for_proc_name, args[0]);
    //         waitpid(pid, NULL, 0);
    //     }
    //     else
    //     {
    //         p_cnt++;
    //         printf("[%d] %d\n", p_cnt, pid);
    //         p_arr[p_cnt].pid = pid;
    //         strcpy(p_arr[p_cnt].name, args[0]);
    //     }
    // }
}

void kjob(char *text)
{
    char *token[1000];
    int i = 0;
    token[i] = strtok(text, " ");
    while (token[i] != NULL)
    {
        i++;
        token[i] = strtok(NULL, " ");
    }
    if (i != 2)
    {
        printf("too few arguments or too many arguments\n");
        return;
    }
    int p_no = atoi(token[0]);
    int sig_no = atoi(token[1]);
    int pid;
    if (p_no > p_cnt || p_no < 0)
    {
        printf("no job exists\n");
        return;
    }
    for (int counter = 1; counter <= p_cnt; counter++)
    {
        if (p_no == counter)
        {
            pid = p_arr[counter].pid;
            break;
        }
    }
    kjob_stop = pid;
    kill(pid, sig_no);
}

void overkill()
{
    for (int i = 1; i <= p_cnt; i++)
    {
        int pid = p_arr[i].pid;

        kill(pid, 9);
        p_cnt--;
    }
}