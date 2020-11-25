#include "header.h"

void pwd()
{
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}

void cd(char *text)
{
    if (strcmp(text, "") == 0)
    {
        getcwd(prev_dir, sizeof(prev_dir));
        chdir(tilde);
        return;
    }
    getcwd(cwd, sizeof(cwd));
    if (strcmp(text, "~") == 0)
    {
        getcwd(prev_dir, sizeof(prev_dir));
        chdir(tilde);
        return;
    }
    if (strcmp(text, "-") == 0)
    {
        char prev[1000];
        getcwd(prev, sizeof(prev));
        chdir(prev_dir);
        strcpy(prev_dir, prev);

        char cwd_hyphen[1000];
        getcwd(cwd_hyphen, sizeof(cwd_hyphen));

        char temp[1000];
        strcpy(temp, cwd_hyphen);
        char *token = strtok(temp, "/");
        char dir[1000], show[1000];
        int flag = 0;
        dir[0] = '\0';

        char s1[1000];
        char s2[1000];
        char *p;
        strcpy(s1, cwd_hyphen);
        strcpy(s2, tilde);
        int k = strlen(s2);
        p = strstr(s1, s2);

        if (p)
        {
            flag = 1;
        }
        if (flag == 1)
            printf("~%s\n", &p[k]);
        else if (flag == 0)
            printf("%s", cwd);

        return;
    }
    strcat(cwd, "/");
    strcat(cwd, text);

    getcwd(prev_dir, sizeof(prev_dir));
    if (chdir(cwd) < 0)
        printf("%s : No such directory\n", text);
}