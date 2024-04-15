/*
 * Projekt: databazeKnih
 * Autor: David Horák
 * Datum: XX-04-2024
 */

#include "gvid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include "databazeK.h"
#include "menicko.h"
#include "sortDatabaze.h"

char cesta[1024];
bool neulozeneZmeny = 0;
bool prvniOtevreni = 1;

//popisy funkci jsou pod main

void Vyhledavani(KDATABAZE * databaze);
void vyhledat(KDATABAZE * databaze, char str[], KNIHA por);
int rovnaSe(KNIHA a, char str[], KNIHA por);

void dostanInt(int * i);
void dostanString(char * string);
void stiskneteEnter(void);

void tiskZaznamu(KNIHA zaznam);
void tiskDatabaze(KDATABAZE * databaze);

int nacteniDatabaze(FILE *f, KDATABAZE * databaze);

void smazaniObnovaZaznamu(KDATABAZE * databaze);

void opravaZaznamu(KDATABAZE * databaze);

void novyZaznam(KDATABAZE *databaze);

void ulozZmeny(KDATABAZE * databaze);

void souhrn(KDATABAZE * databaze);

void seradDatabazi(KDATABAZE * databaze);

void otevriDatabazi(KDATABAZE * databaze);

//otevre databazi a vytiskne menu
int main(void)
{
  KDATABAZE databaze;
  databaze.pocetZaznamu=0;
  printf("\033[1;1H\e[2J");

  printf("########## DATABAZE KNIH ##########\n");

  otevriDatabazi(&databaze);
  prvniOtevreni=0;

    MPOLOZKA menu[]= {
    {.text="otevrit jinou databazi", .pismeno='J', .funkce=otevriDatabazi},
    {.text="tisk databaze", .pismeno='T', .funkce=tiskDatabaze},
    {.text="vyhledat zaznam v databazi",.pismeno='V',.funkce=Vyhledavani},
    {.text="novy zaznam",.pismeno='N',.funkce=novyZaznam},
    {.text="oprava zaznamu",.pismeno='O',.funkce=opravaZaznamu},
    {.text="smazani/obnova zaznamu",.pismeno='D',.funkce=smazaniObnovaZaznamu},
    {.text="seradit databazi",.pismeno='S',.funkce=seradDatabazi},
    {.text="souhrn knih v databazi",.pismeno='K',.funkce=souhrn},
    {.text="ulozit zmeny",.pismeno='U',.funkce=ulozZmeny},
    {.text="0",.pismeno='0',.funkce=NULL},
    };

    menuVolba(menu,&databaze,"########## DATABAZE KNIH ##########",cesta,&neulozeneZmeny);

  return 0;
}

//funkce pro otevreni databaze
void otevriDatabazi(KDATABAZE * databaze){
    FILE * f;
    int check1, check2;
    char volba;

    do{
    check1=0;
    volba = ziskVolby("Chcete otevrit existujici databazi nebo vyrobit novou? \n(s programem prichazi predem definovana databaze.txt) [E/N]: ");
    if(volba!='E' && volba!='N'){
        printf("neni moznost, zkuste znova\n");
        check1=1;
    }
  }while(check1==1);

  //otevreni databaze
  if(volba=='E'){
      printf("zadejte cestu databaze: ");
      do{
        check2=0;
        scanf("%1023s",cesta);
        while(getchar()!='\n');
        f = fopen(cesta,"r");
        if(f==NULL){
            check2=1;
            printf("spatna cesta, zkuste znova: ");
        }  else {
            check2=0;
        }
      }while(check2==1);
  } else { //vytvoreni databaze
      printf("zadejte cestu nove databaze: ");
      do{
        check2=0;
        scanf("%1023s",cesta);
        while(getchar()!='\n');
        f = fopen(cesta,"w");
        if(f==NULL){
            check2=1;
            printf("spatna cesta, zkuste znova: ");
        }  else {
            check2=0;
        }
      }while(check2==1);
  }

  int err = nacteniDatabaze(f,databaze);
    fclose(f);
    if(err!=0){
        printf("chyba pri nacitani databaze\n");
        }
  if(prvniOtevreni==0){
    stiskneteEnter();
  }
}

//funkce pro serazeni databaze
void seradDatabazi(KDATABAZE * databaze){
    char volb[16];
    printf("zadejte v poradi hodnoty, podle kterych chcete seradit databazi: ");
    printf("\n[1] nazev knihy\n[2] autor knihy\n[3] zanr knihy\n[4] pocet stran knihy\n[5] rok vydani knihy\n[0] zrusit serazeni\nvolba: ");

    scanf("%15s",volb);
    while(getchar()!='\n');
    int spatnyString=0;
    do{
        for(int i=0;volb[i]!='\0';i++){
            spatnyString=0;
            if(volb[i]<48 || volb[i]>53){
                spatnyString=1;
                printf("\nspatny input, zkuste znova");
                scanf("%15s",volb);
                while(getchar()!='\n');
                break;
            }
        }
    }while(spatnyString==1);

    for(int j=0;volb[j]!='\0';j++){
        if(volb[j]=='0'){
        printf("\nrusim serazovani");
        stiskneteEnter();
        return;
        }
    }

    int spatne=1;
    char volba;
    do{
        if(spatne==0){
            printf("špatná input, zkuste znova: ");
        }
        spatne=1;
        volba = ziskVolby("\nchcete seradit databazi vzestupne nebo sestupne? [V/S]: ");
        if (volba!='V'&&volba!='S'){
            spatne=0;
        }
    }while(volba!='V' && volba!='S');

    bool vzestupne=0;
    if(volba=='V'){
        vzestupne=1;
    }

    QSsortDat(databaze,volb,vzestupne);
    neulozeneZmeny=1;
    stiskneteEnter();
}


//funkce ktera vytiskne souhrn knih v databazi
void souhrn(KDATABAZE * databaze){
    int pps=0;
    int sps=0;
    for(int i=0;i<databaze->pocetZaznamu;i++){
        sps += databaze->prvky[i].pocetStran;
    }
    pps=sps/databaze->pocetZaznamu;
    printf("v databazi je %d knih, jejichz celkovy pocet stran je %d a prumerny pocet stran je %d",databaze->pocetZaznamu,sps,pps);
    stiskneteEnter();
}

//FUNKCE PRO VYHLEDAVANI
//funkce pro vyhledavani. zepta se, podle jakych polozek, a pote zavola funkci vyhledat
void Vyhledavani(KDATABAZE * databaze){
    char volb[16];
    printf("zadejte hodnoty, podle kterych chcete vyhledavat");
    printf("\n[1] nazev knihy\n[2] autor knihy\n[3] zanr knihy\n[4] pocet stran knihy\n[5] rok vydani knihy\n[0] zrusit vyhledavani\nvolba: ");

    scanf("%15s",volb);
    while(getchar()!='\n');
    int spatnyString=0;
    do{
        for(int i=0;volb[i]!='\0';i++){
            spatnyString=0;
            if(volb[i]<48 || volb[i]>53){
                spatnyString=1;
                printf("\nspatny input, zkuste znova: ");
                scanf("%15s",volb);
                while(getchar()!='\n');
                break;
            }
        }
    }while(spatnyString==1);

    KNIHA porovnavac;
    porovnavac.jeSmazano=0;

    for(int j=0;volb[j]!='\0';j++){
        if(volb[j]=='0'){
        printf("\nrusim vyhledavani");
        stiskneteEnter();
        return;
        }
    }

    for(int i=0;volb[i]!='\0';i++){
    switch(volb[i]){
    case '1':
        printf("\nzadejte nazev, podle ktereho chcete hledat: ");
        dostanString(porovnavac.nazev);
        while(getchar()!='\n');
        break;
    case '2':
        printf("\nzadejte autora, podle ktereho chcete hledat: ");
        dostanString(porovnavac.autor);
        while(getchar()!='\n');
        break;
    case '3':
        printf("\nzadejte zanr, podle ktereho chcete hledat: ");
        dostanString(porovnavac.zanr);
        while(getchar()!='\n');
        break;
    case '4':
        printf("\nzadejte pocet stran, podle ktereho chcete hledat: ");
        dostanInt(&porovnavac.pocetStran);
        break;
    case '5':
        printf("\nzadejte rok vydani, podle ktereho chcete hledat: ");
        dostanInt(&porovnavac.rokVydani);
        break;
    default:
        printf("\nnejak si zadal cislo 1-5 a zaroven jiny charakter, gratuluji, jdete studovat kvantove pocitace");
        exit(130);
        break;

    }
    }
    vyhledat(databaze,volb,porovnavac);
    stiskneteEnter();
}
//funkce vyhledat projde databazi, jestli se dve polozky rovnaji podle funkce rovnaSe, vytiskne ji
void vyhledat(KDATABAZE * databaze, char str[], KNIHA por){
    int pocetNaleznutych = 0;
    for(int i=0;i<databaze->pocetZaznamu;i++){
        if(rovnaSe(databaze->prvky[i],str,por)==1){
            printf("\n%d",i+1);
            tiskZaznamu(databaze->prvky[i]);
            pocetNaleznutych++;
        }
    }

    switch(pocetNaleznutych){
        case 1:
            printf("\nnasla se 1 polozka\n");
            break;
        case 2:
            printf("\nnasly se 2 polozky\n");
            break;
        case 3:
            printf("\nnasly se 3 polozky\n");
            break;
        case 4:
            printf("\nnasly se 4 polozky\n");
            break;
        default:
            printf("\nnaslo se %d polozek\n",pocetNaleznutych);
            break;
    }
}
//funkce rovna se vrati 1 jestli se dve polozky rovnaji podle zadanych polozek
int rovnaSe(KNIHA a, char str[], KNIHA por){
    int rovnaSe=1;

    for(int i=0;str[i]!='\0';i++){
        switch (str[i]){
            case '1':
                if(strcasecmp(a.nazev,por.nazev)!=0){
                    rovnaSe=0;
                }
                break;
            case '2':
                if(strcasecmp(a.autor,por.autor)!=0){
                    rovnaSe=0;
                }
                break;
            case '3':
                if(strcasecmp(a.zanr,por.zanr)!=0){
                    rovnaSe=0;
                }
                break;
            case '4':
                if(a.pocetStran!=por.pocetStran){
                    rovnaSe=0;
                }
                break;
            case '5':
                if(a.rokVydani!=por.rokVydani){
                    rovnaSe=0;
                }
                break;
            default:
                printf("????");
                break;
        }
        if(rovnaSe==0){
            break;
        }

    }
    return rovnaSe;
}


//funkce ktera ulozi zmeny, ktere nastali behem programu
void ulozZmeny(KDATABAZE * databaze){
  char odp = ziskVolby("Chcete ulozit zmeny do stejneho souboru nebo ulozit jako jiny?\n[S/J]: ");
  if(odp!='S' && odp!='J'){
    printf("rusim ulozeni");
    stiskneteEnter();
    return;
  } else {
    if(odp=='S'){
          FILE * f = fopen(cesta,"w");
          if(f==NULL){
            printf("databaze se nedala ulozit, koncim s ulozenim zmen..");
            fclose(f);
            return;
            }

            for(int i=0;i<(databaze->pocetZaznamu);i++){
                if(databaze->prvky[i].jeSmazano==0){
                fprintf(f,"%s, %s, %s, %d, %d\n", databaze->prvky[i].nazev, databaze->prvky[i].autor, databaze->prvky[i].zanr, databaze->prvky[i].pocetStran, databaze->prvky[i].rokVydani);
                }
            }
            fclose(f);

            neulozeneZmeny=0;
            FILE * f2 = fopen(cesta,"r");
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

            printf("zmeny ulozeny\n");
            stiskneteEnter();
    } else {
        int check;
        char novaCesta[1024];
        FILE * f;
        printf("zadejte cestu: ");
        do{
            check=0;

            scanf("%1023s",novaCesta);
            while(getchar()!='\n');
            f = fopen(novaCesta,"w");
            if(f==NULL){
                check=1;
                fclose(f);
                printf("spatna cesta, zkuste znova: ");
            }  else {
                fclose(f);
                check=0;
            }
        }while(check==1);
      strcpy(cesta,novaCesta);
      f = fopen(cesta,"w");
      for(int i=0;i<(databaze->pocetZaznamu);i++){
                if(databaze->prvky[i].jeSmazano==0){
                fprintf(f,"%s, %s, %s, %d, %d\n", databaze->prvky[i].nazev, databaze->prvky[i].autor, databaze->prvky[i].zanr, databaze->prvky[i].pocetStran, databaze->prvky[i].rokVydani);
                }
            }
        fclose(f);
        neulozeneZmeny=0;
            FILE * f2 = fopen(cesta,"r");
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

            printf("zmeny ulozeny\n");
            stiskneteEnter();
        }
    }
}


//funkce, ktera vytvori novy zaznam
void novyZaznam(KDATABAZE *databaze){
    (databaze->prvky) = (KNIHA*)realloc( (databaze->prvky) , (databaze->pocetZaznamu+1)*sizeof(KNIHA) );
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
        stiskneteEnter();
        neulozeneZmeny=1;
        (databaze->pocetZaznamu)++;
}


//funkce, ktera opravi zaznam
void opravaZaznamu(KDATABAZE * databaze){
    int vyb;
    char anoNe;
    printf("zadejte cislo knihy, kterou chcete opravit: ");

    int ck;
    do{
        ck=0;
        dostanInt(&vyb);
        if((vyb<1)||(vyb>(databaze->pocetZaznamu))){
            printf("spatne vstup, zkuste znova: ");
            ck=1;
        }
    }while(ck==1);

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
        neulozeneZmeny=1;
        }

    stiskneteEnter();
}


//funkce pro smazani nebo obnovu zaznamu
void smazaniObnovaZaznamu(KDATABAZE * databaze){
    int s;
    char anoNe;
    printf("zadejte cislo knihy v zaznamu, ktery chcete smazat/obnovit: ");

    int ck;
    do{
        ck=0;
        dostanInt(&s);
        if((s<1)||(s>(databaze->pocetZaznamu))){
            printf("spatne vstup, zkuste znova: ");
            ck=1;
        }
    }while(ck==1);

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
            neulozeneZmeny=1;
        }

    //pro vraceni k menu
    stiskneteEnter();
}


//funkce pro nacteni databaze, pri ulozeni zmen a na zacatku programu
int nacteniDatabaze(FILE *f, KDATABAZE * databaze){
    databaze->pocetZaznamu = 0;
    (databaze->prvky) = (KNIHA*)malloc( 1*sizeof(KNIHA) );

        int e; KNIHA temp;
        KNIHA * tempPole;

        while((e=fscanf(f,"%255[^,], %255[^,], %255[^,], %d, %d\n", temp.nazev, temp.autor, temp.zanr, &temp.pocetStran, &temp.rokVydani))==5){
            temp.jeSmazano = 0;
            (tempPole) = (KNIHA*)realloc( (databaze->prvky) , (databaze->pocetZaznamu+1)*sizeof(KNIHA) );
                    if(tempPole==NULL){
                        printf("error pri alokaci");
                        return 1;
                    }
            databaze->prvky = tempPole;
            databaze->pocetZaznamu++;
            databaze->prvky[(databaze->pocetZaznamu)-1] = temp;
        }

        // -1 ==eof, 5 znamena ze se nacetlo spravne, ale dosahlo to maximalniho poctu prvku
        if(e!=-1 && e!=5){
            printf("jejdanenky! nastala chyba v formatu databaze, omrknete to prosimvas..");
            return 2;
        } else {
            return 0;
        }
}

//FUNKCE PRO TISK
//funkce, ktera vytiskne databazi
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
//funkce, ktera vytiskne jeden zaznam v databazi
void tiskZaznamu(KNIHA zaznam){
    printf("\n\tnazev: %s \n\tautor: %s \n\tzanr: %s \n\tpocet stran: %d \n\trok vydani: %d\n", zaznam.nazev, zaznam.autor, zaznam.zanr, zaznam.pocetStran, zaznam.rokVydani);
    if(zaznam.jeSmazano==1){
            printf("\t[PO UKLADANI ZMEN BUDE TENTO ZAZNAM SMAZAN]\n");
        }
}


//FUNKCE PRO ZISKANI INPUTU
//funkce, ktera donuti uzivate stisknout enter pro vraceni k menu
void stiskneteEnter(void){
    printf("\nstistknete enter pro vraceni k menu...");
    getchar();
}
//funkce pro spravnee ziskani intu
void dostanInt(int * i){
    int ck=0;
    do{
        ck = scanf(" %d",i);
        while(getchar()!='\n');
        if(ck!=1){
            printf("spatne vstup, zkuste znova: ");
        }
    }while(ck!=1);
}
//funkce, ktera dostane od uzivatele string ve spravnem formatu
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
