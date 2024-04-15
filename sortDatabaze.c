#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "databazeK.h"
#include <strings.h>

int jeVetsi(KNIHA a, KNIHA b,char volb[]){
    int aJeVetsi;
    for(int i=0;volb[i]!='\0';i++){
        switch(volb[i]){
            case '1':
                if( (aJeVetsi=strcasecmp(a.nazev,b.nazev))!=0){
                    return aJeVetsi;
                }
                break;
            case '2':
                if( (aJeVetsi=strcasecmp(a.autor,b.autor))!=0){
                    return aJeVetsi;
                }
                break;
            case '3':
                if( (aJeVetsi=strcasecmp(a.zanr,b.zanr))!=0){
                    return aJeVetsi;
                }
                break;
            case '4':
                if(a.pocetStran>b.pocetStran){
                    return 1;
                }
                if(a.pocetStran<b.pocetStran){
                    return -1;
                }
                break;
            case '5':
                if(a.rokVydani>b.rokVydani){
                    return 1;
                }
                if(a.rokVydani<b.rokVydani){
                    return -1;
                }
                break;
        }
    }
    return 0;
}

void QSswap(KNIHA *a, KNIHA *b){
    KNIHA c=*a;
    *a=*b;
    *b=c;
}

int QSsortRozdel(KDATABAZE * databaze, int l, int r, char volb[], bool vzes){
    int i=l;
    KNIHA pivot = databaze->prvky[r];
    for(int j=l;j<r;j++){
        if( !( (jeVetsi(databaze->prvky[j],pivot,volb)<1)^(vzes) )   ){
            QSswap(&databaze->prvky[j],&databaze->prvky[i]);
            i++;
        }
    }
    QSswap(&databaze->prvky[i],&databaze->prvky[r]);
    return i;
}

void QSsortRek(KDATABAZE * databaze,int l, int r, char volb[], bool vzes){
    if(l<r){
        int pivot=QSsortRozdel(databaze,l,r,volb,vzes);
        QSsortRek(databaze,l,pivot-1,volb,vzes);
        QSsortRek(databaze,pivot+1,r,volb,vzes);
    }
}

void QSsortDat(KDATABAZE *databaze, char volb[], bool vzes){
    QSsortRek(databaze,0,databaze->pocetZaznamu-1,volb,vzes);
}







