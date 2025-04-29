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
pasjans::pasjans(){
    pola_gry.resize(8);
    karta puste_pole(0,0);
    for(int i=0;i<4;i++){
        pola_docelowe.push_back(puste_pole);
        pola_pomocnicze.push_back(puste_pole);
    }
}
void pasjans::ustawCls(const bool czyszczenie){
    czy_cls = czyszczenie;
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
    std::vector<std::vector<std::string> > polaczone;
    polaczone.resize(8);
    for(int i=0;i<8;i++){
        polaczone[i].resize(5);
    }
    for(int i=0;i<4;i++){
        if(pola_pomocnicze[i].getSymbol()==0){
            polaczone[i][0]="┌──────┐";
            polaczone[i][1]="│      │";
            polaczone[i][2]="│      │";
            polaczone[i][3]="│      │";
            polaczone[i][4]="└──────┘";
        }
        else{
            polaczone[i][0] = "╔══════╗";
            polaczone[i][1] ="║" + pola_pomocnicze[i].wyswietl();
            polaczone[i][3] = "║   ";
            if(pola_pomocnicze[i].getSymbol()!=10){
                polaczone[i][1]+=" ";
                polaczone[i][3]+=" ";
            }
            polaczone[i][1]+= "   ║";
            polaczone[i][3]+=pola_pomocnicze[i].wyswietl()+ "║";
            polaczone[i][2] = "║      ║";
            polaczone[i][4] = "╚══════╝";
         }
        if(pola_docelowe[i].getSymbol()==0){
            polaczone[i+4][0]="┌──────┐";
            polaczone[i+4][1]="│      │";
            polaczone[i+4][2]="│      │";
            polaczone[i+4][3]="│      │";
            polaczone[i+4][4]="└──────┘";
        }
        else{
            polaczone[i+4][0] = "╔══════╗";
            polaczone[i+4][1] = "║" + pola_docelowe[i].wyswietl();
            polaczone[i+4][3] = "║   ";
            if(pola_docelowe[i].getSymbol()!=10){
                polaczone[i+4][1]+=" ";
                polaczone[i+4][3]+=" ";
            }
            polaczone[i+4][1] += "   ║";
            polaczone[i+4][3] += pola_docelowe[i].wyswietl()+ "║";
            polaczone[i+4][2] = "║      ║";
            polaczone[i+4][4] = "╚══════╝";
        }
    }
    for(int i=0;i<5;i++){
        std::cout<<std::endl;
        for(int j=0;j<8;j++){
            std::cout<<polaczone[j][i]<<"    ";
            if(j==3) std::cout<<"            ";
        }
    }

    std::cout<<std::endl<<"Pola Gry:  G1          G2          G3          G4          G5          G6          G7          G8";
    std::vector<std::vector<std::string> > do_wyswietlenia;
    do_wyswietlenia.resize(8);
    int max = pola_gry[0].size();
    for(int i=1;i<8;i++){
        if(pola_gry[i].size() > max) max = pola_gry[i].size();
    }
    int n = max*2 +3;
    if(n == 3) n=5;
    for(int i=0;i<8;i++) do_wyswietlenia[i].resize(n,"        ");
    for(int i=0;i<8;i++){
        if(pola_gry[i].empty()){
            do_wyswietlenia[i][0]="┌──────┐";
            do_wyswietlenia[i][1]="│      │";
            do_wyswietlenia[i][2]="│      │";
            do_wyswietlenia[i][3]="│      │";
            do_wyswietlenia[i][4]="└──────┘";
        }
        else{
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
    }
    for(int i=0;i<n;i++){
        std::cout<<std::endl<<"        ";
        for(int j=0;j<8;j++){
            std::cout<<do_wyswietlenia[j][i]<<"    ";
        }
    }
    std::cout<<std::endl;
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
bool pasjans::czyKoniec() const{
    for(int i=0;i<8;i++){
        if(!pola_gry[i].empty()) return false;
    }
    for(int i=0;i<4;i++){
        if(!pola_pomocnicze[i].pusta()) return false;
    }
    return true;
}
std::vector<std::vector<karta> > pasjans::getPola_gry() const{
    return pola_gry;
}
bool pasjans::czyRuchJestdozwolony(const ruch potencjalny) const{
    bool decyzja = false;
    if(potencjalny.typ_pola_1==0){
        if(pola_gry[potencjalny.numer_pola_1].empty()) decyzja=false;
        else if(potencjalny.typ_pola_2==0){
            if(pola_gry[potencjalny.numer_pola_2].empty()) decyzja = true;
            else if(pola_gry[potencjalny.numer_pola_1].back().getKolor()!=pola_gry[potencjalny.numer_pola_2].back().getKolor() && pola_gry[potencjalny.numer_pola_2].back().getSymbol()-pola_gry[potencjalny.numer_pola_1].back().getSymbol()==1) decyzja = true;
        }
        else if(potencjalny.typ_pola_2==1){
            if(pola_pomocnicze[potencjalny.numer_pola_2].pusta()) decyzja=true;
        }
        else{
            if(pola_docelowe[potencjalny.numer_pola_2].pusta()){
                if(pola_gry[potencjalny.numer_pola_1].back().getSymbol()==1) decyzja=true;
            }
            else if(pola_docelowe[potencjalny.numer_pola_2].getZnakKoloru() == pola_gry[potencjalny.numer_pola_1].back().getZnakKoloru() && pola_gry[potencjalny.numer_pola_1].back().getSymbol() - pola_docelowe[potencjalny.numer_pola_2].getSymbol() == 1) decyzja = true;
        }
    }
    else{
        if(pola_pomocnicze[potencjalny.numer_pola_1].pusta()) decyzja = false;
        else if(potencjalny.typ_pola_2==0){
            if(pola_gry[potencjalny.numer_pola_2].empty()) decyzja=true;
            else if(pola_pomocnicze[potencjalny.numer_pola_1].getKolor()!=pola_gry[potencjalny.numer_pola_2].back().getKolor() && pola_gry[potencjalny.numer_pola_2].back().getSymbol() - pola_pomocnicze[potencjalny.numer_pola_1].getSymbol() == 1) decyzja = true;
        }
        else{
            if(pola_docelowe[potencjalny.numer_pola_2].pusta()){
                if(pola_pomocnicze[potencjalny.numer_pola_1].getSymbol()==1) decyzja=true;
            }
            else if(pola_docelowe[potencjalny.numer_pola_2].getZnakKoloru() == pola_pomocnicze[potencjalny.numer_pola_1].getZnakKoloru() && pola_pomocnicze[potencjalny.numer_pola_1].getSymbol() - pola_docelowe[potencjalny.numer_pola_2].getSymbol() == 1) decyzja = true;
            
        }
    }
    if(!decyzja) std::cout<<"Nie dozwolony ruch, wprowadz poprawny ruch: ";
    return decyzja;
}
void pasjans::wykonajRuch(const ruch dobry_ruch){
    if(dobry_ruch.typ_pola_1==0){
        if(dobry_ruch.typ_pola_2==0){
            pola_gry[dobry_ruch.numer_pola_2].push_back(pola_gry[dobry_ruch.numer_pola_1].back());
        }
        else if(dobry_ruch.typ_pola_2==1){
            pola_pomocnicze[dobry_ruch.numer_pola_2] = pola_gry[dobry_ruch.numer_pola_1].back();
        }
        else{
            pola_docelowe[dobry_ruch.numer_pola_2] = pola_gry[dobry_ruch.numer_pola_1].back();
        }
        pola_gry[dobry_ruch.numer_pola_1].pop_back();
    }
    else{
        if(dobry_ruch.typ_pola_2==0){
            pola_gry[dobry_ruch.numer_pola_2].push_back(pola_pomocnicze[dobry_ruch.numer_pola_1]);
        }
        else{
            pola_docelowe[dobry_ruch.numer_pola_2] = pola_pomocnicze[dobry_ruch.numer_pola_1];
        }
        pola_pomocnicze[dobry_ruch.numer_pola_1].zmienKarte(0,0);
    }
}
ruch dekoduj(const std::string komenda,bool& poprawnosc){
    poprawnosc = true;
    if(komenda == "help"){
        std::cout<<"Schemat komendy: "<<std::endl;
        std::cout<<"Typ i numer pierwszego pola - typ i numer drugiego pola"<<std::endl;
        std::cout<<"Przykładowa komenda: G1 - P2"<<std::endl;
        std::cout<<"Reguły ruchów znajdziesz: http://pl.wikipedia.org/wiki/FreeCell"<<std::endl;
        std::cout<<"Podaj swój ruch: "<<std::endl;
        poprawnosc = false;
        return ruch{0,0,0,0};
    }
    ruch zdekodowany = {0,0,0,0};
    if(komenda.size()!=7){
        poprawnosc = false;
    }
    else{
        if(komenda[0]=='G' || komenda[0]=='g'){
            zdekodowany.typ_pola_1 = 0;
            if(komenda[1]>='1' && komenda[1]<='8') zdekodowany.numer_pola_1 = komenda[1] - '0' - 1;
            else poprawnosc = false;
        }
        else if(komenda[0]=='P' || komenda[0]=='p'){
            zdekodowany.typ_pola_1 = 1;
            if(komenda[1]>='1' && komenda[1]<='4') zdekodowany.numer_pola_1 = komenda[1] - '0' - 1;
            else poprawnosc = false;
        }
        else poprawnosc = false;

        if(!(komenda[2]==' ' && komenda[3]=='-' && komenda[4]==' ')) poprawnosc = false;

        if(komenda[5]=='G' || komenda[5]=='g'){
            zdekodowany.typ_pola_2 = 0;
            if(komenda[6]>='1' && komenda[6]<='8') zdekodowany.numer_pola_2 = komenda[6] - '0' - 1;
            else poprawnosc = false;
        }
        else if(komenda[5]=='P' || komenda[5]=='p'){
            zdekodowany.typ_pola_2 = 1;
            if(komenda[6]>='1' && komenda[6]<='4') zdekodowany.numer_pola_2 = komenda[6] - '0' - 1;
            else poprawnosc = false;
        }
        else if(komenda[5]=='D' || komenda[5]=='d'){
            zdekodowany.typ_pola_2 = 2;
            if(komenda[6]>='1' && komenda[6]<='4') zdekodowany.numer_pola_2 = komenda[6] - '0' - 1;
            else poprawnosc = false;
        }
        else poprawnosc = false;
    }
    if(zdekodowany.typ_pola_1 == zdekodowany.typ_pola_2 && zdekodowany.typ_pola_1!=0) poprawnosc=false;
    if(zdekodowany.typ_pola_1 == zdekodowany.typ_pola_2 && zdekodowany.typ_pola_1==0 && zdekodowany.numer_pola_1==zdekodowany.numer_pola_2) poprawnosc=false;
    if(!poprawnosc) std::cout<<"Niepoprawny ruch, wprowadź ponownie: ";
    return zdekodowany;
}
void tasuj(pasjans& gra){
    gra.rozdajKraty();
}
void pasjans::wczytaj_talie(const std::vector<std::vector<karta> > gry, const std::vector<karta> docelowe, const std::vector<karta> pomocnicze){
    pola_gry = gry;
    pola_docelowe = docelowe;
    pola_pomocnicze = pomocnicze;
}