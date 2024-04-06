# DatabazeKnih
---
## Úvod:
Účel programu databazeKnih je, aby si uživatel mohl uchovat databázi knih a s ní
pak i manipulovat. 
Program je určen pro lidi, kteří si potřebují uchovat databázi knih. Například
studenti, kteří si potřebují někam sepsat maturitní četbu, nebo vášnivý čtenáři
co si potřebují sepsat knihy, které přečetli/chtějí přečíst, a třeba zjistit,
kolik je to celkově stran.
## Účel programu:
Program pracuje se souborem databaze.txt, ve kterém program pracuje se záznamy
knih. Uživatel jednotlivé knihy může vyhledat/přidat/změnit/smazat, nebo celou
databázi seřadit a vytisknout. Také může zjistit počet knih a stran a také
průměrný počet stran. Jednotlivé knihy mají tyhle položky: název, jméno autora, 
žánr knihy, počet stran a rok vydání.
Řeší problém uchování si seznamu knih, třeba při výrobě nákupního seznamu pro
studenty vysokých škol.
## Hlavní funkcionality:
- ### klíčové funkce:
    - #### tiskDatabaze:
        - vytiskne celou databázi na obrazovku
    - #### Vyhledavani:
        - nechá uživatele vyhledat knihu více položkami pomocí lineárního 
        vyhledávání, jelikož binární by se dalo maximálně částečně implementovat
        a plně implementovat jen ve 2 z 3125 případů
    - #### novyZaznam:
        - nechá uživatele vytvořit nový záznam knihy
    - #### opravaZaznamu:
        - nechá uživatele zadat nové hodnoty existujícího záznamu
    - #### smazaniObnovaZaznamu:
        - označí vybraný soubor jako smazaný/nesmazaný, jelikož smazané položky
        nejsou během uložení napsány znovu do souboru
    - #### sortDatabaze:
        - seřadí databázi podle roku vydání nebo počtu stran pomocí quicksort,
        který byl vybrán jelikož autor projektu se ho zbytečně učil před pár 
        týdny, protože si myslel, že měl být na testu (nebyl)
    - #### ulozZmeny:
        - vypíše pole v paměti bez smazaných souborů a poté soubor dá znovu do 
        paměti 
- ### použité technologie:
    - C, git, github, Codeblocks a Neovim
## Omezení a známé problémy:
- program pracuje pouze s jedním souborem pro databázi, který nelze vyměnit za
jiný soubor (autor projektu byl moc líný aby to naprogramoval)
- nelze seřadit databáze podle více položek (autor projektu neměl čas tohle
naprogramovat kvůli čvrtletce z matematiky)
- názvy, autoři a žánry knih nemohou mít čárky v sobě a jsou automaticky změněny
na mezery (autor projektu byl moc líný aby změnil znak na oddělení položek 
v databázi)
- databáze nemůže mít víc položek, než je definováno při kompilaci (autor 
projektu byl moc líný se naučit jak používat realloc)
- databáze nemá opravdu knihy, jen základní informace o nich
- databáze nemůže mít unicode písmena ale pouze ASCII písmena
## Použití:
Po spuštění programu budete uvítáni s menu. Zadejte písmeno, které koresponduje
s nabídkou v seznamu (při chybném zadání budete vráceni zpět na menu). Poté vám 
program řekne dál, co zadat. Někdy jen musíte stisknout enter aby vás vrátil
zpět na menu, někdy bude chtít od vás zadat hodnoty knih nebo číslo záznamu.
Jednotlivé nabídky najdete výše v odstavci hlavní funkcionality.
## Příklady:
Příklady použití tohodle programu najdete výše v odstavci úvod a v odstavi účel
programu.
## Podpora a kontakt:
Pro podporu můžete otevřít problém na [githubu](https://www.github.com/Devy246/databazeKnih)
