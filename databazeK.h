#ifndef DATABAZEK_H_INCLUDED
#define DATABAZEK_H_INCLUDED
#include <stdbool.h>

typedef struct{
    char nazev[256];
    char autor[256];
    char zanr[256];
    int pocetStran;
    int rokVydani;
    bool jeSmazano;
} KNIHA;

typedef struct{
    KNIHA *prvky;
    int pocetZaznamu;
} KDATABAZE;

#endif // DATABAZEK_H_INCLUDED
