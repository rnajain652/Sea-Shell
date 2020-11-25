#include "header.h"

int sea_shell_id = 0;
void handler()
{
    //printf("fo");
    int status;
    int p = waitpid(-1, &status, WNOHANG);

    for (int i = 1; i <= p_cnt; i++)
    {
        if (p < 0)
        {
            printf("error\n");
            break;
        }
        const int exit = WEXITSTATUS(status);
        int ret = WIFEXITED(status);
        //        printf("%d %d %d %d ", exit, ret, p, p_arr[i].pid);
        if (ret && p == p_arr[i].pid || kjob_stop == p_arr[i].pid && p == p_arr[i].pid)
        {
            if (exit == 0)
                fprintf(stderr, "\n%s with pid %d exited normally\n", p_arr[i].name, p_arr[i].pid);
            else
                fprintf(stderr, "\nExitted abnormally \n");
            prompt();
            fflush(stdout);
            for (int j = i; j <= p_cnt; j++)
            {
                strcpy(p_arr[i].name, p_arr[i + 1].name);
                p_arr[i].pid = p_arr[i + 1].pid;
            }
            p_cnt--;
            if (kjob_stop != 0)
            {
                kjob_stop = 0;
            }
        }
    }
}

void controlC(int signo)
{
    //  printf("yo");
    int pid = getpid();
    //    printf("%d", pid);
    printf("\n");
    if (pid != sea_shell_id)
        return;
    if (for_proc == -1)
    {
        prompt();
        fflush(stdout);
    }
    if (for_proc != -1)
        kill(for_proc, SIGINT);

    //    signal(SIGINT, controlC);
}

// void controlZ(int signo)
// {
//     //  printf("yo");
//     pid_t pid = getpid();
//     //    printf("%d", pid);
//     // printf("\n");
//     if (pid != sea_shell_id)
//         return;

//     if (for_proc != -1)
//     {
//         kill(for_proc, SIGTTIN);
//         kill(for_proc, SIGTSTP);
//         p_cnt++;
//         p_arr[p_cnt].pid = for_proc;
//         strcpy(p_arr[p_cnt].name, for_proc_name);
//         return;
//     }
//     signal(SIGTSTP, controlZ);
//     if (pid == sea_shell_id)
//     {
//         prompt();
//         fflush(stdout);
//     }
//     return;
// }

// void controlZ(int signo)
// {
//     pid_t p = getpid();
//     if (p != sea_shell_id)
//         return;
//     if (for_proc != -1)
//     {
//         kill(for_proc, SIGTTIN);
//         kill(for_proc, SIGTSTP);
//         p_cnt++;
//         p_arr[p_cnt].pid = for_proc;
//         strcpy(p_arr[p_cnt].name, for_proc_name);
//         return;
//     }
//     signal(SIGTSTP, controlZ);
//     if (p == sea_shell_id)
//     {
//         prompt();
//         fflush(stdout);
//     }

//     return;
// }

void controlZ(int signo)
{
    int pid = getpid();
   // printf("pid:%d shell_pid: %d for_proc: %d\n", pid, sea_shell_id, for_proc);
    if (pid != sea_shell_id)
    {
        return;
    }
    if (for_proc != -1)
    {
        //   printf("yoyoyy wowow\n");
        kill(for_proc, SIGTTIN);
        kill(for_proc, SIGTSTP);
        p_cnt++;
        p_arr[p_cnt].pid = for_proc;
        strcpy(p_arr[p_cnt].name, for_proc_name);
    }
    else
    {
        fflush(stdout);
    }
//    signal(SIGTSTP, controlZ);
    fflush(stdout);
}

int main()
{
    p_cnt = 0;
    kjob_stop = 0;
    controlD = 0;
    printf("\n\n\t**** Welcome to The-Sea-Shell  ****\n\n");

    printf("\t****to quit type \"quit\" without quotes ****\n\n");

    /*  ---------------------HOME Address------------------------------- */

    getcwd(cwd, sizeof(cwd));
    sea_shell_id = getpid();
    //printf("home_id:%d", sea_shell_id);
    strcpy(tilde, cwd);

    /* -------------------------SHELL LOOP --------------------------*/
    while (1)
    {
        for_proc = -1;
        strcpy(exe_part, "");
        signal(SIGCHLD, handler);
        signal(SIGINT, controlC);
        signal(SIGTSTP, controlZ);
        prompt();
        input();

        if (strcmp(cmdline, "quit") == 0)
            break;
    }
    overkill();
    printf("\n\n\t****hope you liked working here****\n\n");

    printf("\t****Terminating****\n\n");

    return 0;
}