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
} KNIHA;

int nacteniDatabaze(KNIHA databaze[], int * pocetZaznamu){
    FILE *f = fopen("test1.txt","rw");
    if(f==NULL){
        printf("databaze se nedala nacist, nechyby vam nahodou databaze.txt? koncim..");
        return 1;
    } else {
        int e; KNIHA temp;
        while((e=fscanf(f,"%255[^,], %255[^,], %255[^,], %d\n", temp.nazev, temp.autor, temp.zanr, &temp.pocetStran))==4){
            (*pocetZaznamu)++;
            if(*pocetZaznamu>MAXZaznamu){
                printf("maximalni pocet knih dosazen, vic uz nenacitam");
                (*pocetZaznamu)--;
                break;
            }
            databaze[(*pocetZaznamu)-1] = temp;
        }
        // -1 ==eof, 4 znamena ze se nacetlo spravne, ale dosahlo to maximalniho poctu prvku
        if(e!=-1 && e!=4){
            printf("jejdanenky! nastala chyba v formatu databaze, omrknete to prosimvas..");
            return 1;
        } else {
            return 0;
        }

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

  printf("pocet zaznamu: %d",pocetZaznamu);
  for(int i=0;i<pocetZaznamu;i++){
    printf("\n%d: %s, %s, %s, %d", i, databaze[i].nazev,databaze[i].autor,databaze[i].zanr,databaze[i].pocetStran);
  }

  return 0;
}
