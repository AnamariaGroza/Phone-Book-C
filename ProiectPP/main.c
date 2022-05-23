#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  <conio.h>
#include <windows.h>
#include <ctype.h>

#define GREEN 2
#define BLUE 3
#define GREY 8
#define RED 12
#define YELLOW 14
#define WHITE 15

void set_color(int color_code) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

void meniu()
{
    set_color(BLUE);
    printf("[==AGENDA TELEFONICA==]\n");
    set_color(WHITE);
    printf("Vizualizare contacte..");
    set_color(GREEN);
    printf("1\n");
    set_color(WHITE);
    printf("Adaugare contact......");
    set_color(GREEN);
    printf("2\n");
    set_color(WHITE);
    printf("Stergere contact......");
    set_color(GREEN);
    printf("3\n");
    set_color(WHITE);
    printf("Blocare numar.........");
    set_color(GREEN);
    printf("4\n");
    set_color(WHITE);
    printf("Vizualizare blocate...");
    set_color(GREEN);
    printf("5\n");
    set_color(WHITE);
    printf("Cautare dupa: nume....");
    set_color(GREEN);
    printf("6\n");
    set_color(WHITE);
    printf("              numar...");
    set_color(GREEN);
    printf("7\n");
    set_color(WHITE);
    printf("Iesire din program....");
    set_color(GREEN);
    printf("0\n");
    set_color(WHITE);


}
typedef struct contact{
    char nume[30];
    char numar[16];
    char email[50];

}contact;
typedef struct blocat{
    char nume[30];
    char numar[16];
    char email[50];

}blocat;

int nr_contacte,nr_blocate;
contact c[100];
blocat b[100];
void meniu();
void vizualizare_contacte();
int main()
{
    citire();
    while(1!=0)
    {
        int choice = -1;
        meniu();
        while(choice < 0 || choice > 7)
        {
            printf("\nIntroduceti numarul optiunii dorite: ");
            set_color(GREEN);
            scanf("%d",&choice);
            set_color(WHITE);

            switch(choice)
            {
            case 0:
                return 0;
            case 1:
                system("cls");
                vizualizare_contacte();
                break;
            case 2:
                system("cls");
                adaugare_contact();
                break;
            case 3:
                system("cls");
                stergere_contact();
                break;
            case 4:
                system("cls");
                blocare_numar();
                break;
            case 5:
                system("cls");
                vizualizare_blocate();
                break;
            case 6:
                system("cls");
                cautare_nume();
                break;
            case 7:
                system("cls");
                cautare_numar();
                break;

            }
        }
    }


}
void citire()
{

    FILE* fp = fopen("agenda.txt","r");
    fscanf(fp,"%d",&nr_contacte);
    if(fp==NULL){
        printf("Eroare la deschiderea fisierului");
        exit(1);
    }
    int i;
    char temp[2];
    for(i=1;i<=nr_contacte;i++)
    {
        fgets(temp,2,fp);
        fgets(c[i].nume,30,fp);
        c[i].nume[strlen(c[i].nume)-1]='\0';
        fscanf(fp,"%s%s",
               &c[i].numar,
               &c[i].email);
    }
    fclose(fp);
}

void ordonare_agenda()
{
    int i,j;
    for(i=1;i<nr_contacte;i++)
        for(j=i+1;j<=nr_contacte;j++)
            if(strcmp(c[i].nume,c[j].nume)>0)
            {
                char auxnume[30],auxnr[16],auxemail[50];

                strcpy(auxnume,c[i].nume);
                strcpy(c[i].nume,c[j].nume);
                strcpy(c[j].nume,auxnume);

                strcpy(auxnr,c[i].numar);
                strcpy(c[i].numar,c[j].numar);
                strcpy(c[j].numar,auxnr);

                strcpy(auxemail,c[i].email);
                strcpy(c[i].email,c[j].email);
                strcpy(c[j].email,auxemail);
            }
    reactualizare();
}

void vizualizare_contacte()
{
    ordonare_agenda();
    int i;
    citire();
    FILE* fp = fopen("agenda.txt","r");
    fscanf(fp,"%d",&nr_contacte);
    set_color(RED);
    printf("\t===AGENDA===");
    set_color(WHITE);
    for(i=1;i<=nr_contacte;i++)
    {
        set_color(GREY);
        printf("\n----------------------------");
        set_color(WHITE);
        printf("\nNume: ");
        set_color(YELLOW);
        printf("%s",c[i].nume);
        set_color(WHITE);
        printf("\nNumar: ");
        set_color(GREEN);
        printf("%s",c[i].numar);
        set_color(WHITE);
        printf("\nEmail: ");
        set_color(BLUE);
        printf("%s",c[i].email);
        set_color(WHITE);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    fclose(fp);


}

void vizualizare_blocate()
{
    int i;
    citire();
    FILE* fp = fopen("block.txt","r");
    fscanf(fp,"%d",&nr_blocate);
    set_color(RED);
    printf("\t===BLOCATE===");
    set_color(WHITE);
    for(i=1;i<=nr_blocate;i++)
    {
        set_color(GREY);
        printf("\n----------------------------");
        set_color(WHITE);
        printf("\nNume: ");
        set_color(YELLOW);
        printf("%s",b[i].nume);
        set_color(WHITE);
        printf("\nNumar: ");
        set_color(GREEN);
        printf("%s",b[i].numar);
        set_color(WHITE);
        printf("\nEmail: ");
        set_color(BLUE);
        printf("%s",b[i].email);
        set_color(WHITE);
    }
    printf("\n\n");
    system("pause");
    system("cls");
    fclose(fp);
}
void reactualizare()
{
    int i;
    FILE *fp=fopen("agenda.txt","w");
        fprintf(fp,"%d\n",nr_contacte);
        for(i=1;i<=nr_contacte;i++)
        {
            fprintf(fp,"%s\n%s\n%s\n",c[i].nume,c[i].numar,c[i].email);
        }
    fclose(fp);
}
void adaugare_contact()
{

    set_color(RED);
    printf("\t===ADAUGARE CONTACT===\n");
    set_color(WHITE);
    nr_contacte++;
    int i=nr_contacte;
    char temp[2];

    printf("Introduceti numele:");

    set_color(YELLOW);
    fgets(temp,2,stdin);
    fgets(c[i].nume,30,stdin);
    set_color(WHITE);
    c[i].nume[strlen(c[i].nume)-1]='\0';
    printf("Introduceti numarul:");
    set_color(GREEN);
    scanf("%s",&c[i].numar);
    set_color(WHITE);
    printf("Introduceti email-ul:");
    set_color(BLUE);
    fgets(temp,2,stdin);
    fgets(c[i].email,50,stdin);
    set_color(WHITE);
    c[i].email[strlen(c[i].email)-1]='\0';
    printf("\nContactul a fost salvat cu succes:\n");

    FILE* fp = fopen("agenda.txt","a");

    fprintf(fp,"%s\n",c[i].nume);
    fprintf(fp,"%s\n",c[i].numar);
    fprintf(fp,"%s\n",c[i].email);
    fclose(fp);

    fp=fopen("agenda.txt","r+");
    char numar[5];
    itoa(i,numar,10);
    fputs(numar,fp);
    fclose(fp);


    system("pause");
    system("cls");

}
int cautare(char *numar)
{
    int i;
    int p=0;
    for(i=1;i<=nr_contacte;i++)
        if(strcmp(numar,c[i].numar)==0)
            p=i;
    return p;
}
void stergere_efectiva(int p)
{
    int i,ok=0;
    for(i=p;i<nr_contacte;i++)
    {
        strcpy(c[i].nume,c[i+1].nume);
        strcpy(c[i].numar,c[i+1].numar);
        strcpy(c[i].email,c[i+1].email);
        ok=1;
    }
    if(p==nr_contacte)
        ok=1;
    if(ok==1)
        nr_contacte--;
    system("pause");
    reactualizare();
}
void stergere_contact()
{
    int i,p;
    char numar[16];
    set_color(RED);
    printf("\t===STERGERE CONTACT===\n");
    set_color(WHITE);
    printf("Numar contact:");
    set_color(GREEN);
    scanf("%s",&numar);
    set_color(WHITE);
    p=cautare(&numar);
    if(p==0)
        printf("Contactul nu exista\n");
    else
    {
       stergere_efectiva(p);
    }
    //system("pause");
    system("cls");
}
void blocare_numar()
{
    set_color(RED);
    printf("\t===BLOCARE NUMAR===\n");
    set_color(WHITE);
    int i,ok=0,p;
    FILE* fp = fopen("block.txt","r");
    fscanf(fp,"%d",&nr_blocate);
    i=nr_blocate;
    fclose(fp);

    char numar[16];
    printf("Numarul pe care doriti sa il blocati:");
    set_color(GREEN);
    scanf("%s",&numar);
    set_color(WHITE);
    p=cautare(&numar);

    fp=fopen("block.txt","a");
    i++;
    if(p!=0)
    {

        strcpy(b[i].nume,c[p].nume);
        strcpy(b[i].numar,c[p].numar);
        strcpy(b[i].email,c[p].email);

        fprintf(fp,"%s\n",b[i].nume);
        fprintf(fp,"%s\n",b[i].numar);
        fprintf(fp,"%s\n",b[i].email);
        stergere_efectiva(p);
        fclose(fp);

        fp=fopen("block.txt","r+");
        char nr[5];

        itoa(i,nr,10);
        fputs(nr,fp);
        fclose(fp);
        system("pause");

    }
    else
    {
        char temp[2];
        strcpy(b[i].numar,numar);
        printf("Introduceti numele:");
        set_color(YELLOW);
        fgets(temp,2,stdin);
        fgets(b[i].nume,30,stdin);
        set_color(WHITE);
        b[i].nume[strlen(b[i].nume)-1]='\0';
        strcpy(b[i].email,"-");

        fprintf(fp,"%s\n",b[i].nume);
        fprintf(fp,"%s\n",b[i].numar);
        fprintf(fp,"%s\n",b[i].email);
        fclose(fp);

        fp=fopen("block.txt","r+");
        char nr[5];

        itoa(i,nr,10);
        fputs(nr,fp);
        fclose(fp);

    }


    system("cls");
}
void cautare_nume()
{
    set_color(RED);
    printf("\t===CAUTARE DUPA NUME===\n");
    set_color(WHITE);

    printf("Introduceti numele:");
    int p=0,i;
    char nume[30];
    set_color(YELLOW);
    scanf("%s",&nume);
    set_color(WHITE);
    for(i=1;i<=nr_contacte;i++)
    {
        int j;
        char aux[30],aux_nume[30];
        strcpy(aux,c[i].nume);
        strcpy(aux_nume,nume);
        for(j=0;j<strlen(aux);j++)
            aux[j]=tolower(aux[j]);
        for(j=0;j<strlen(aux_nume);j++)
            aux_nume[j]=tolower(aux_nume[j]);
        if(strstr(aux,aux_nume)!= NULL)
        {
            p=1;
            printf("\nNume: %s\nNumar: %s\nEmail: %s\n",c[i].nume,c[i].numar,c[i].email);
        }
    }
    if(p==0)
        printf("\nContactul nu exista\n");
    system("pause");
    system("cls");

}
void cautare_numar()
{
    int p=0,i;
    char numar[16];
     set_color(RED);
    printf("\t===CAUTARE DUPA NUMAR===\n");
    set_color(WHITE);
    printf("Introduceti numarul:");
    set_color(GREEN);
    scanf("%s",&numar);
    set_color(WHITE);
    //p=cautare(&numar);
    for(i=1;i<=nr_contacte;i++)
        if(strstr(c[i].numar,numar)!=NULL)
        {
            p=1;
            printf("\nNume: %s\nNumar: %s\nEmail: %s\n",c[i].nume,c[i].numar,c[i].email);
        }
    if(p==0)
        printf("Contactul nu exista\n");
    printf("\n");

    system("pause");
    system("cls");
}

