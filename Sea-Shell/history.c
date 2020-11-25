#include "header.h"

void history_wr(char *text)
{
    FILE *fptr;
    char path[10000];

    strcpy(path, tilde);
    strcat(path, "/hist.txt");

    fptr = fopen(path, "r");

    if (fptr == NULL)
    {
        fptr = fopen(path, "w+");
        fprintf(fptr, "%s", text);
        fclose(fptr);
    }
    else
    {
        int i = 0;
        char h[100][500], line[500];
        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            strcpy(h[i], line);
            i++;
        }
        int k = i;

        if (k >= 20)
        {
            for (i = 0; i < k - 1; i++)
            {
                strcpy(h[i], h[i + 1]);
            }
            k--;
            strcpy(h[i], text);
        }
        else
        {
            strcpy(h[k], text);
        }
        fclose(fptr);

        fptr = fopen(path, "w");

        i = 0;
        while (i <= k)
        {
            fprintf(fptr, "%s", h[i]);
            i++;
        }
        fclose(fptr);
    }
}

void hist_show(char *nol)
{
    FILE *fptr;
    char path[10000], line[500];
    strcpy(path, tilde);
    strcat(path, "/hist.txt");
    fptr = fopen(path, "r");
    int siz = 0;
    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        siz++;
    }
    fclose(fptr);

    if (strcmp(nol, "") == 0)
    {
        fptr = fopen(path, "r");
        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            printf("%s", line);
        }
        fclose(fptr);
    }
    else
    {
        fptr = fopen(path, "r");
        int line_no = atoi(nol);
        int i = siz - line_no, j = 0;

        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            if (j < i)
            {
                j++;
                continue;
            }

            printf("%s", line);
            j++;
        }
        fclose(fptr);
    }
}