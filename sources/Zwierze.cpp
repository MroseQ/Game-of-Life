#include "Organizm.h"
#include "Zwierze.h"
#include <cstdlib>
#include <iostream>
#include "Swiat.h"
#include "Wilk.h"
#include "SystemEventow.h"
Zwierze::~Zwierze() {
	
}

void Zwierze::rysowanie(std::ostream& out) {
	std::cout << "rysuj";
}

void Zwierze::akcja()  {
	
	int randX, randY;
	do {
		if (this->polozenie.x == 1) randX = rand() % 2;
		else if (this->polozenie.x == 20) randX = rand() % 2 - 1;
		else randX = rand() % 3 - 1;
		if (this->polozenie.y == 1) randY = rand() % 2;
		else if (this->polozenie.y == 20) randY = rand() % 2 - 1;
		else randY = rand() % 3 - 1;
	} while (randX == 0 && randY == 0);
	
	this->poprzedniePolozenie = this->polozenie;
	this->polozenie.x += 1;
	this->polozenie.y += 1;
	//this->polozenie.x += randX;
	//this->polozenie.y += randY;
	//std::cout << this->polozenie.x << "  " << this->polozenie.y;
	/*
	poprzedniePolozenie = this->polozenie;
	this->polozenie.x = 6;
	this->polozenie.y = 8;
	*/
	if (Organizm* kolizator = swiat->sprawdzKolizjeNaPolozeniu(&this->polozenie,this)) {
		this->kolizja(kolizator);
	}
	else {
		this->swiat->listaEventow.push_back(new SystemEvent{"Ruch" } );
	}
}

void Zwierze::kolizja(Organizm* kolizator){
	if (czyTenSamTyp(dynamic_cast<Zwierze*>(kolizator))) {
		this->polozenie = this->poprzedniePolozenie;
		this->swiat->listaEventow.push_back(new SystemEvent{ "Kolizja" } );
		this->rozmnoz(*this->swiat, this->polozenie, kolizator->getPolozenie());
		kolizator->czyPoAkcji = true;
	}
	else {
		std::cout << "Kolizja z obiektem innej klasy" << std::endl;
	}

}

void Zwierze::rozmnoz(Swiat& swiat, Polozenie alfa, Polozenie beta) {
	try {
		pair<Polozenie*,int> lista = alfa ^ beta;
		Polozenie* mozliwePolozenia = lista.first;
		Polozenie* polozenieNowegoOsobnika = nullptr;
		for (int i = 0; i < lista.second; i++) {
			cout << &mozliwePolozenia[i];
			if (!this->swiat->czyObiektNaPolozeniu(&mozliwePolozenia[i])) {
				polozenieNowegoOsobnika = &mozliwePolozenia[i];
				break;
			}
		}
		cout << polozenieNowegoOsobnika;
		if (polozenieNowegoOsobnika != nullptr) {
			Organizm* a = this->utworzDziecko(*this->getSwiat(), polozenieNowegoOsobnika);
		}
		else {
			this->getSwiat()->listaEventow.push_back(new SystemEvent{ "Gatunek byl niesmialy wiec nie bylo dziecka." });
			// case gdy gatunek jest otoczony i sie wstydzi.
		}
	}
	catch (Wyjatek& w) {
		cout << "Wyjatek: " << w.tekst;
	}
	
}

bool Zwierze::czyTenSamTyp(Zwierze* other) {
	return typeid(*this) == typeid(*other);
}