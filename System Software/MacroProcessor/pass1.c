#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
    FILE *f1, *f2, *f3;
    char mne[20], opnd[20], la[20];
    f1 = fopen("./Files/macrotext.txt", "r");
    if (f1 == NULL)
    {
        printf("Failed to open File f1\n");
        exit(0);
    }
    f2 = fopen("./Files/NAMTAB.txt", "w+");
    if (f2 == NULL)
    {
        printf("Failed to open File f2\n");
        exit(0);
    }

    f3 = fopen("./Files/DEFTAB.txt", "w+");
    if (f3 == NULL)
    {
        printf("Failed to open File f3\n");
        exit(0);
    }
    int cnt=0;
    fscanf(f1, "%s\t%s\t%s", la, mne, opnd);
    cnt++;
    while (strcmp(mne, "END") != 0)
    {
        while (strcmp(mne, "MEND") != 0)
        {
            if (strcmp(mne, "MACRO") == 0)
            {
                fprintf(f2, "%s\t%d", la, cnt);
                fprintf(f3, "%s\t%s\n", la, opnd);
            }
            else
                fprintf(f3, "%s\t%s\n", mne, opnd);
            printf("%s\n", mne);
            fscanf(f1, "%s%s%s", la, mne, opnd);
            cnt++;
        }
        fprintf(f2, "\t%d\n", cnt);
        fprintf(f3, "%s\n", mne);
        printf("%s", mne);
        fscanf(f1, "%s%s%s", la, mne, opnd);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    printf("PASS 1 is successful");
}