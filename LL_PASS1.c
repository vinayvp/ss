#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ES_TAB
{
    char ctrlSec[10];
    char symName[10];
    long int address;
    int length;
} ESTAB[100];

int checkDuplicateCtrl(char input[10], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(ESTAB[i].ctrlSec, input) == 0)
        {
            return 1;
        }
    }
    return 0;
}
int checkDuplicateSym(char input[10], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(ESTAB[i].symName, input) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void printESTAB(long int row, FILE *fp2)
{
    fprintf(fp2, "[CTRL_SEC]\t[SYM_NAME]\t[ADDRESS]\t[LENGTH]\n");
    for (int i = 0; i < row; i++)
    {
        if (ESTAB[i].length == 0)
            fprintf(fp2, "%s\t\t%s\t\t%lx\t\t\t\n", ESTAB[i].ctrlSec, ESTAB[i].symName, ESTAB[i].address);
        else
            fprintf(fp2, "%s\t\t%s\t\t%lx\t\t%d\n", ESTAB[i].ctrlSec, ESTAB[i].symName, ESTAB[i].address, ESTAB[i].length);
    }
}

void pass1Algo(FILE *fp1, FILE *fp2)
{
    char input[10];
    long int row = 0;
    long int start, length, loc;
    int flag = 0;
    int flag1 = 0;
    printf("\nEnter Start Location: ");
    scanf("%lx", &start);
    rewind(fp1);
    while (!feof(fp1))
    {
        fscanf(fp1, "%s", input);
        if (strcmp(input, "H") == 0) //Header Record Found
        {
            fscanf(fp1, "%s", input);
            flag = checkDuplicateCtrl(input, row);
            if (flag == 1)
            {
                printf("Duplicate Control Section Found\n");
            }
            else
            {
                strcpy(ESTAB[row].ctrlSec, input);
            }
            if (flag == 0)
            {
                strcpy(ESTAB[row].symName, "\t");
            }
            fscanf(fp1, "%s", input);
            if (flag == 0)
            {
                ESTAB[row].address = atoi(input) + start;
            }
            fscanf(fp1, "%s", input);
            length = atoi(input);
            if (flag == 0)
            {
                ESTAB[row].length = atoi(input);
                row++;
            }
            fscanf(fp1, "%s", input);
        }
        if (strcmp(input, "D") == 0) //Defination Record Found
        {
            fscanf(fp1, "%s%lx", input, &loc);
            while ((strcmp(input, "R") != 0))
            {
                flag1 = checkDuplicateSym(input, row);
                if (flag1 != 1 && flag != 1)
                {
                    strcpy(ESTAB[row].ctrlSec, "\t");
                    strcpy(ESTAB[row].symName, input);
                    ESTAB[row].address = loc + start;
                    ESTAB[row].length = 0;
                    row++;
                }
                fscanf(fp1, "%s%lx", input, &loc);
            }
            while (strcmp(input, "T") != 0)
            {
                fscanf(fp1, "%s", input);
            }
        }
        if (strcmp(input, "T") == 0)
        {
            while (strcmp(input, "E") != 0)
            {
                fscanf(fp1, "%s", input);
            }
        }
        fscanf(fp1, "%s", input);
        start = start + length;
    }
    printESTAB(row, fp2);
}

void handleFile()
{
    FILE *fp1, *fp2;
    fp1 = fopen("LL_input.txt", "r");
    fp2 = fopen("LL_output.txt", "w");
    pass1Algo(fp1, fp2);
}

int main()
{
    handleFile();
}