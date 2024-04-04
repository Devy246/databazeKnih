/*
 * Projekt: databazeKnih
 * Autor: David Horák
 * Datum: XX-XX-2024
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>  // pro praci s textovymi retezci
#include <stdbool.h> // pro praci s typem bool a konstantami true a false
#include <ctype.h>   // isalpha, isspace, islower, isupper, ...
// #include <math.h>    // funkce z matematicke knihovny
// #include <float.h>   // konstanty pro racionalni typy DBL_MAX, DBL_DIG, ...
// #include <limits.h>  // konstanty pro celociselne typy INT_MAX, INT_MIN, ...
// #include <time.h>    // funkce time a dalsi pro praci s casem
#define MAXZaznamu 512

void dostanInt(int * i){
    scanf(" %d",i);
    while(getchar()!='\n');
}
typedef struct{
    char nazev[256];
    char autor[256];
    char zanr[256];
    int pocetStran;
    int rokVydani;
    bool jeSmazano;
} KNIHA;

typedef struct{
    KNIHA prvky[MAXZaznamu];
    int pocetZaznamu;
} KDATABAZE;

char ziskVolby(char * text){
    printf("%s",text);
    char c;
    scanf(" %c",&c);
    c = toupper(c);
    while(getchar()!='\n');

    return c;
}

void stiskneteEnter(void){
    printf("\nstistknete enter pro vraceni k menu...");
    getchar();
}

void tiskZaznamu(KNIHA zaznam){
    printf("\n\tnazev: %s \n\tautor: %s \n\tzanr: %s \n\tpocet stran: %d \n\trok vydani: %d\n", zaznam.nazev, zaznam.autor, zaznam.zanr, zaznam.pocetStran, zaznam.rokVydani);
    if(zaznam.jeSmazano==1){
            printf("\t[PO UKLADANI ZMEN BUDE TENTO ZAZNAM SMAZAN]\n");
        }
}

void tiskDatabaze(KDATABAZE * databaze){
    for(int i=0;i<databaze->pocetZaznamu;i++){
        printf("%3d: ",i+1);
        tiskZaznamu(databaze->prvky[i]);
    }
    switch(databaze->pocetZaznamu){
    case 1:
        printf("\n\t%d kniha v databazi\n",databaze->pocetZaznamu);
        break;
    case 2:
        printf("\n\t%d knihy v databazi\n",databaze->pocetZaznamu);
        break;
    case 3:
        printf("\n\t%d knihy v databazi\n",databaze->pocetZaznamu);
        break;
    case 4:
        printf("\n\t%d knihy v databazi\n",databaze->pocetZaznamu);
        break;
    default:
        printf("\n\t%d knih v databazi\n",databaze->pocetZaznamu);
        break;
    }
    stiskneteEnter();
}

int nacteniDatabaze(FILE *f, KDATABAZE * databaze){
    databaze->pocetZaznamu = 0;
        int e; KNIHA temp;
        while((e=fscanf(f,"%255[^,], %255[^,], %255[^,], %d, %d\n", temp.nazev, temp.autor, temp.zanr, &temp.pocetStran, &temp.rokVydani))==5){
            temp.jeSmazano = 0;
            databaze->pocetZaznamu++;
            if((databaze->pocetZaznamu)>MAXZaznamu){
                printf("maximalni pocet knih dosazen, vic uz nenacitam");
                databaze->pocetZaznamu--;
                break;
            }
            databaze->prvky[(databaze->pocetZaznamu)-1] = temp;
        }
        // -1 ==eof, 5 znamena ze se nacetlo spravne, ale dosahlo to maximalniho poctu prvku
        if(e!=-1 && e!=5){
            printf("jejdanenky! nastala chyba v formatu databaze, omrknete to prosimvas..");
            return 1;
        } else {
            return 0;
        }

}

void smazaniObnovaZaznamu(KDATABAZE * databaze){
    int s;
    char anoNe;
    printf("zadejte cislo knihy v zaznamu, ktery chcete smazat/obnovit: ");
    dostanInt(&s);
    if( (s<1) || (s>(databaze->pocetZaznamu)) ){
        printf("\nzadane cislo knihy neexistuje, koncim mazani..\n");
    } else {
        if(databaze->prvky[s-1].jeSmazano==1){
            printf("\nrozhodly jste se obnovit zaznam %d:\n",s);
        } else {
            printf("\nrozhodly jste se smazat zaznam %d:\n",s);
        }
        printf("\n\tnazev: %s \n\tautor: %s \n\tzanr: %s \n\tpocet stran: %d \n\trok vydani: %d\n", databaze->prvky[s-1].nazev, databaze->prvky[s-1].autor, databaze->prvky[s-1].zanr, databaze->prvky[s-1].pocetStran, databaze->prvky[s-1].rokVydani);

        anoNe = ziskVolby("\nje tohle spravne? [A/N] ");
        if(anoNe!='A'){
            printf("koncim mazani/obnovu");
        } else {
            databaze->prvky[s-1].jeSmazano=!databaze->prvky[s-1].jeSmazano;
            if(databaze->prvky[s-1].jeSmazano==1){
            printf("\nzaznam %d bude smazan po ulozeni zmen",s);
            } else {
            printf("\nzaznam %d bude obnoven po ulozeni zmen",s);
            }
        }
    }
    //pro vraceni k menu
    stiskneteEnter();
}

void QSswap(KNIHA *a, KNIHA *b){
    KNIHA c=*a;
    *a=*b;
    *b=c;
}

int QSsortRok(KDATABAZE * a,int l,int r){
    int i=l;
    int pVal=a->prvky[r].rokVydani;
    for(int j=l;j<r;j++){
        if(a->prvky[j].rokVydani<=pVal){
            QSswap(&a->prvky[j],&a->prvky[i]);
            i++;
        }
    }
    QSswap(&a->prvky[i],&a->prvky[r]);
    return i;
}

void QSrecRok(KDATABAZE * a,int l, int r){
    if(l<r){
        int pivot = QSsortRok(a,l,r);
        QSrecRok(a,l,pivot-1);
        QSrecRok(a,pivot+1,r);
    }
}

void sortDatabazeRok(KDATABAZE * a){
    QSrecRok(a,0,(a->pocetZaznamu-1));
}

void dostanString(char * string){
    int zmena=0;
    scanf(" %255[^\n]", string);
        for(int i=0;string[i]!='\0';i++){
            if(string[i]==','){
                string[i]=' ';
                zmena=1;
            }
        }
    if(zmena==1){
        printf("carky byly premeneny na mezery\n");
    }
}

void opravaZaznamu(KDATABAZE * databaze){
    int vyb;
    char anoNe;
    printf("zadejte cislo knihy, kterou chcete opravit: ");
    scanf("%d",&vyb);
    if( (vyb<1) || ( vyb>(databaze->pocetZaznamu) ) ){
        printf("\ncislo moc male nebo moc velke, rusim opravu..");
    } else {
        printf("\nvybrali jste si opravit zaznam %d:", vyb);
        tiskZaznamu(databaze->prvky[vyb-1]);
        anoNe = ziskVolby("\nje tohle spravne? [A/N] ");
        if(anoNe!='A'){
            printf("koncim mazani.. \n");
        } else {
        printf("\nzadejte postupne nove hodnoty knihy,");
        printf("\nnovy nazev: ");
            dostanString(databaze->prvky[vyb-1].nazev);
        printf("\nnovy autor: ");
            dostanString(databaze->prvky[vyb-1].autor);
        printf("\nnovy zanr: ");
            dostanString(databaze->prvky[vyb-1].zanr);
        printf("\nnovy pocet stran: ");
            dostanInt(&databaze->prvky[vyb-1].pocetStran);
        printf("\nnovy rok vydani: ");
            dostanInt(&databaze->prvky[vyb-1].rokVydani);
        printf("\nzaznam bude zmenen po ulozeni zmen");
        }
    }
    stiskneteEnter();
}

void novyZaznam(KDATABAZE *databaze){
    printf("zadejte postupne hodnoty nove knihy,");
        printf("\nnovy nazev: ");
            dostanString(databaze->prvky[databaze->pocetZaznamu].nazev);
        printf("\nnovy autor: ");
            dostanString(databaze->prvky[databaze->pocetZaznamu].autor);
        printf("\nnovy zanr: ");
            dostanString(databaze->prvky[databaze->pocetZaznamu].zanr);
        printf("\nnovy pocet stran: ");
            dostanInt(&databaze->prvky[databaze->pocetZaznamu].pocetStran);
        printf("\nnovy rok vydani: ");
            dostanInt(&databaze->prvky[databaze->pocetZaznamu].rokVydani);
        printf("\nzaznam bude zmenen po ulozeni zmen");
        (databaze->pocetZaznamu)++;
}

void ulozZmeny(KDATABAZE * databaze){

  FILE * f = fopen("test2.txt","w");
  if(f==NULL){
        printf("databaze se nedala ulozit, koncim s ulozenim zmen..");
        fclose(f);
    }

    for(int i=0;i<(databaze->pocetZaznamu);i++){
        if(databaze->prvky[i].jeSmazano==0){
        fprintf(f,"%s, %s, %s, %d, %d\n", databaze->prvky[i].nazev, databaze->prvky[i].autor, databaze->prvky[i].zanr, databaze->prvky[i].pocetStran, databaze->prvky[i].rokVydani);
        }
    }
    fclose(f);


    FILE * f2 = fopen("test2.txt","r");
    if(f2==NULL){
        printf("databaze se nedala znovu nacist..");
        fclose(f2);
        exit(100);
    }
  int err = nacteniDatabaze(f2,databaze);
    fclose(f2);
    if(err!=0){
        printf("databaze se nedala znovu nacist..");
        exit(110);
    }

    printf("ulozeno sefe");
    stiskneteEnter();
}

typedef void (*fcePtr)(KDATABAZE*);

typedef struct{
    char text[256];
    char pismeno;
    fcePtr funkce;
} MPOLOZKA;

void tiskMenu(MPOLOZKA menu[]){
    for(int i=0; menu[i].funkce!=NULL;i++){
        printf("[%c] %s\n", menu[i].pismeno, menu[i].text);
    }
    printf("[Q] konec programu");
}

void menuVolba(MPOLOZKA menu[], KDATABAZE * databaze, char nadpisek[]){
    char c;
    do{
        printf("\033[1;1H\e[2J");
        printf("%s\n",nadpisek);
        tiskMenu(menu);
        c = ziskVolby("\n\nzadejte vasi volbu: ");
        if(c=='Q'){
            break;
        }
        for(int i=0; menu[i].funkce!=NULL;i++){
            if(c==menu[i].pismeno){
                printf("\n");
                menu[i].funkce(databaze);
            }
        }
    }while(true);
}

int main(void)
{
  KDATABAZE databaze;
  FILE * f = fopen("test2.txt","r");

  if(f==NULL){
        printf("databaze se nedala nacist, nechyby vam nahodou databaze? koncim..");
        fclose(f);
        return 1;
    }
  int err = nacteniDatabaze(f,&databaze);
    fclose(f);
    if(err!=0){
    return 1;
    }

    MPOLOZKA menu[]= {
    {.text="tisk databaze", .pismeno='T', .funkce=tiskDatabaze},
    {.text="smazani/obnova zaznamu",.pismeno='D',.funkce=smazaniObnovaZaznamu},
    {.text="oprava zaznamu",.pismeno='O',.funkce=opravaZaznamu},
    {.text="novy zaznam",.pismeno='N',.funkce=novyZaznam},
    {.text="ulozit zmeny",.pismeno='U',.funkce=ulozZmeny},
    {.text="0",.pismeno='0',.funkce=NULL},
    };

    menuVolba(menu,&databaze,"DATABAZE KNIH V1:");
    /*
    todo:
    add sorting (by year and pagecount)
    add searching - multiple choices, linear
    add summing
    sort functions into headers - database and menu
    move functions under main and make function pointers
    */


  return 0;
}
