//Plik z funkcajmi i klasami - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include "funkcje.hpp"

karta::karta(const int symbol_poczatkowy, const int kolor_poczatkowy){
    symbol = symbol_poczatkowy;
    znak_koloru = kolor_poczatkowy;
    if(znak_koloru<=2) kolor = true;
    else kolor = false;
}
bool karta::getKolor() const{
    return kolor;
}
int karta::getSymbol() const{
    return symbol;
}
int karta::getZnakKoloru() const{
    return znak_koloru;
}
void karta::zmienKarte(const int symbol_docelowy,const int kolor_docelowy){
    symbol = symbol_docelowy;
    znak_koloru = kolor_docelowy;
    if(znak_koloru<=2) kolor = true;
    else kolor = false;
}
void karta::wyswietl() const{
    if(symbol == 0 && kolor == 0){
        std::cout<<"  ";
        return;
    }
    if(!kolor) std::cout<<"\033[31m";
    if(symbol == 1) std::cout<<"A";
    else if(symbol == 10) std::cout<<"J";
    else if(symbol == 11) std::cout<<"Q";
    else if(symbol == 12) std::cout<<"K";
    else std::cout<<symbol;

    if(znak_koloru == 1) std::cout<<"♠";
    else if(znak_koloru == 2) std::cout<<"♣";
    else if(znak_koloru == 3) std::cout<<"♥";
    else std::cout<<"♦";
    if(!kolor) std::cout<<"\033[0m";
}

pasjans::pasjans(){
    pola_gry.resize(8);
    karta puste_pole(0,0);
    for(int i=0;i<4;i++){
        pola_docelowe.push_back(puste_pole);
        pola_pomocnicze.push_back(puste_pole);
    }
    rozdajKraty(); //później trzeba zrobić z tymi thread i ref na wymagania dodatkowe
}

void pasjans::rozdajKraty(){
    std::vector<karta> talia;
    karta temp(1,1);
	for (int i = 1; i <= 12; i++){
		for (int j = 1; j <= 4; j++){
			temp.zmienKarte(i,j);
			talia.push_back(temp);
		}
	}
    srand(time(NULL));
    for(int i=0;i<8;i++){
        int ile_kart = 7;
        if(i>3) ile_kart--; //na pierwsze 4 pola gry po 7 kart, a na kolejne 4 6 kart
        for(int j=0;j<ile_kart;j++){
            int indeks = rand() % talia.size();
            talia[indeks].wyswietl();
            pola_gry[i].push_back(talia[indeks]);
            temp = talia[talia.size()-1];
            talia[talia.size()-1] = talia[indeks];
            talia[indeks] = temp;
            talia.pop_back();
        }
    }
}