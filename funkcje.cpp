//Plik z funkcajmi i klasami - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
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
bool karta::pusta() const{
    if(symbol == 0 && znak_koloru == 0) return true;
    else return false;
}
void karta::zmienKarte(const int symbol_docelowy,const int kolor_docelowy){
    symbol = symbol_docelowy;
    znak_koloru = kolor_docelowy;
    if(znak_koloru<=2) kolor = true;
    else kolor = false;
}
//test
void karta::wyswietl() const{
    if(pusta()){
        std::cout<<"  ";
        return;
    }
    if(!kolor) std::cout<<"\033[31m";
    if(symbol == 1) std::cout<<" A";
    else if(symbol == 11) std::cout<<" J";
    else if(symbol == 12) std::cout<<" Q";
    else if(symbol == 13) std::cout<<" K";
    else if(symbol == 10) std::cout<<symbol;
    else std::cout<<" "<<symbol;

    if(znak_koloru == 1) std::cout<<"♠";
    else if(znak_koloru == 2) std::cout<<"♣";
    else if(znak_koloru == 3) std::cout<<"♥";
    else std::cout<<"♦";
    if(!kolor) std::cout<<"\033[0m";
}

pasjans::pasjans(const bool czy_czyscic){
    czy_cls = czy_czyscic;
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
	for (int i = 1; i <= 13; i++){
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
            if(talia.size()==1){ 
                pola_gry[i].push_back(talia[0]);
                break;
            }
            int indeks = rand() % talia.size();
            //talia[indeks].wyswietl();
            pola_gry[i].push_back(talia[indeks]);
            temp = talia[talia.size()-1];
            talia[talia.size()-1] = talia[indeks];
            talia[indeks] = temp;
            talia.pop_back();
        }
    }
}
void pasjans::wyswietl_testowe() const{
    if(czy_cls) system("cls");
    std::cout<<"Pola docelowe: "<<std::endl;
    for(int i=0;i<4;i++){
        std::cout<<"D"<<i+1<<": ";
        pola_docelowe[i].wyswietl();
        std::cout<<"    ";
    }
    std::cout<<std::endl<<"Pola pomocnicze: "<<std::endl;
    for(int i=0;i<4;i++){
        std::cout<<"P"<<i+1<<": ";
        pola_pomocnicze[i].wyswietl();
        std::cout<<"    ";
    }
    std::cout<<std::endl;
    for(int i=0;i<8;i++){
        std::cout<<"Pole Gry G"<<i+1<<" (ilość kart: "<<pola_gry[i].size()<<"): ";
        for(int j=0;j<pola_gry[i].size();j++){
            pola_gry[i][j].wyswietl();
            std::cout<<" ";
        }
        std::cout<<std::endl;
    }
}
bool pasjans::czyJestRuch() const{
    for(int i=0;i<4;i++){ //czy jest jakieś pole pomocnicze puste
        if(pola_pomocnicze[i].pusta()) return true;
    }
    for(int i=0;i<8;i++){ //czy jest jakieś pole gry puste
        if(pola_gry[i].size()==0) return true;
    }
    for(int i=0;i<4;i++){ //czy z jakiegoś pola pomocniczego można przenieś na jakieś pole gry 
        for(int j=0;j<8;j++){
            if(pola_pomocnicze[i].getKolor() != pola_gry[j].back().getKolor() && pola_gry[j].back().getSymbol() - pola_pomocnicze[i].getSymbol() == 1) return true;
        }
    }
    for(int i=0;i<4;i++){ //czy z jakiegoś pola pomocniczego można przenieść na pole doelowe
        for(int j=0;j<4;j++){
            if(pola_docelowe[j].pusta()){
                if(pola_pomocnicze[i].getSymbol()==1) return true;
            }
            else{
                if(pola_docelowe[j].getZnakKoloru()==pola_pomocnicze[i].getZnakKoloru() && pola_pomocnicze[i].getSymbol()-pola_docelowe[j].getSymbol()==1) return true;
            }
        }
    }
    for(int i=0;i<8;i++){ //czy z jakiegoś pola gry można przenieść na pole docelowe
        for(int j=0;j<4;j++){
            if(pola_docelowe[j].pusta()){
                if(pola_gry[i].back().getSymbol()==1) return true;
            }
            else{
                if(pola_docelowe[j].getZnakKoloru()==pola_gry[i].back().getZnakKoloru() && pola_gry[i].back().getSymbol()-pola_docelowe[j].getSymbol()==1) return true;
            }
        }
    }
    for(int i=0;i<8;i++){ //czy z jakiegoś pola gry można przenieść na inne pole gry
        for(int j=0;j<8;j++){
            if(i==j) continue;
            if(pola_gry[i].back().getKolor()!=pola_gry[j].back().getKolor() && pola_gry[j].back().getSymbol()-pola_gry[i].back().getSymbol()==1) return true;
        }
    }
    return false;
}