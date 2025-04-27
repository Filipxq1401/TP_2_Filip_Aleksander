//Plik main - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include "funkcje.hpp"
#include <cstdlib>
#include<iostream>
int main() {
	system("chcp 65001");
	std::cout<<"Czy chcesz żeby program czyścił konsolę?(Y/N) ";
	char znak;
	bool czy_cls;
	std::cin>>znak;
	if(znak == 'Y' || znak =='y') czy_cls=true;
	else czy_cls = false; 
	if(czy_cls) system("cls");
	pasjans gra(czy_cls);
	
	return 0;
}
