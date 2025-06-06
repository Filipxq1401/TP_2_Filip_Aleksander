#pragma once
#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
class karta
{
private:
    int symbol; //symbol - jednostka karty, czyli A,1,2,3,4,5,6,7,8,9,J,Q,K
    int znak_koloru; //znak koluru czyli pik (♠), trefl (♣), kier (♥) oraz karo (♦)
    bool kolor; //kolor znaku czyli dla piku i trefla (czarnych) true , a dla kieru i karo (czerwone) false
    // karta 0 i 0 jest pustym polem
public:
    karta(const int symbol_poczatkowy,const int kolor_poczatkowy);
    int getSymbol() const;
    int getZnakKoloru() const;
    bool getKolor() const;
    bool pusta() const;
    void zmienKarte(const int symbol_docelowy,const int kolor_docelowy);
    std::string wyswietl() const;
};
struct ruch
{
    int typ_pola_1,typ_pola_2;
    int numer_pola_1,numer_pola_2;
};
ruch dekoduj(const std::string komenda,bool& poprawnosc);


class pasjans
{
private:
    std::vector<std::vector<karta> > pola_gry;
    std::vector<karta> pola_docelowe;
    std::vector<karta> pola_pomocnicze;
    bool czy_cls;
public:
    pasjans();
    void rozdajKraty();
    bool czyJestRuch() const;
    void wyswietl_ladne() const; 
    bool czyKoniec() const;
    bool czyRuchJestdozwolony(const ruch potencjalny) const;
    void wykonajRuch(const ruch dobry_ruch);
    void ustawCls(const bool czyszczenie);
    std::vector<std::vector<karta> > getPola_gry() const;
    void wczytaj_talie(const std::vector<std::vector<karta> > gry, const std::vector<karta> docelowe, const std::vector<karta> pomocnicze);
};
void tasuj(pasjans& gra);