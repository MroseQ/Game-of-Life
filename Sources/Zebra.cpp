#include "Zwierze.h"
#include "Zebra.h"
#include <iostream>
#include <random>
#include "Swiat.h"
#include "SystemEventow.h"
#include <string>
void Zebra::rysowanie(std::ostream& out) {
	out << this->symbol;
};

void Zebra::akcja() {
	Polozenie polozenieZebry = this->getPolozenie();
	std::pair<Polozenie*, int> polaObok = polozenieZebry ^ polozenieZebry;
	bool wilkSpotted = false;
	Polozenie polozenieWilka;
	for (int i = 0; i < polaObok.second; i++) {
		if (this->getSwiat()->czyObiektNaPolozeniu(&polaObok.first[i])
			&& typeid(*this->getSwiat()->zwrocObiektZPolozenia(&polaObok.first[i])) == typeid(Wilk))
		{
			wilkSpotted = true;
			polozenieWilka = this->getSwiat()->zwrocObiektZPolozenia(&polaObok.first[i])->getPolozenie();
		}
	}
	if (!wilkSpotted) {
		Zwierze::akcja();
	}
	else {
		int distX = this->getPolozenie().x - polozenieWilka.x;
		int distY = this->getPolozenie().y - polozenieWilka.y;
		this->setPopPolozenie(this->getPolozenie());
		this->addPolozenie(distX, distY);
		if (Organizm* kolizator = this->getSwiat()->sprawdzKolizjeNaPolozeniu(this->getPolozenie(), this)) {
			Zwierze::kolizja(kolizator);
		}
		else {
			this->getSwiat()->pushEvent(new SystemEvent("Ruch obiektu " + this->getID() +
				" na -> (" + to_string(this->getPolozenie().x) + "," + to_string(this->getPolozenie().y) + ")"));
		}
	}
}

const std::string Zebra::symbol = "//";