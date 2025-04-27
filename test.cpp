//Plik testowy - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include"funkcje.hpp"
#include<iostream>
#include<cassert>
using namespace std;

int main(){
    pasjans test(false);
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
    return 0;
}