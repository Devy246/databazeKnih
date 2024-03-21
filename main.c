/*
 * Projekt: databazeKnih
 * Autor: David Horák
 * Datum: XX-XX-2024
 */

#include "gvid.h"       // par drobnosti pro zjednoduseni prace
#include <stdio.h>
#include <stdlib.h>
// #include <string.h>  // pro praci s textovymi retezci
// #include <stdbool.h> // pro praci s typem bool a konstantami true a false
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
} KNIHA;

void tiskZaznamu(KNIHA zaznam){
    printf("\n\tnazev: %s \n\tautor: %s \n\tzanr:  %s \n\tpocet stran: %d \n\trok vydani: %d\n", zaznam.nazev, zaznam.autor, zaznam.zanr, zaznam.pocetStran, zaznam.rokVydani);
}

void tiskDatabaze(KNIHA databaze[], int pocet){
    for(int i=0;i<pocet;i++){
        printf("%3d: ",i+1);
        tiskZaznamu(databaze[i]);
    }
    switch(pocet){
    case 1:
        printf("\n\t%d kniha v databazi\n",pocet);
        break;
    case 2:
        printf("\n\t%d knihy v databazi\n",pocet);
        break;
    case 3:
        printf("\n\t%d knihy v databazi\n",pocet);
        break;
    case 4:
        printf("\n\t%d knihy v databazi\n",pocet);
        break;
    default:
        printf("\n\t%d knih v databazi\n",pocet);
        break;
    }
}

int nacteniDatabaze(KNIHA databaze[], int * pocetZaznamu){
    FILE *f = fopen("test2.txt","r");
    if(f==NULL){
        printf("databaze se nedala nacist, nechyby vam nahodou databaze? koncim..");
        fclose(f);
        return 1;
    } else {
        int e; KNIHA temp;
        while((e=fscanf(f,"%255[^,], %255[^,], %255[^,], %d, %d\n", temp.nazev, temp.autor, temp.zanr, &temp.pocetStran, &temp.rokVydani))==5){
            (*pocetZaznamu)++;
            if(*pocetZaznamu>MAXZaznamu){
                printf("maximalni pocet knih dosazen, vic uz nenacitam");
                (*pocetZaznamu)--;
                break;
            }
            databaze[(*pocetZaznamu)-1] = temp;
        }
        // -1 ==eof, 4 znamena ze se nacetlo spravne, ale dosahlo to maximalniho poctu prvku
        if(e!=-1 && e!=5){
            printf("jejdanenky! nastala chyba v formatu databaze, omrknete to prosimvas..");
            fclose(f);
            return 1;
        } else {
            fclose(f);
            return 0;
        }

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

int main(void)
{
  KNIHA databaze[MAXZaznamu];
  int pocetZaznamu = 0;
  int err = nacteniDatabaze(databaze,&pocetZaznamu);
      if(err!=0){
        return 1;
      }

  tiskDatabaze(databaze,pocetZaznamu);
  smazaniZaznamu(databaze,&pocetZaznamu);
  tiskDatabaze(databaze,pocetZaznamu);
  return 0;
}
