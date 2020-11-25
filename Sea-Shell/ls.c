#include "header.h"

DIR *dir;
struct dirent *d;
void comp(int flag_a, int flag_l)
{
    if (dir == NULL)
    {
        perror("ls ");
        return;
    }

    while (d = readdir(dir))
    {
        printf(RESET);

        if (flag_a != 1)
        {
            if (d->d_name[0] == '.')
                continue;
        }
        if (flag_l == 1)
        {
            struct stat s1;
            stat(d->d_name, &s1);
            (S_ISDIR(s1.st_mode)) ? printf("d") : printf("-");
            (s1.st_mode & S_IRUSR) ? printf("r") : printf("-");
            (s1.st_mode & S_IWUSR) ? printf("w") : printf("-");
            (s1.st_mode & S_IXUSR) ? printf("x") : printf("-");
            (s1.st_mode & S_IRGRP) ? printf("r") : printf("-");
            (s1.st_mode & S_IWGRP) ? printf("w") : printf("-");
            (s1.st_mode & S_IXGRP) ? printf("x") : printf("-");
            (s1.st_mode & S_IROTH) ? printf("r") : printf("-");
            (s1.st_mode & S_IWOTH) ? printf("w") : printf("-");
            (s1.st_mode & S_IXOTH) ? printf("x") : printf("-");
            printf(" ");
            printf("%ld ", s1.st_nlink);
            struct group *gr = getgrgid(s1.st_gid);
            struct passwd *pw = getpwuid(s1.st_uid);
            printf("%s ", pw->pw_name);
            printf("%s ", gr->gr_name);
            printf("%8zu ", s1.st_size);
            char tim[1000];
            strftime(tim, 50, "%b  %d %H:%M ", localtime(&s1.st_mtime));
            printf("%s", tim);
        }
        if (d->d_type == 4)
            printf(BOLDBLUE);
        else
            printf(RESET);

        printf("%s\n", d->d_name);
        printf(RESET);
    }
    closedir(dir);
}

void ls(char *text)
{
    char *args[1000];
    int i = 0;

    args[i] = strtok(text, " ");
    int flag_a = 0, flag_l = 0, flag_cur = 0;

    if (args[0] == NULL)
    {
        dir = opendir(".");
        if (dir == NULL)
        {
            printf("error in opening directory");
            return;
        }
        comp(flag_a, flag_l);
        return;
    }

    while (args[i] != NULL)
    {
        if (args[i][0] == '-')
        {
            for (int p = 1; p < strlen(args[i]); p++)
            {
                if (args[i][p] == 'a')
                    flag_a = 1;
                else
                    flag_l = 1;
            }

            args[i] = strtok(NULL, " ");
            if (args[i] == NULL)
            {
                flag_cur = 1;
            }
            continue;
        }
        i++;
        args[i] = strtok(NULL, " ");
    }
    if (flag_cur)
    {
        dir = opendir(".");
        comp(flag_a, flag_l);
        return;
    }
    int k = 0;
    while (k < i)
    {
        if (strcmp(args[k], "~") == 0)
            dir = opendir(tilde);

        else
        {
            dir = opendir(args[k]);
        }
        printf("\n%s: \n", args[k]);

        comp(flag_a, flag_l);
        k++;
    }
}