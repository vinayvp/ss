#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opc
{
    char op[100];
    char hex[3];
};

struct data
{
    char label[100];
    char opcode[100];
    char operand[100];
};

struct str
{
    char *stt;
};

struct sym
{
    char lab[100];
    char addr[100];
};

char delimeter[] = " \t\n";
char word[100], l[100];

struct str sample[100];
struct data list[200];
struct opc opdata[200];
struct sym s[100];

FILE *fp, *fp1, *fp2, *fp3, *fp4;
int LOCCTR = 0, start, prgmlen, lc = 0, oc = 0, sc = 0, flag = 0, value, j, k;

void openfile()
{
    fp = fopen("optab.txt", "r");
    fp1 = fopen("SIC_input.txt", "r");
    fp2 = fopen("intermediate.txt", "w");
    fp3 = fopen("SYMTAB.txt", "r");
    fp4 = fopen("SYMTAB.txt", "w");
}

void optab()
{
    if (fp == NULL)
    {
        printf("Failed to open file Optab!\n");
    }
    else
    {
        printf("File opening success Optab!\n");
    }

    while (fgets(word, 30, fp) != NULL)
    {
        oc++;
        int count1 = 0;
        char *token = strtok(word, delimeter);
        while (token != NULL)
        {
            count1++;
            sample[count1].stt = token;
            token = strtok(NULL, delimeter);
        }
        if (count1 == 2)
        {
            strcpy(opdata[oc].op, sample[1].stt);
            strcpy(opdata[oc].hex, sample[2].stt);
        }
        printf("%s\t%s\n", opdata[oc].op, opdata[oc].hex);
    }

    printf("\n\n\n");
}

void SICinput()
{

    char com[100];
    if (fp1 == NULL)
    {
        printf("Failed to open file SIC_input!\n");
    }
    else
    {
        printf("File opening success SIC_input!\n");
    }
    int temp = 1;

    while (fgets(word, 30, fp1) != NULL)
    {
        lc++;
        int count2 = 0;
        char *token = strtok(word, delimeter);
        while (token != NULL)
        {
            count2++;
            sample[count2].stt = token;
            token = strtok(NULL, delimeter);
        }
        if (count2 == 3)
        {
            strcpy(com, sample[1].stt);
            if (com[0] != '.')
            {
                strcpy(list[lc].label, sample[1].stt);
                strcpy(list[lc].opcode, sample[2].stt);
                strcpy(list[lc].operand, sample[3].stt);
            }
        }
        if (count2 == 2)
        {
            strcpy(com, sample[1].stt);
            if (com[0] != '.')
            {
                strcpy(list[lc].opcode, sample[1].stt);
                strcpy(list[lc].operand, sample[2].stt);
            }
        }
        if (count2 == 1)
        {
            strcpy(com, sample[1].stt);
            if (com[0] != '.')
            {
                strcpy(list[lc].opcode, sample[1].stt);
            }
        }
    }
    printf("\n\n");
}

int hextodec(char hex[100])
{
    long int decimal = 0, i, base = 1;
    int length = strlen(hex);
    for (i = length--; i >= 0; i--)
    {
        if (hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }
        else if (hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }
    }
    return decimal;
}

void inter_sym()
{
    int temp = 1;
    int c = 1;
    while (c < lc)
    {
        if (!strcmp(list[c].opcode, "START"))
        {
            LOCCTR = hextodec(list[c].operand);
            start = hextodec(list[c].operand);
            printf("%x\t%s\t%s\t%s\n", LOCCTR, list[c].label, list[c].opcode, list[c].operand);
            fprintf(fp2, "%x\t%s\t%s\t%s\n", LOCCTR, list[c].label, list[c].opcode, list[c].operand);
            c++;
        }

        if (strcmp(list[c].opcode, "END"))
        {
            if (strcmp(list[c].opcode, ""))
            {
                printf("%x\t%s\t%s\t%s\n", LOCCTR, list[c].label, list[c].opcode, list[c].operand);
                fprintf(fp2, "%x\t%s\t%s\t%s\n", LOCCTR, list[c].label, list[c].opcode, list[c].operand);
            }

            if (strcmp(list[c].label, "")) // for sym table
            {
                while (fgets(word, 30, fp3) != NULL)
                {
                    sc++;
                    int count3 = 0;
                    char *token = strtok(word, delimeter);
                    while (token != NULL)
                    {
                        count3++;
                        sample[count3].stt = token;
                    }
                    if (count3 == 2)
                    {
                        strcpy(s[sc].lab, sample[1].stt);
                        strcpy(s[sc].addr, sample[2].stt);
                    }
                }

                /*if(sc>0)
                {
                    for(k=1; k<=sc; k++)
                    {
                        if(!strcmp(list[c].label,s[k].lab))
                        {
                            flag=1;
                            printf("\nLabel already exists!\n");
                        }
                    }
                }*/

                if (flag == 0)
                {
                    fprintf(fp4, "%s\t%x\n", list[c].label, LOCCTR);
                }
            }

            for (j = 0; j <= oc; j++)
            {
                if (!strcmp(list[c].opcode, opdata[j].op) && (strcmp(list[c].opcode, "")))
                {
                    LOCCTR = LOCCTR + 3;
                }
            }

            if (!strcmp(list[c].opcode, "RESW"))
            {
                value = atoi(list[c].operand);
                LOCCTR = LOCCTR + (value * 3);
            }
            else if (!strcmp(list[c].opcode, "RESB"))
            {
                value = atoi(list[c].operand);
                LOCCTR = LOCCTR + value;
            }
            else if (!strcmp(list[c].opcode, "BYTE"))
            {
                if (list[c].operand[0] == 'C')
                {
                    value = strlen(list[c].operand);
                    LOCCTR = LOCCTR + (value - 3);
                }
                if (list[c].operand[0] == 'X')
                {
                    value = strlen(list[c].operand);
                    value = value - 3;
                    LOCCTR = LOCCTR + (value / 2);
                }
            }
            else if (!strcmp(list[c].opcode, "WORD"))
            {
                LOCCTR = LOCCTR + 3;
            }
            else
            {
                if (!strcmp(list[c].opcode, "."))
                {
                    printf("%s IS A Invalid OPCODE!!!!!....\n", list[c].opcode);
                    LOCCTR = LOCCTR + 0;
                    exit(0);
                }
            }
            c++;
        }
    }

    printf("%x\t%s\t%s\t%s\n", LOCCTR, list[lc].label, list[lc].opcode, list[lc].operand);
    fprintf(fp2, "%x\t%s\t%s\t%s\n", LOCCTR, list[lc].label, list[lc].opcode, list[lc].operand);

    prgmlen = LOCCTR - start;
    printf("\nProgram length is %x \n", prgmlen);
}

void closefile()
{
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}

int main()
{
    openfile();
    optab();
    SICinput();
    inter_sym();
    closefile();
    return 0;
}
