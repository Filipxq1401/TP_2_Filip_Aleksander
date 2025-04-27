#pragma once
#include<vector>
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
    void zmienKarte(const int symbol_docelowy,const int kolor_docelowy);
    void wyswietl() const;
};


class pasjans
{
private:
    std::vector<std::vector<karta> > pola_gry;
    std::vector<karta> pola_docelowe;
    std::vector<karta> pola_pomocnicze;
public:
    pasjans();
    void rozdajKraty();

};
