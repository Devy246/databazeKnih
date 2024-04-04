#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "menicko.h"
#include "databazeK.h"

char ziskVolby(char * text){
    printf("%s",text);
    char c;
    scanf(" %c",&c);
    c = toupper(c);
    while(getchar()!='\n');

    return c;
}

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
