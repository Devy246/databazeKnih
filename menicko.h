#ifndef MENICKO_H_INCLUDED
#define MENICKO_H_INCLUDED
#include <stdbool.h>
#include "databazeK.h"

char ziskVolby(char * text);

typedef void (*fcePtr)(KDATABAZE*);

typedef struct{
    char text[256];
    char pismeno;
    fcePtr funkce;
} MPOLOZKA;

void tiskMenu(MPOLOZKA menu[]);

void menuVolba(MPOLOZKA menu[], KDATABAZE * databaze, char nadpisek[], char podpisek[],bool * neulozeneZmeny);
#endif // MENICKO_H_INCLUDED
