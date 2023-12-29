#include "Roslina.h"
#include "Organizm.h"
#include <cstdlib>
#include <iostream>
#include "Swiat.h"
#include "SystemEventow.h"
#include <string>
#include <random>

void Roslina::rysowanie(std::ostream& out) {
	std::cout << "ER";
}

void Roslina::akcja() {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> percentage(1, 100);
	int spawnRate = 5;
	
	//pr�ba rozprzestnienienia si�
	if (percentage(gen) <= spawnRate) {
		this->rozmnoz(this->getSwiat(), this->getPolozenie());
	}
}

void Roslina::kolizja(Organizm* kolizator) {
	this->getSwiat()->pushEvent(new SystemEvent{"Obiekt "+kolizator->getID() + " zebral "+this->getID()});
	this->getSwiat()->pushToRemove(this);
}


void Roslina::rozmnoz(Swiat* swiat, Polozenie alfa) {
	std::random_device rd;
	std::mt19937 gen(rd());

	pair<Polozenie*, int> lista = alfa ^ alfa;
	Polozenie* mozliwePolozenia = lista.first;
	Polozenie* polozenieNowegoOsobnika = nullptr;
	

	//losowanie s�siaduj�cej pozycji, kt�re nie jest zaj�te.
	std::uniform_int_distribution<int> pozycja(0, lista.second - 1);
	int startIndex = pozycja(gen);
	int index = startIndex;
	do {
		if (index+1 > lista.second-1) {
			index = 0;
		}
		else {
			index++;
		}
		if (!this->getSwiat()->czyObiektNaPolozeniu(&mozliwePolozenia[index])) {
			polozenieNowegoOsobnika = &mozliwePolozenia[index];
			break;
		}
	} while (index!=startIndex);

	// je�eli nie ma �adnego obiektu na mo�liwym po�o�eniu, roslina zasieje s�siaduj�ce pole.
	if (polozenieNowegoOsobnika != nullptr) {
		Organizm* a = this->utworzDziecko(this->getSwiat(), polozenieNowegoOsobnika);

		this->getSwiat()->pushEvent(new SystemEvent("Roslina " + this->getID() +
			" rozprzestrzenila sie na -> (" + to_string(a->getPolozenie().x) + "," + to_string(a->getPolozenie().y) + ")"));
	}

	// je�eli wszystkie pozycje s� zaj�te, roslina nie zasieje s�siaduj�cego pola.
	else {
		this->getSwiat()->pushEvent(new SystemEvent("Roslina '" + this->getType() + "' nie miala miejsca na rozprzestrzenienie sie."));
	}
}