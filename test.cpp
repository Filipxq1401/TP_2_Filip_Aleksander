//Plik testowy - techniki programowania projekt 2 - zadanie 8
//Filip Skudlarz 203314 ACIR 4A
//Aleksander Kargol 203225 ACIR 4A
#include"funkcje.hpp"
#include<iostream>
using namespace std;

int main(){
    //testowanie wyświetlania kart
    system("chcp 65001");
    /*karta test(1,1);
	for (int i = 1; i <= 13; i++){
		for (int j = 1; j <= 4; j++){
			test.zmienKarte(i,j);
			test.wyswietl();
			cout<<"	";
		}
		cout<<endl;
	}*/
    pasjans tak(false);
    tak.wyswietl_testowe();
    return 0;
}