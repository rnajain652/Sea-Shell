#include "input.h"
#include "process.c"

size_t buf_size = 101;
int redirect_out = 0;
char *ignorespace(char *text, size_t size)
{
    int c = 0, d = 0;
    char *blank;
    blank = (char *)malloc(size * sizeof(char));
    int s_flag = 0;

    if (text[0] != ' ' && text[0] != '\t')
    {
        s_flag = 1;
    }

    while (text[c] != '\0')
    {
        if ((text[c] == ' ' && text[c + 1] == ' ') || (text[c] == '\t' && text[c + 1] == '\t'))
        {
            c++;
            continue;
        }
        else
        {
            if (s_flag != 1)
            {
                s_flag = 1;
                c++;
                continue;
            }
            else
            {
                blank[d] = text[c];
                if (blank[d] == '\t')
                    blank[d] = ' ';
                d++;
            }
        }
        c++;
    }
    if (blank[d - 1] == '\n' || blank[d - 1] == ' ')
        blank[d - 1] = '\0';
    else
    {
        blank[d] = '\0';
    }

    if (blank[0] == '\0')
    {
        return "-1";
    }
    return blank;
}
void extract()
{
    int c = 0, stop = 0;
    char *blank;
    blank = (char *)malloc(buf_size * sizeof(char));
    cmd = (char *)malloc(buf_size * sizeof(char));

    strcpy(blank, cmdline);
    cmd = strtok(blank, " ");

    int i = 0;
    while (cmd[i] == cmdline[i])
    {
        i++;
        if (cmdline[i] == '\0')
            stop = 1;
    }

    if (!stop)
        strcpy(exe_part, &cmdline[i + 1]);
}

int loop_break = 0, main_return = 0;
void compare()
{
    //    printf("cmdline1:%s\n", cmdline);

    if (strcmp(cmdline, "-1") == 0)
    {
        main_return = 1;
        return;
    }
    extract();
    //    printf("cmd:%s\n", cmd);
    //printf("yo9");
    if (strcmp(cmd, "quit") == 0)
    {
        loop_break = 1;
        return;
    }
    else if (strcmp(cmd, "echo") == 0)
    {
        echo(exe_part);
    }
    else if (strcmp(cmd, "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(cmd, "cd") == 0)
    {
        cd(exe_part);
    }
    else if (strcmp(cmd, "ls") == 0 || strcmp(cmd, "l") == 0)
    {
        ls(exe_part);
    }
    else if (strcmp(cmd, "pinfo") == 0)
    {
        pinfo(exe_part);
    }
    else if (strcmp(cmd, "setenv") == 0)
    {
        setenvv(exe_part);
    }
    else if (strcmp(cmd, "unsetenv") == 0)
    {
        unsetenvv(exe_part);
    }
    else if (strcmp(cmd, "jobs") == 0)
    {
        jobs();
    }
    else if (strcmp(cmd, "kjob") == 0)
    {
        kjob(exe_part);
    }
    else if (strcmp(cmd, "bg") == 0)
    {
        bg(exe_part);
    }
    else if (strcmp(cmd, "fg") == 0)
    {
        fg(exe_part);
    }
    else if (strcmp(cmd, "overkill") == 0)
    {
        overkill();
    }
    else if (strcmp(cmd, "history") == 0)
    {
        if (strcmp(exe_part, "") == 0 || exe_part == NULL)
        {
            strcpy(exe_part, "10");
        }
        hist_show(exe_part);
    }
    else
    {
        //        printf("cmd1:%s\n", cmd);
        //        printf("cmdline2:%s\n", cmdline);
        syscmd(cmdline);

        redirect_out = 0;
    }
    //printf("yo10");
}
void input()
{
    inp = (char *)malloc(buf_size * sizeof(char));
    getline(&inp, &buf_size, stdin);

    if (strcmp(inp, "\0") == 0)
    {
        overkill();
        printf("\n\n\t****hope you liked working here****\n\n");

        printf("\t****Terminating****\n\n");
        exit(0);
    }

    history_wr(inp);

    char *args[1000];
    int i = 0;
    args[i] = strtok(inp, ";");
    while (args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, ";");
    }

    int k = 0;
    while (k < i)
    {
        // strcpy(exe_part, "");
        // strcpy(cmd, "");
        cmdline = ignorespace(args[k], buf_size);
        //printf("yo1");
        char *pipe_present = strstr(cmdline, "|");

        if (pipe_present == NULL)
            redirection();
        else
        {
            char *toke[1000];
            int j = 0;
            char temp[1000];
            strcpy(temp, cmdline);
            toke[j] = strtok(temp, "|");
            while (toke[j] != NULL)
            {
                j++;
                toke[j] = strtok(NULL, "|");
            }
            int size = j;
            j = 0;
            while (j < size)
            {
                piping(toke[j], j, size);
                j++;
            }
        }

        //printf("yo2");
        // compare();

        if (main_return == 1)
        {
            main_return = 0;
            return;
        }
        if (loop_break == 1)
        {
            loop_break = 0;
            break;
        }
        k++;
    }
}