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
std::string karta::wyswietl() const{
    std::string wyjscie = "";
    if(pusta()){
        return "  ";
    }
    if(!kolor) wyjscie += "\033[31m";
    if(symbol == 1) wyjscie +="A";
    else if(symbol == 11) wyjscie +="J";
    else if(symbol == 12) wyjscie +="Q";
    else if(symbol == 13) wyjscie +="K";
    else if(symbol == 10) wyjscie += "10";
    else wyjscie += (char)('0' + symbol);
    if(znak_koloru == 1) wyjscie +="♠";
    else if(znak_koloru == 2) wyjscie +="♣";
    else if(znak_koloru == 3) wyjscie +="♥";
    else wyjscie += "♦";
    if(!kolor) wyjscie +="\033[0m";
    return wyjscie;
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
            pola_gry[i].push_back(talia[indeks]);
            temp = talia[talia.size()-1];
            talia[talia.size()-1] = talia[indeks];
            talia[indeks] = temp;
            talia.pop_back();
        }
    }
}
void pasjans::wyswietl_ladne() const{
    if(czy_cls) system("cls");
    std::cout<<std::endl;
    std::cout<<"              Pola Pomocnicze:                                             Pola Docelowe:"<<std::endl;
    std::cout<<"   P1          P2          P3          P4                      D1          D2          D3          D4";
    std::vector<std::vector<std::string> > polonczone;
    polonczone.resize(8);
    for(int i=0;i<8;i++){
        polonczone[i].resize(5);
    }
    for(int i=0;i<4;i++){
        if(pola_pomocnicze[i].getSymbol()==0){
            polonczone[i][0]="┌──────┐";
            polonczone[i][1]="│      │";
            polonczone[i][2]="│      │";
            polonczone[i][3]="│      │";
            polonczone[i][4]="└──────┘";
        }
        else{
            polonczone[i][0] = "╔══════╗";
            polonczone[i][1] ="║" + pola_pomocnicze[i].wyswietl();
            polonczone[i][3] = "║   ";
            if(pola_pomocnicze[i].getSymbol()!=10){
                polonczone[i][1]+=" ";
                polonczone[i][3]+=" ";
            }
            polonczone[i][1]+= "   ║";
            polonczone[i][3]+=pola_pomocnicze[i].wyswietl()+ "║";
            polonczone[i][2] = "║      ║";
            polonczone[i][4] = "╚══════╝";
         }
        if(pola_docelowe[i].getSymbol()==0){
            polonczone[i+4][0]="┌──────┐";
            polonczone[i+4][1]="│      │";
            polonczone[i+4][2]="│      │";
            polonczone[i+4][3]="│      │";
            polonczone[i+4][4]="└──────┘";
        }
        else{
            polonczone[i+4][0] = "╔══════╗";
            polonczone[i+4][1] = "║" + pola_docelowe[i].wyswietl();
            polonczone[i+4][3] = "║   ";
            if(pola_docelowe[i].getSymbol()!=10){
                polonczone[i+4][1]+=" ";
                polonczone[i+4][3]+=" ";
            }
            polonczone[i+4][1] += "   ║";
            polonczone[i+4][3] += pola_docelowe[i].wyswietl()+ "║";
            polonczone[i+4][2] = "║      ║";
            polonczone[i+4][4] = "╚══════╝";
        }
    }
    for(int i=0;i<5;i++){
        std::cout<<std::endl;
        for(int j=0;j<8;j++){
            std::cout<<polonczone[j][i]<<"    ";
            if(j==3) std::cout<<"            ";
        }
    }

    std::cout<<std::endl<<"Pola Gry:  G1          G2          G3          G4          G5          G6          G7          G8";
    std::vector<std::vector<std::string> > do_wyswietlenia;
    do_wyswietlenia.resize(8);
    for(int i=0;i<8;i++) do_wyswietlenia[i].resize(17,"      ");
    for(int i=0;i<8;i++){
        for(int j=0;j<pola_gry[i].size();j++){
            do_wyswietlenia[i][2*j] = "╔══════╗";
            do_wyswietlenia[i][2*j + 1] = "║" + pola_gry[i][j].wyswietl();
            if(pola_gry[i][j].getSymbol()!=10) do_wyswietlenia[i][2*j + 1] += " ";
            do_wyswietlenia[i][2*j + 1] += "   ║";
            if(j == pola_gry[i].size() - 1){
                do_wyswietlenia[i][2*j + 2] = "║      ║";
                do_wyswietlenia[i][2*j + 3] = "║   ";
                if(pola_gry[i][j].getSymbol()!=10) do_wyswietlenia[i][2*j + 3] +=" ";
                do_wyswietlenia[i][2*j + 3] += pola_gry[i][j].wyswietl() + "║";
                do_wyswietlenia[i][2*j+4] = "╚══════╝";
            }
        }
    }
    for(int i=0;i<17;i++){
        std::cout<<std::endl<<"        ";
        for(int j=0;j<8;j++){
            std::cout<<do_wyswietlenia[j][i]<<"    ";
        }
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
std::vector<std::vector<karta> > pasjans::getPola_gry() const{
    return pola_gry;
}