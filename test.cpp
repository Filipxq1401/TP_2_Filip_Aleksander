//Plik testowy - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include"funkcje.hpp"
#include<iostream>
#include<cassert>
using namespace std;

int main(){
    system("chcp 65001");
    pasjans test;
    test.ustawCls(false);
    test.rozdajKraty();

    //test czy po potasowaniu są wszystkie karty i się nie powtarzają
    std::vector<std::vector<karta> > potasowane_karty = test.getPola_gry();
    int ilosc_kart = 0;
    for(int i=0;i<potasowane_karty.size();i++) ilosc_kart += potasowane_karty[i].size();
    assert(ilosc_kart == 52);

    bool tablica[13][4];
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++) tablica[i][j] = false;
    }
    for(int i=0;i<potasowane_karty.size();i++){
        for(int j=0;j<potasowane_karty[i].size();j++){
            tablica[potasowane_karty[i][j].getSymbol()-1][potasowane_karty[i][j].getZnakKoloru()-1] = true;
        }
    }

    bool czy_wszystkie = true;
    for(int i=0;i<13;i++){
        for(int j=0;j<4;j++){
            if(tablica[i][j]==false){
                czy_wszystkie = false;
                break;
            }
        }
    }
    assert(czy_wszystkie == true);

    //test przegrania
    std::vector<std::vector<karta> > pola_gry;
    std::vector<karta> pola_docelowe;
    std::vector<karta> pola_pomocnicze;
    pola_gry.resize(8);
    for(int i=0;i<8;i++) pola_gry[i].push_back(karta(1,1));
    pola_gry[0].push_back(karta(2,1));
    pola_docelowe.resize(4,karta(1,1));
    pola_pomocnicze.resize(4,karta(1,1));
    test.wczytaj_talie(pola_gry,pola_docelowe,pola_pomocnicze);
    //dostępny tylko 1 ruch
    assert(test.czyJestRuch()==true);
    ruch testowy{0,2,0,0};
    //ruch testowy jest legalny
    assert(test.czyRuchJestdozwolony(testowy));
    //Po wykonaniu ruch testowy powinno nie być już innych ruchów
    test.wykonajRuch(testowy);
    assert(test.czyJestRuch()==false);
    //Teraz ruch testowy powinnen być nie legalny
    assert(test.czyRuchJestdozwolony(testowy)==false);

    //test wygrania
    pola_gry.clear();
    pola_gry.resize(8);
    pola_gry[1].push_back(karta(13,1));
    for(int i=0;i<4;i++){
        pola_docelowe[i] = karta(13,i+1);
        pola_pomocnicze[i] = karta(0,0);
    }
    pola_docelowe[0] = karta(12,1);
    test.wczytaj_talie(pola_gry,pola_docelowe,pola_pomocnicze);
    assert(test.czyKoniec() == false);
    assert(test.czyJestRuch() == true);
    testowy = {0,1,1,2};
    assert(test.czyRuchJestdozwolony(testowy)==true);
    test.wykonajRuch(testowy);
    assert(test.czyKoniec() == false);
    assert(test.czyJestRuch()==true);
    test.wyswietl_ladne();
    testowy = {1,2,2,0};
    assert(test.czyRuchJestdozwolony(testowy)==true);
    test.wykonajRuch(testowy);
    assert(test.czyKoniec() == true);
    return 0;
}