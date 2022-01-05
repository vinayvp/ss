#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char label[50], opcode[50], operand[50];
char symbol[50];
char address[10];
char mnemonic[50];
int length;


int searchSymtab()
{
    FILE *fp4=fopen("symtab.txt","r");
    int found = 0;

    while(!feof(fp4))
    {
        fscanf(fp4,"%s\t%s",symbol,address);
        if(strcmp(symbol,label)==0)
        {
            found = 1;
            break;

        }
        fscanf(fp4,"%s\t%s",symbol,address);
    }

    fclose(fp4);
    return found;
}

int searchOptab()
{
    FILE *fp5=fopen("optab.txt","r");
    if(fp5 == NULL)
        printf("Error opening optab.txt");

    int found = 0;
    while(!feof(fp5))
    {
        fscanf(fp5,"%s\t%s",mnemonic,address);
        if(strcmp(mnemonic, opcode)==0)
        {
            found = 1;
            break;

        }
    }

    fclose(fp5);
    return found;
}


void pass1(){
    char delimit[]=" \t\r\n";
    int locctr, start=0;
    char line[100];
    size_t len = 100 * sizeof(char);
    locctr = 0x0;

    FILE *fp1 = fopen("input.txt", "r");
    if (fp1 == NULL)
        exit(EXIT_FAILURE);

    FILE *fp2, *fp3, *fp4;

    fp2 = fopen("symtab.txt", "w");
    fp3 = fopen("intermediate.txt", "w");
    fclose(fp2);


    while ((fgets(line, len, fp1)) != NULL)
    {
        int len = 0;
        strcpy(label, " ");
        strcpy(opcode, " ");
        strcpy(operand, " ");
        char *p = strtok (line, delimit);
        char *array[4];

        while (p != NULL)
        {
            array[len++] = p;
            p = strtok (NULL, delimit);
        }

        if(len == 1){
            strcpy(opcode, array[0]);
        }
        else if(len == 2){
            strcpy(opcode, array[0]);
            strcpy(operand, array[1]);
        }
        else if(len == 3){
            strcpy(label, array[0]);
            strcpy(opcode, array[1]);
            strcpy(operand, array[2]);
        }
        if(strcmp(opcode, "END")==0)
            break;

        if (strcmp(opcode, "START") == 0) {
            start = (int)strtol(operand, NULL, 16);
            locctr = start;
            fprintf(fp3, "\t\t%s\t%s\t%s\n", label, opcode, operand);
            continue;
        }


        if((!strcmp(label, " ")==0) || (!strcmp(opcode, " ")==0) || (!strcmp(operand, " ")==0))
        {
            fprintf(fp3, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
            if (strcmp(label, " ") != 0)
                if(!searchSymtab() && strcmp(label,"-")!=0)
                {
                    fp2 = fopen("symtab.txt", "a");
                    fprintf(fp2, "%s\t%X\n", label, locctr);
                    fclose(fp2);
                }
                else if(strcmp(label,"-") != 0)
                {
                    printf("Error !!! Duplicate Symbol found \n DUPLICATE SYMBOL == %s\n", label);

                }

            if(searchOptab())
                locctr += 3;

            else if (strcmp(opcode, "WORD") == 0)
            {
                locctr += 3;
            }

            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += 3 * atoi(operand);
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += 1 * atoi(operand);
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                if(operand[0] == 'C' || operand[0] == 'c')
                    locctr += (strlen(operand) - 3);
                else
                    locctr ++;
            }
            else
            {
                printf("Error !!! Invalid Opcode found \n INVALID CODE USED == %s\n", opcode);
            }

          }
    }

    // fprintf(fp3, " \t%s\t%s\t%s\n", label, opcode, operand);


    length = locctr - start;



    fclose(fp1);
    fclose(fp3);
}


void show_intermediate_file(){
    FILE *fp6 = fopen("intermediate.txt", "r");

    if(fp6== NULL)
        printf("Error Opening intermediate file \n");

    printf("\nINTERMEDIATE CODE GENERATED\n\n");

    char line[100];
    size_t len = 100 * sizeof(char);

    while ((fgets(line, len, fp6)) != NULL)
        printf("%s", line);


    fclose(fp6);

}

void show_symtab()
{
    FILE *fp7=fopen("symtab.txt","r");
    if(fp7 == NULL)
        printf("Error Opening SYMTAB file\n");

    printf("\nSYMBOL TABLE \n\n");

    fscanf(fp7,"%s\t%s",symbol,address);
    while(!feof(fp7))
    {
        printf("%s\t%s\n", symbol, address);
        fscanf(fp7,"%s\t%s",symbol,address);
    }

    fclose(fp7);
    printf("\nlength of code is %X bytes in hex\n", length);

}

int main(){

    pass1();
    show_intermediate_file();
    show_symtab();

    return 0;
}