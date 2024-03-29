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
// #include <ctype.h>   // isalpha, isspace, islower, isupper, ...
// #include <math.h>    // funkce z matematicke knihovny
// #include <float.h>   // konstanty pro racionalni typy DBL_MAX, DBL_DIG, ...
// #include <limits.h>  // konstanty pro celociselne typy INT_MAX, INT_MIN, ...
// #include <time.h>    // funkce time a dalsi pro praci s casem
#define MAXZaznamu 512

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

void tiskZaznamu(KNIHA zaznam){
    printf("\n\tnazev: %s \n\tautor: %s \n\tzanr: %s \n\tpocet stran: %d \n\trok vydani: %d\n", zaznam.nazev, zaznam.autor, zaznam.zanr, zaznam.pocetStran, zaznam.rokVydani);
    if(zaznam.jeSmazano==1){
            printf("\tPO UKLADANI ZMEN BUDE SMAZAN\n");
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
}

int nacteniDatabaze(FILE *f, KDATABAZE * databaze){
    databaze->pocetZaznamu = 0;
    printf("zacalo nacteni databaze");
        int e; KNIHA temp;
        while((e=fscanf(f,"%255[^,], %255[^,], %255[^,], %d, %d\n", temp.nazev, temp.autor, temp.zanr, &temp.pocetStran, &temp.rokVydani))==5){
            printf("%d",e);
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

void smazaniZaznamu(KNIHA databaze[], int * pocetZaznamu){
    int s;
    printf("zadejte cislo knihy v zaznamu, ktery chcete smazat: ");
    scanf("%d",&s);
    if( (s<1) || (s>(*pocetZaznamu)) ){
        printf("\nzadane cislo knihy neexistuje, koncim smazani..");
    } else {
        s--;
        for(;s<(*pocetZaznamu);s++){
            databaze[s] = databaze[s+1];
        }
        (*pocetZaznamu)--;
    }
}

void QSswap(KNIHA *a, KNIHA *b){
    KNIHA c=*a;
    *a=*b;
    *b=c;
}

int QSsortRok(KNIHA a[],int l,int r){
    int i=l;
    int pVal=a[r].rokVydani;
    for(int j=l;j<r;j++){
        if(a[j].rokVydani<=pVal){
            QSswap(&a[j],&a[i]);
            i++;
        }
    }
    QSswap(&a[i],&a[r]);
    return i;
}

void QSrecRok(KNIHA a[],int l, int r){
    if(l<r){
        int pivot = QSsortRok(a,l,r);
        QSrecRok(a,l,pivot-1);
        QSrecRok(a,pivot+1,r);
    }
}

void sortDatabazeRok(KNIHA a[],int size){
    QSrecRok(a,0,size-1);
}
/*
void opravaZaznamu(KNIHA a[],int pocetZaznamu){
    int vyb;
    printf("\nzadejte cislo knihy, kterou chcete opravit: ");
    scanf("%d",&vyb);
    if( (vyb<1) || ( vyb>(pocetZaznamu-1) ) ){
        printf("\ncislo moc male nebo moc velke, rusim opravu..");
        break;
    } else {
        vyb--;
        tiskZaznamu(a[vyb]);
        printf("\nzadejte postupne nove hodnoty knihy,");
        printf("novy nazev: ");//doplnit
            scanf("%255[^,]", a[].nazev);
        printf("novy autor: ");
        printf("novy pocet stran:");
        printf("novy rok vydani: ");
    }
}*/


int main(void)
{
  printf("ahoj");
  KDATABAZE databaze;
  FILE * f = fopen("test2.txt","rw");

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

  tiskDatabaze(&databaze);
//  smazaniZaznamu(databaze,&pocetZaznamu);
//  tiskDatabaze(databaze,pocetZaznamu);

//  sortDatabazeRok(databaze,pocetZaznamu);
//if if  tiskDatabaze(databaze,pocetZaznamu);

  //opravaZaznamu(databaze,&pocetZaznamu);
  //tiskDatabaze(databaze,pocetZaznamu);
  return 0;
}
