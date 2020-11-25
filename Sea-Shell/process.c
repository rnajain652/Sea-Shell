#include "header.h"

void pinfo(char *pt)
{
    int pid, i = 1;
    // printf("%s\n", pt);
    if (strcmp(pt, "") == 0)
    {
        pid = getpid();
    }
    else
    {
        pid = atoi(pt);
    }

    FILE *fptr;

    char status_path[1000], e_path[1000];

    sprintf(status_path, "/proc/%d/status", pid);
    fptr = fopen(status_path, "r");
    if (fptr == NULL)
    {
        printf("Process doesn't exists.");
        return;
    }
    char status[500], memory[500];
    char text[500];
    while (fgets(text, sizeof(text), fptr) != NULL)
    {
        if (i == 3)
        {
            strcpy(status, text);
        }
        else if (i == 18)
        {
            strcpy(memory, text);
        }
        i++;
    }

    char *s = strtok(status, ":\t");
    s = strtok(NULL, ":\t");
    char *m = strtok(memory, ":\t");
    m = strtok(NULL, ":\t");

    printf("pid -- %d\n", pid);
    printf("Process Status -- %s", s);
    printf("Memory -- %s", m);

    sprintf(e_path, "/proc/%d/exe", pid);
    char exe_p[1000];
    int r = readlink(e_path, exe_p, 1000);

    if (r == -1)
    {
        printf("process not exists.\n");
        return;
    }
    char s1[1000];
    char s2[1000];
    char *p;
    strcpy(s1, exe_p);
    strcpy(s2, tilde);
    int k = strlen(s1);
    int l = strlen(s2);
    p = strstr(s1, s2);

    if (p)
    {
        printf("Executable Path -- ~%s\n", &p[l]);
    }
    else
    {
        printf("Executable Path -- %s\n", exe_p);
    }

    fclose(fptr);
}

void jobs()
{
    for (int counter = 1; counter <= p_cnt; counter++)
    {
        int pid, i = 1;
        pid = p_arr[counter].pid;
        char *name = p_arr[counter].name;
        FILE *fptr;

        char status_path[1000], e_path[1000];

        sprintf(status_path, "/proc/%d/status", pid);
        fptr = fopen(status_path, "r");
        if (fptr == NULL)
        {
            printf("Process doesn't exists.\n");
            return;
        }
        char status[500];
        char text[500];
        while (fgets(text, sizeof(text), fptr) != NULL)
        {
            if (i == 3)
            {
                strcpy(status, text);
            }
            i++;
        }
        //    printf("%s", status);
        char *s = strtok(status, ":\t");
        //    printf("%s", s);
        s = strtok(NULL, ":\t");
        char *state = strtok(s, " ");
        //printf("%s", state);

        if (strcmp(state, "S") == 0 || strcmp(state, "R") == 0)
        {
            s = "Running";
        }
        else if (strcmp(state, "T") == 0)
        {
            s = "Stopped";
        }

        printf("[%d] %s %s [%d]\n", counter, s, name, pid);
    }
}
