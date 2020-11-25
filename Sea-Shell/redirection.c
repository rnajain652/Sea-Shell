#include "header.h"

void redirection()
{
    int std_in_saved = dup(0);
    int std_out_saved = dup(1);
    size_t buf_size = 1000;

    cmdline = ignorespace(cmdline, buf_size);

    char *in_redirect = strstr(cmdline, "<");
    char *out_redirect = strstr(cmdline, ">");
    char *app_redirect = strstr(cmdline, ">>");

    //    printf("cmdline:%s\nout:%s\napp:%s\n", cmdline, out_redirect, app_redirect);

    if (in_redirect == NULL && out_redirect == NULL)
    {
        strcpy(cmdline, cmdline);
        compare();
    }
    if (in_redirect == NULL && out_redirect != NULL)
    {
        char *args[1000];
        int i = 0;
        args[i] = strtok(cmdline, ">");
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, ">");
        }

        args[0] = ignorespace(args[0], buf_size);
        args[1] = ignorespace(args[1], buf_size);
        int fd;
        if (app_redirect == NULL)
            fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd = open(args[1], O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (fd < 0)
        {
            perror("Failed to open file.");
            return;
        }
        if (dup2(fd, 1) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            return;
        }
        close(fd);

        strcpy(cmdline, args[0]);

        compare();

        dup2(std_out_saved, 1);
        close(std_in_saved);
        close(std_out_saved);
    }

    if (in_redirect != NULL && out_redirect == NULL)
    {
        char *args[1000];
        int i = 0;
        args[i] = strtok(cmdline, "<");
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, "<");
        }

        args[0] = ignorespace(args[0], buf_size);
        args[1] = ignorespace(args[1], buf_size);

        int fd = open(args[1], O_RDONLY, 0644);

        if (fd < 0)
        {
            perror("Failed to open file.");
            return;
        }
        if (dup2(fd, 0) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            return;
        }
        close(fd);

        strcpy(cmdline, args[0]);

        compare();

        dup2(std_in_saved, 0);
        close(std_in_saved);
        close(std_out_saved);
    }

    if (in_redirect != NULL && out_redirect != NULL)
    {
        char *args[1000];
        int i = 0;
        args[i] = strtok(cmdline, "><");
        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, "><");
        }

        args[0] = ignorespace(args[0], buf_size);
        args[1] = ignorespace(args[1], buf_size);
        args[2] = ignorespace(args[2], buf_size);

        int fd1 = open(args[1], O_RDONLY, 0644);
        int fd2;
        if (app_redirect == NULL)
            fd2 = open(args[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else
            fd2 = open(args[2], O_WRONLY | O_CREAT | O_APPEND, 0644);

        if (fd1 < 0)
        {
            perror("file1");
            return;
        }
        if (fd2 < 0)
        {
            perror("file2");
            return;
        }
        if (dup2(fd1, 0) < 0 || dup2(fd2, 1) < 0)
        {
            perror("Unable to duplicate file descriptor.");
            return;
        }
        close(fd1);
        close(fd2);

        strcpy(cmdline, args[0]);

        compare();

        dup2(std_in_saved, 0);
        dup2(std_out_saved, 1);
        close(std_in_saved);
        close(std_out_saved);
    }
}