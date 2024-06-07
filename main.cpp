#include <ncurses.h>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#define ILOSCWIERSZY 19
#define ILOSCKOLUMN 50
#define ILOSCWIERSZYMENU 6
#define ILOSCKOLUMNMENU 26
#define ILOSCPOL 24

struct ekran_t{
    char mapa[ILOSCWIERSZY][ILOSCKOLUMN]={
            "##13#14#15#16#17#18####19#20#21#22#23#24###",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#                    |                    #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "#  %  %  %  %  %  %  |  %  %  %  %  %  %  #",
            "##12#11#10##9##8##7#####6##5##4##3##2##1###",};
    // dodanie mapy jako tablicy char
    char menu [ILOSCWIERSZYMENU][ILOSCKOLUMNMENU]={"#########################",
                                                   "# Zacznij gre           #",
                                                   "# Wczytaj gre           #",
                                                   "# Hall of fame          #",
                                                   "# Wyjdz z gry           #",
                                                   "#########################",};
    int opcja=1;
};
struct gra_t {
    int etapgry=0;
    int Xpionkowbialychnapolu[ILOSCPOL]={0,0,0,0,0,
                                         0,0,0,0,0,0,
                                         0,0,0,0,0,0,0,0,0,0,
                                         0,0,0};
    int Xpionkowczarnychnapolu[ILOSCPOL]={0,0,0,0,0,
                                          0,0,0,0,0,0,
                                          0,0,0,0,0,0,0,0,0,0,
                                          0,0,0};
    int pionkibialenabandzie=0;
    int pionkiczarnenabandzie=0;
    int ruchgracza=1;
    int kostka1=0;
    int kostka2=0;
    int iloscruchow=0;
    int ukostka1=0;
    int ukostka2=0;


};
int instrukbialybicie(struct ekran_t *ekran,struct gra_t *gra,int polez,int poledo)
{
   mvprintw(4, 70, "istnieje bicie");
           if(gra->ukostka1==0) mvprintw(7, 70, "Kostka 1: %d", gra->kostka1);
           if(gra->ukostka2==0) mvprintw(8, 70, "Kostka 2: %d", gra->kostka2);
            mvprintw(5, 70, "Podaj z jakiego pola chcesz przesunac pionka bialego:");
            move(6, 70);
            scanw("%d", &polez);
            mvprintw(9, 70, "Podaj na jakie pole chcesz przesunac pionka bialego:");
            move(10, 70);
            scanw("%d", &poledo);
};

int sprawdzczylegalnyruchczarnego(struct ekran_t *ekran,struct gra_t *gra,int polez,int poledo){
    if(poledo-1<polez-1){
        if(gra->Xpionkowczarnychnapolu[polez-1]>0){
            if(poledo==polez-gra->kostka1 || poledo==polez-gra->kostka2){
                if(gra->Xpionkowbialychnapolu[poledo-1]==0) return 1;
                else if(gra->Xpionkowbialychnapolu[poledo-1]==1) return 2;
                gra->iloscruchow--;
            }
            else if(poledo==polez-gra->kostka1-gra->kostka2) {
                if(gra->Xpionkowbialychnapolu[poledo-1]==0) return 3;
                else if(gra->Xpionkowbialychnapolu[poledo-1]==1) return 4;

            }

        }
    }else return 0;

}
int sprawdzczylegalnyruchbialego(struct ekran_t *ekran, struct gra_t *gra,int polez,int poledo){
    if(poledo-1>polez-1){
        if(gra->Xpionkowbialychnapolu[polez-1]>0){
            if(poledo==polez+gra->kostka1 || poledo==polez+gra->kostka2){
                if(gra->Xpionkowczarnychnapolu[poledo-1]==0) return 1;
                else if(gra->Xpionkowczarnychnapolu[poledo-1]==1) return 2;

            }
            else if(poledo==polez+gra->kostka1+gra->kostka2) {
                if(gra->Xpionkowczarnychnapolu[poledo-1]==0) return 3;
                else if(gra->Xpionkowczarnychnapolu[poledo-1]==1) return 4;

            }
        }
    }else return 0;
}
int rzutKostka(struct ekran_t *ekran, struct gra_t *gra) {
    int wynik = rand() % 6 + 1;

    return wynik;
}
int czyistniejebicieczarnego(struct ekran_t *ekran,struct gra_t *gra){
    int wynik=0;
    for(int i=0;i<ILOSCPOL;i++) {
        if (gra->Xpionkowczarnychnapolu[i] > 0) {
            if (gra->Xpionkowbialychnapolu[i - gra->kostka1] == 1 ||
                gra->Xpionkowbialychnapolu[i - gra->kostka2] == 1 ) {
                wynik = 1;
            }
            else if(gra->Xpionkowbialychnapolu[i- gra->kostka1]==0 || gra->Xpionkowbialychnapolu[i-gra->kostka2]==0){
                if(gra->Xpionkowbialychnapolu[i-gra->kostka1-gra->kostka2]==1){
                    wynik = 1;
                }
            }
        }
    }
    return wynik;
}
int czyistniejebiciebialego(struct ekran_t *ekran, struct gra_t *gra){
    int wynik=0;
    for(int i=0;i<ILOSCPOL;i++)
    {
        if (gra->Xpionkowbialychnapolu[i] > 0)
        {
            if (gra->Xpionkowczarnychnapolu[i + gra->kostka1] == 1 || gra->Xpionkowczarnychnapolu[i + gra->kostka2] == 1 )
            {
                wynik = 1;
            }
            else if(gra->Xpionkowczarnychnapolu[i+gra->kostka1+gra->kostka2]==1) {
                    wynik = 1;
            }

        }
    }
    return wynik;
}
int czyistniejeruchczarnego(struct ekran_t *ekran, struct gra_t *gra){
    int wynik=0;
    for(int i=0;i<ILOSCPOL;i++)
    {
        if (gra->Xpionkowczarnychnapolu[i] > 0) {
            if (gra->Xpionkowbialychnapolu[i - gra->kostka1-1] == 0 ||
                gra->Xpionkowbialychnapolu[i - gra->kostka2-1] == 0 ) {

                wynik = 1;
            }
        }
    }
    return wynik;
};
int czyistniejeruchbialego(struct ekran_t *ekran, struct gra_t *gra){
    int wynik=0;
    for(int i=0;i<ILOSCPOL;i++)
    {
        if (gra->Xpionkowbialychnapolu[i] > 0) {
            if (gra->Xpionkowczarnychnapolu[i + gra->kostka1] == 0 ||
                gra->Xpionkowczarnychnapolu[i + gra->kostka2] == 0 ) {

                wynik = 1;
            }
        }
    }
    return wynik;
};
void ruchbialego (struct ekran_t *ekran, struct gra_t *gra ){

        int polez = 0;
        int poledo = 0;

        if (czyistniejebiciebialego(ekran, gra) == 1) {
            instrukbialybicie(ekran,gra,polez,poledo);
            move(6, 70);
            scanw("%d", &polez);
            move(10, 70);
            scanw("%d", &poledo);
            if (sprawdzczylegalnyruchbialego(ekran, gra, polez, poledo) == 2) {
                gra->Xpionkowbialychnapolu[poledo - 1]++;
                gra->Xpionkowbialychnapolu[polez - 1]--;
                gra->Xpionkowczarnychnapolu[poledo - 1]--;
                gra->pionkiczarnenabandzie++;
                gra->iloscruchow--;
            }
            else if(sprawdzczylegalnyruchbialego(ekran,gra,polez,poledo)==4){
                gra->Xpionkowbialychnapolu[poledo - 1]++;
                gra->Xpionkowbialychnapolu[polez - 1]--;
                gra->Xpionkowczarnychnapolu[poledo - 1]--;
                gra->pionkiczarnenabandzie++;
                gra->iloscruchow-=2;
            }
            else ruchbialego(ekran, gra);
        } else if (czyistniejeruchbialego(ekran, gra) == 1) {
            mvprintw(4, 70, "nie ma bicia ale istnieje ruch");
            mvprintw(7, 70, "Kostka 1: %d", gra->kostka1);
            mvprintw(8, 70, "Kostka 2: %d", gra->kostka2);
            mvprintw(5, 70, "Podaj z jakiego pola chcesz przesunac pionka bialego:");
            move(6, 70);
            scanw("%d", &polez);
            mvprintw(9, 70, "Podaj na jakie pole chcesz przesunac pionka bialego:");
            move(10, 70);
            scanw("%d", &poledo);
            if (sprawdzczylegalnyruchbialego(ekran, gra, polez, poledo) == 1) {
                gra->Xpionkowbialychnapolu[poledo - 1]++;
                gra->Xpionkowbialychnapolu[polez - 1]--;
                gra->iloscruchow--;
            } else if (sprawdzczylegalnyruchbialego(ekran,gra,polez,poledo)==3){
                gra->Xpionkowbialychnapolu[poledo - 1]++;
                gra->Xpionkowbialychnapolu[polez - 1]--;
                gra->iloscruchow-=2;
            }
            else ruchbialego(ekran, gra);
        } else mvprintw(4, 70, "nie ma ruchu");
    }

void ruchczarnego (struct ekran_t *ekran, struct gra_t *gra){
        int polez=0;
        int poledo=0;

        if(czyistniejebicieczarnego(ekran,gra)==1){
            mvprintw(15,70,"istnieje bicie");
            mvprintw(16,70,"Kostka 1: %d",gra->kostka1);
            mvprintw(17,70, "Kostka 2: %d",gra->kostka2);
            mvprintw(18, 70,"Podaj z jakiego pola chcesz przesunac pionka czarnego:");
            move(19,70);
            scanw("%d",&polez);
            mvprintw(20,70, "Podaj na jakie pole chcesz przesunac pionka czarnego:");
            move(21,70);
            scanw("%d",&poledo);

            if (sprawdzczylegalnyruchczarnego(ekran,gra,polez,poledo)==2){
                gra->Xpionkowczarnychnapolu[poledo-1]++;
                gra->Xpionkowczarnychnapolu[polez-1]--;
                gra->Xpionkowbialychnapolu[poledo-1]--;
                gra->pionkibialenabandzie++;
                gra->iloscruchow--;
            }else if(sprawdzczylegalnyruchbialego(ekran,gra,polez,poledo)==4)
            {
                gra->Xpionkowczarnychnapolu[poledo-1]++;
                gra->Xpionkowczarnychnapolu[polez-1]--;
                gra->Xpionkowbialychnapolu[poledo-1]--;
                gra->pionkibialenabandzie++;
                gra->iloscruchow-=2;
            }
            else ruchczarnego(ekran,gra);
        }
        else if(czyistniejeruchczarnego(ekran,gra)==1){
            mvprintw(15,70,"nie ma bicia ale istnieje ruch");
            mvprintw(16,70,"Kostka 1: %d",gra->kostka1);
            mvprintw(17,70, "Kostka 2: %d",gra->kostka2);
            mvprintw(18,70,"Podaj z jakiego pola chcesz przesunac pionka czarnego:");
            move(19,70);
            scanw("%d",&polez);
            mvprintw(20,70, "Podaj na jakie pole chcesz przesunac pionka czarnego:");
            move(21,70);
            scanw("%d",&poledo);

            if(sprawdzczylegalnyruchczarnego(ekran,gra,polez,poledo)==1){
                    gra->Xpionkowczarnychnapolu[poledo-1]++;
                    gra->Xpionkowczarnychnapolu[polez-1]--;
                gra->iloscruchow--;
            }
            else if(sprawdzczylegalnyruchczarnego(ekran,gra,polez,poledo)==3){
                gra->Xpionkowczarnychnapolu[poledo-1]++;
                gra->Xpionkowczarnychnapolu[polez-1]--;
                gra->iloscruchow-=2;
            }

            else ruchczarnego(ekran,gra);

        }
    }
void resetujpola(struct ekran_t *ekran, struct gra_t *gra){
    for(int i=1;i<9;i++){
        for(int j=3;j<40;j+=3){

            if (j!=21) ekran->mapa[i][j]='%';
            else ekran->mapa[i][j]='|';
        }
    }
    for(int i=10;i<18;i++){
        for(int j=3;j<40;j+=3){

            if (j!=21) ekran->mapa[i][j]='%';
            else ekran->mapa[i][j]='|';
        }
    }
}
void ruch(struct ekran_t *ekran, struct gra_t *gra){
    gra->kostka1 = rzutKostka(ekran, gra);
    gra->kostka2 = rzutKostka(ekran, gra);
    if(gra->kostka1==gra->kostka2) gra->iloscruchow = 4;
    else gra->iloscruchow=2;
    while(gra->iloscruchow==0){
        if(gra->ruchgracza%2==0) ruchbialego;
        if(gra->ruchgracza%2==1) ruchczarnego;
    } gra->ruchgracza++;
}
void zaimplementujpionkinabande(struct ekran_t *ekran,struct gra_t *gra){
    for(int i=0;i<gra->pionkiczarnenabandzie;i++){
        ekran->mapa[1+i][21]='@';
    }
    for(int i=0;i<gra->pionkibialenabandzie;i++){
        ekran->mapa[17-i][21]='X';
    }
}
void zaiplementujbialepionkidomapy1(struct ekran_t *ekran,struct gra_t *gra){
    for(int i=0;i<gra->Xpionkowbialychnapolu[0];i++){
        ekran->mapa[17-i][39]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[1];i++){
        ekran->mapa[17-i][36]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[2];i++){
        ekran->mapa[17-i][33]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[3];i++){
        ekran->mapa[17-i][30]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[4];i++){
        ekran->mapa[17-i][27]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[5];i++){
        ekran->mapa[17-i][24]='X';
    }
}
void zaiplementujbialepionkidomapy2(struct ekran_t *ekran,struct gra_t *gra) {
    for (int i = 0; i < gra->Xpionkowbialychnapolu[6]; i++) {
        ekran->mapa[17 - i][18] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[7]; i++) {
        ekran->mapa[17 - i][15] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[8]; i++) {
        ekran->mapa[17 - i][12] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[9]; i++) {
        ekran->mapa[17 - i][9] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[10]; i++) {
        ekran->mapa[17 - i][6] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[11]; i++) {
        ekran->mapa[17 - i][3] = 'X';
    }
}
void zaiplementujbialepionkidomapy3(struct ekran_t *ekran,struct gra_t *gra) {
    for (int i = 0; i < gra->Xpionkowbialychnapolu[12]; i++) {
        ekran->mapa[i + 1][3] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[13]; i++) {
        ekran->mapa[i + 1][6] = 'X';
    }
    for (int i = 0; i < gra->Xpionkowbialychnapolu[14]; i++) {
        ekran->mapa[i + 1][9] = 'X';
    }

    for (int i = 0; i < gra->Xpionkowbialychnapolu[15]; i++) {
        ekran->mapa[i + 1][12] = 'X';
    }

    for (int i = 0; i < gra->Xpionkowbialychnapolu[16]; i++) {
        ekran->mapa[i + 1][15] = 'X';
    }

    for (int i = 0; i < gra->Xpionkowbialychnapolu[17]; i++) {
        ekran->mapa[i + 1][18] = 'X';
    }
}
void zaiplementujbialepionkidomapy4(struct ekran_t *ekran,struct gra_t *gra){
    for(int i=0;i<gra->Xpionkowbialychnapolu[18];i++){
        ekran->mapa[i+1][24]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[19];i++){
        ekran->mapa[i+1][27]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[20];i++){
        ekran->mapa[i+1][30]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[21];i++){
        ekran->mapa[i+1][33]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[22];i++){
        ekran->mapa[i+1][36]='X';
    }
    for(int i=0;i<gra->Xpionkowbialychnapolu[23];i++){
        ekran->mapa[i+1][39]='X';
    }

}
void zaiplementujczarnepionkidomapy1(struct ekran_t *ekran,struct gra_t *gra){
    for(int i=0;i<gra->Xpionkowczarnychnapolu[0];i++){
        ekran->mapa[17-i][39]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[1];i++){
        ekran->mapa[17-i][36]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[2];i++){
        ekran->mapa[17-i][33]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[3];i++){
        ekran->mapa[17-i][30]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[4];i++){
        ekran->mapa[17-i][27]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[5];i++){
        ekran->mapa[17-i][24]='@';
    }
}
void zaiplementujczarnepionkidomapy2(struct ekran_t *ekran,struct gra_t *gra) {
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[6]; i++) {
        ekran->mapa[17 - i][18] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[7]; i++) {
        ekran->mapa[17 - i][15] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[8]; i++) {
        ekran->mapa[17 - i][12] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[9]; i++) {
        ekran->mapa[17 - i][9] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[10]; i++) {
        ekran->mapa[17 - i][6] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[11]; i++) {
        ekran->mapa[17 - i][3] = '@';
    }
}
void zaiplementujczarnepionkidomapy3(struct ekran_t *ekran,struct gra_t *gra) {
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[12]; i++) {
        ekran->mapa[i + 1][3] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[13]; i++) {
        ekran->mapa[i + 1][6] = '@';
    }
    for (int i = 0; i < gra->Xpionkowczarnychnapolu[14]; i++) {
        ekran->mapa[i + 1][9] = '@';
    }

    for (int i = 0; i < gra->Xpionkowczarnychnapolu[15]; i++) {
        ekran->mapa[i + 1][12] = '@';
    }

    for (int i = 0; i < gra->Xpionkowczarnychnapolu[16]; i++) {
        ekran->mapa[i + 1][15] = '@';
    }

    for (int i = 0; i < gra->Xpionkowczarnychnapolu[17]; i++) {
        ekran->mapa[i + 1][18] = '@';
    }
}
void zaiplementujczarnepionkidomapy4(struct ekran_t *ekran,struct gra_t *gra){
    for(int i=0;i<gra->Xpionkowczarnychnapolu[18];i++){
        ekran->mapa[i+1][24]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[19];i++){
        ekran->mapa[i+1][27]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[20];i++){
        ekran->mapa[i+1][30]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[21];i++){
        ekran->mapa[i+1][33]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[22];i++){
        ekran->mapa[i+1][36]='@';
    }
    for(int i=0;i<gra->Xpionkowczarnychnapolu[23];i++){
        ekran->mapa[i+1][39]='@';
    }

}
bool koniecgry(struct ekran_t *ekran,struct gra_t *gra){
    return true;
}
void zapiszGre(struct ekran_t *ekran, struct gra_t *gra){
    FILE *plik = fopen("test.txt", "w");
    for (int i=0;i<ILOSCPOL;i++){
        fprintf(plik, "%d ", gra->Xpionkowbialychnapolu[i]);
    }
    fprintf(plik,"\n");
    for (int i=0;i<ILOSCPOL;i++){
        fprintf(plik, "%d ", gra->Xpionkowczarnychnapolu[i]);
    }
    fprintf(plik,"\n");
    fprintf(plik,"%d\n",gra->ruchgracza);
    fprintf(plik,"%d\n",gra->pionkibialenabandzie);
    fprintf(plik,"%d\n",gra->pionkiczarnenabandzie);
    fclose(plik);
    clear();
    endwin();
    exit(0);

}
void pozycjapoczakowa(struct ekran_t *ekran, struct gra_t *gra){
    gra->Xpionkowbialychnapolu[0]=2;
    gra->Xpionkowbialychnapolu[16]=3;
    gra->Xpionkowbialychnapolu[11]=5;
    gra->Xpionkowbialychnapolu[18]=5;
    gra->Xpionkowczarnychnapolu[12]=5;
    gra->Xpionkowczarnychnapolu[7]=3;
    gra->Xpionkowczarnychnapolu[5]=5;
    gra->Xpionkowczarnychnapolu[23]=2;
}
void printmap(struct ekran_t *ekran, struct gra_t *gra){
    while(1) {
        char klawisz;
        resetujpola(ekran, gra);
        zaiplementujbialepionkidomapy1(ekran, gra);
        zaiplementujbialepionkidomapy2(ekran, gra);
        zaiplementujbialepionkidomapy3(ekran, gra);
        zaiplementujbialepionkidomapy4(ekran, gra);
        zaiplementujczarnepionkidomapy1(ekran, gra);
        zaiplementujczarnepionkidomapy2(ekran, gra);
        zaiplementujczarnepionkidomapy3(ekran, gra);
        zaiplementujczarnepionkidomapy4(ekran, gra);
        zaimplementujpionkinabande(ekran, gra);
        for (int i = 0; i < ILOSCWIERSZY; i++) {
            for (int j = 0; j < ILOSCKOLUMN; j++) {
                mvprintw(i + 10, j + 20, "%c", ekran->mapa[i][j]);
            }
        }
}
void przebieggry(struct ekran_t *ekran, struct gra_t *gra){
    printmap(ekran,gra);
    char klawisz;
     klawisz=getch();
        if (klawisz == 'X' || klawisz == 'x') {
            zapiszGre(ekran,gra);
        }
        else if(klawisz == 'Z' || klawisz == 'z'){
            clear();
            endwin();
            exit(0);
        }
        ruch(ekran, gra);
        clear();
        if (koniecgry(ekran, gra)) {
            przebieggry(ekran,gra);   
            }
    
}
void wybranaopcja(struct ekran_t *ekran, struct gra_t *gra){
    if(ekran->opcja==1){
        pozycjapoczakowa(ekran,gra);
        zaiplementujbialepionkidomapy1(ekran,gra);
        zaiplementujbialepionkidomapy2(ekran,gra);
        zaiplementujbialepionkidomapy3(ekran,gra);
        zaiplementujbialepionkidomapy4(ekran,gra);
        zaiplementujczarnepionkidomapy1(ekran,gra);
        zaiplementujczarnepionkidomapy2(ekran,gra);
        zaiplementujczarnepionkidomapy3(ekran,gra);
        zaiplementujczarnepionkidomapy4(ekran,gra);
        printmap(ekran,gra);
    }
    if(ekran->opcja==2){
        FILE *plik = fopen("test.txt", "r");
        for(int i=0;i<ILOSCPOL;i++){
            fscanf(plik,"%d",&gra->Xpionkowbialychnapolu[i]);
        }
        for(int i=0;i<ILOSCPOL;i++){
            fscanf(plik,"%d",&gra->Xpionkowczarnychnapolu[i]);
        }
        fscanf(plik,"%d",&gra->ruchgracza);
        fscanf(plik,"%d",&gra->pionkibialenabandzie);
        fscanf(plik,"%d",&gra->pionkiczarnenabandzie);
        zaiplementujbialepionkidomapy1(ekran,gra);
        zaiplementujbialepionkidomapy2(ekran,gra);
        zaiplementujbialepionkidomapy3(ekran,gra);
        zaiplementujbialepionkidomapy4(ekran,gra);
        zaiplementujczarnepionkidomapy1(ekran,gra);
        zaiplementujczarnepionkidomapy2(ekran,gra);
        zaiplementujczarnepionkidomapy3(ekran,gra);
        zaiplementujczarnepionkidomapy4(ekran,gra);
        printmap(ekran,gra);

    }
    else if(ekran->opcja==4){
        clear();
        endwin();
    }
}
bool wybierzopcje(struct ekran_t *ekran,struct gra_t *gra, int x){
    if(x==10){
        wybranaopcja(ekran,gra);
        return false;
    }
    else if(x==66 && ekran->opcja < 4){
        ekran->opcja+=1;
        return true;

    }
    else if(x==65 && ekran->opcja >1) {
        ekran->opcja -= 1;
        return true;
    }
    else return true;



}
void printmenu(struct ekran_t *ekran,struct gra_t *gra){



    for(int i=0;i < ILOSCWIERSZYMENU;i++)
    {
        for(int j=0;j<ILOSCKOLUMNMENU;j++){
            mvprintw(i+10,j+20,"%c",ekran->menu[i][j]);
        }
    }
    int ch =getch();
    mvprintw(0,0,"%d",ch);
    mvprintw(0,10,"Michal Matysiak nr indeksu 198395");
    if(wybierzopcje(ekran, gra,ch)){
        printmenu(ekran,gra);
    }
}
int main() {
    srand(time(NULL));
    struct ekran_t ekran;
    struct gra_t gra;
    initscr();
    printmenu(&ekran,&gra);
    endwin();
    return 0;
};