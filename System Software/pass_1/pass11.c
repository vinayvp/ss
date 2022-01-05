#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void main()
{
   FILE *f1,*f2,*f3,*f4;
   int lcctr,startaddr,i=0,j=0,len,l=0,op1,symadd,opstart;
   char name[10],opnd[10],la[10],mne[10],s1[10],mne1[10],opnd1[10];
  f1=fopen("input.txt","r");
  f2=fopen("intermediateFile.txt","w");
  f3=fopen("optab.txt","r");
  f4=fopen("symtab.txt","w");
  fscanf(f1,"%s%s%X",la,mne,&opstart);

  if(strcmp(mne,"START")==0)
 {
    startaddr=opstart;
    strcpy(name,la);
    lcctr=startaddr;
    printf("Location Address defined in program, Loc address= %X\n",lcctr);
 }
 else
 {
     lcctr=0;
     printf("Location Address not defined, taking default = %X\n",lcctr);
 }
 fprintf(f2,"\t%s\t%s\t%X\n",la,mne,lcctr);

 fscanf(f1,"%s%s%s",la,mne,opnd);
int flag=0;
 while(!feof(f1))
 {
     printf("%X\t%s\t%s\t%s\n",lcctr,la,mne,opnd);
     fprintf(f2,"%X\t%s\t%s\t%s",lcctr,la,mne,opnd);



    //  fscanf(f1,"%s%s%s",la,mne,opnd);
    //  while(!feof(f3))
    //  {
    //      fscanf(f3,"%s%s",mne1,opnd1);

    //      if(!(strcmp(mne,mne1)==0 /*|| mne=="WORD" || mne=="BYTE" || mne=="RESW" || mne=="RESB" || mne=="END"*/))
    //      {
    //          flag=1;
    //      }
    //  }
    //   if(flag==1){
    //          printf("invalid opcode= %s\n",mne);}


     if(strcmp(la,"-")!=0)
     {
         fprintf(f4,"%X\t%s\n",lcctr,la);
     }
         fscanf(f3,"%s%s",mne1,opnd1);

         while(!feof(f3))
         {
             if(strcmp(mne,mne1)==0)
             {
                 lcctr=lcctr+3;
                 break;
             }
            fscanf(f3,"%s%s",mne1,opnd1);
         }

         if(strcmp(mne,"WORD")==0)
         {
             lcctr=lcctr+3;
         }

         else if(strcmp(mne,"RESW")==0)
        {
         op1=atoi(opnd);
         lcctr=lcctr+(3*op1);
         }

         else if(strcmp(mne,"RESB")==0)
        {
         op1=atoi(opnd);
         lcctr=lcctr+op1;
        }

        else if(strcmp(mne,"BYTE")==0)
        {
         if(opnd[0]=='X')
         lcctr=lcctr+1;
         else
         {
          int len=strlen(opnd)-3;
         lcctr=lcctr+len;}
        }

        fscanf(f1,"%s%s%s",la,mne,opnd);
    fprintf(f2,"\n");

 }
 printf("\nProgram length=%x",lcctr-startaddr);
 }
