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
	
	//próba rozprzestnienienia siê
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
	

	//losowanie s¹siaduj¹cej pozycji, które nie jest zajête.
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

	// je¿eli nie ma ¿adnego obiektu na mo¿liwym po³o¿eniu, roslina zasieje s¹siaduj¹ce pole.
	if (polozenieNowegoOsobnika != nullptr) {
		Organizm* a = this->utworzDziecko(this->getSwiat(), polozenieNowegoOsobnika);

		this->getSwiat()->pushEvent(new SystemEvent("Roslina " + this->getID() +
			" rozprzestrzenila sie na -> (" + to_string(a->getPolozenie().x) + "," + to_string(a->getPolozenie().y) + ")"));
	}

	// je¿eli wszystkie pozycje s¹ zajête, roslina nie zasieje s¹siaduj¹cego pola.
	else {
		this->getSwiat()->pushEvent(new SystemEvent("Roslina '" + this->getType() + "' nie miala miejsca na rozprzestrzenienie sie."));
	}
}