#ifndef SORTDATABAZE_H_INCLUDED
#define SORTDATABAZE_H_INCLUDED
#include <stdbool.h>
#include "databazeK.h"

void QSsortDat(KDATABAZE *databaze, char volb[], bool vzes);

void QSsortRek(KDATABAZE * databaze,int l, int r, char volb[], bool vzes);

void QSswap(KNIHA *a, KNIHA *b);

int QSsortRozdel(KDATABAZE * databaze, int l, int r, char volb[],bool vzes);

int jeVetsi(KNIHA a, KNIHA b,char volb[]);

#endif
