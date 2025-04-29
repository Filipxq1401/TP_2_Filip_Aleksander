//Plik main - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include "funkcje.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
int main() {
	pasjans gra;
	std::thread watekTasowania(tasuj,std::ref(gra));
	system("chcp 65001");
	std::cout<<"Czy chcesz żeby program czyścił konsolę?(Y/N) ";
	char znak;
	bool czy_cls = false;
	std::cin>>znak;
	if(znak == 'Y' || znak =='y') czy_cls=true;
	else czy_cls = false; 
	if(czy_cls) system("cls");
	int tura = 1;
	watekTasowania.join();
	gra.ustawCls(czy_cls);
	std::cin.ignore();
	while (!gra.czyKoniec()){
		gra.wyswietl_ladne();
		if(!gra.czyJestRuch()){
			std::cout<<"Przegrana - brak dostępnych ruchów";
			return 0;
		}
		std::cout<<"Podaj następny ruch";
		if(tura == 1) std::cout<<"(napisz help aby wyświetlić jak wpisać ruch): ";
		else std::cout<<": ";
		std::string komenda;
		bool poprawna;
		ruch aktualny_ruch;
		while(true){
			std::getline(std::cin,komenda);
			aktualny_ruch = dekoduj(komenda,poprawna);
			if (poprawna) poprawna = gra.czyRuchJestdozwolony(aktualny_ruch);
			if(poprawna) break;
		}
		gra.wykonajRuch(aktualny_ruch);
		tura++;
	}
	gra.wyswietl_ladne();
	std::cout<<"Wygrana - ułożyłeś te rozdanie w "<<tura-1<<" ruchów";
	return 0;
}
