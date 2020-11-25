#include "header.h"

void prompt()
{
    getlogin_r(lname, sizeof(lname));
    gethostname(hname, sizeof(hname));
    getcwd(cwd, sizeof(cwd));

    char temp[1000];
    strcpy(temp, cwd);
    char *token = strtok(temp, "/");
    char dir[1000], show[1000];
    int flag = 0;
    dir[0] = '\0';

    char s1[1000];
    char s2[1000];
    char *p;
    strcpy(s1, cwd);
    strcpy(s2, tilde);
    int k = strlen(s2);
    p = strstr(s1, s2);

    if (p)
    {
        flag=1;
    }

    if ( flag == 1)
    printf("<" BOLDMAGENTA "%s@%s" RESET ":" YELLOW "~%s" RESET ">", lname, hname, &p[k]);
    else if (flag == 0)
    printf("<" BOLDMAGENTA "%s@%s" RESET ":" YELLOW "%s" RESET ">", lname, hname, cwd);
}