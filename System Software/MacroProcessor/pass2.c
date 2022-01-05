#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

int i, len, start, end, flag;
char mne[20], opnd[20], la[20], name[20], mne1[20], opnd1[20], arg[20], str[20];

int searchNAMTAB()
{
    int flg;
    FILE *f10;
    f10 = fopen("./Files/NAMTAB.txt", "r");
    if (f10 == NULL)
    {
        printf("Failed to open File f2\n");
        exit(0);
    }
    char nam[20];
    while (!feof(f10))
    {
        fscanf(f10, "%s%d%d", nam, &start, &end);
        if (strcmp(nam, mne) == 0)
        {
            flg = 1;
            break;
        }
        flg = 0;
    }
    fclose(f10);
    return flg;
}
void argu()
{
    FILE *f4;
    f4 = fopen("./Files/ARGTAB.txt", "w+");
    if (f4 == NULL)
    {
        printf("Failed to open File f3\n");
        exit(0);
    }
    len = strlen(opnd);
    for (i = 0; i < len; i++)
    {
        if (opnd[i] != ',')
            fprintf(f4, "%c", opnd[i]);
        else
        {
            fprintf(f4, "\n");
        }
    }
    fclose(f4);
    return;
}
void searcharg(int x)
{
    FILE *f11;
    f11 = fopen("./Files/ARGTAB.txt", "r");
    if (f11 == NULL)
    {
        printf("Failed to open File f3\n");
        exit(0);
    }
    for (int i = 0; i < x; i++)
    {
        fscanf(f11, "%s", arg);
    }
    fclose(f11);
}
void main()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    f1 = fopen("./Files/macrotext.txt", "r");
    if (f1 == NULL)
    {
        printf("Failed to open File f1\n");
        exit(0);
    }
    // f2 = fopen("./Files/NAMTAB.txt", "r");
    // if (f2 == NULL)
    // {
    //     printf("Failed to open File f2\n");
    //     exit(0);
    // }
    f5 = fopen("./Files/Pass2output.txt", "w");
    if (f5 == NULL)
    {
        printf("Failed to open File f3\n");
        exit(0);
    }
    fscanf(f1, "%s%s%s", la, mne, opnd);
    while (strcmp(mne, "END") != 0)
    {

        if (strcmp(mne, "MACRO") == 0)
        {
            fscanf(f1, "%s%s%s", la, mne, opnd);
            while (strcmp(mne, "MEND") != 0)
                fscanf(f1, "%s%s%s", la, mne, opnd);
        }
        else if (strcmp(mne, "START") == 0)
        {
            fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
        }
        else
        {

            FILE *f10;
            f10 = fopen("./Files/NAMTAB.txt", "r");
            if (f10 == NULL)
            {
                printf("Failed to open File f2\n");
                exit(0);
            }
            char nam[20];
            while (!feof(f10))
            {
                fscanf(f10, "%s%d%d", nam, &start, &end);
                if (strcmp(nam, mne) == 0)
                {
                    flag = 1;
                    break;
                }
                flag = 0;
            }
            fclose(f10);
            f3 = fopen("./Files/DEFTAB.txt", "r");
            if (f3 == NULL)
            {
                printf("Failed to open File f3\n");
                exit(0);
            }
            // if (start - 1 != 0)
            // {
            //     int y = end;
            //     for (int i = 1; i < y; i++)
            //     {
            //         fscanf(f3, "%s%s", mne1, opnd1);
            //     }
            //     fscanf(f3, "%s", mne1);
            // }

            if (flag == 0)
            {
                fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
                fscanf(f1, "%s%s%s", la, mne, opnd);
                continue;
            }
            fprintf(f5, "//%s\t%s\t%s\n", la, mne, opnd);
            argu();
            fscanf(f3, "%s%s", mne1, opnd1);
            printf("%s%s\n", mne1, opnd1);
            int fl = 0;
            for (int i = start + 1; i < end; i++)
            {
                fscanf(f3, "%s%s", mne1, opnd1);
                for (int j = 0; j < strlen(opnd1); j++)
                {
                    if ((opnd1[j] == '?'))
                    {
                        searcharg(opnd1[j + 1] - '0');
                        fl = 1;
                    }
                }
                if (fl == 0)
                {
                    fprintf(f5, "-\t%s\t%s\n", mne1, opnd1);
                }
                else
                    fprintf(f5, "-\t%s\t%s\n", mne1, arg);
            }
            fscanf(f3, "%s", mne1);
        }
        fscanf(f1, "%s%s%s", la, mne, opnd);
        fclose(f3);
    }
    fprintf(f5, "%s\t%s\t%s\n", la, mne, opnd);
    fclose(f1);
    fclose(f2);
    fclose(f5);
    printf("End of Pass 2");
}