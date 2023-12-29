#include "Zwierze.h"
#include "Komar.h"
#include <iostream>
#include <random>
#include "Swiat.h"
#include "SystemEventow.h"
#include <string>
void Komar::rysowanie(std::ostream& out) {
	out << this->symbol;
};

void Komar::akcja() {
	Polozenie polozenieKomara = this->getPolozenie();
	std::pair<Polozenie*, int> polaObok = polozenieKomara ^ polozenieKomara;
	int counter = 0;
	for (int i = 0; i < polaObok.second; i++) {
		if (this->getSwiat()->czyObiektNaPolozeniu(&polaObok.first[i]) 
			&& typeid(*this->getSwiat()->zwrocObiektZPolozenia(&polaObok.first[i])) == typeid(Komar)) 
		{
			this->incSila();
			this->incInicjatywa();
			counter++;
		}
	}
	if (counter != 0) {
		this->getSwiat()->pushEvent(new SystemEvent
			{ this->getID() + " zwiekszyl swoje parametry o +" + to_string(counter) });
	}
	Zwierze::akcja();
}

const std::string Komar::symbol = "*-";