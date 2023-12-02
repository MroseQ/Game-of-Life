#include "Zwierze.h"
#include "Zolw.h"
#include <iostream>
void Zolw::rysowanie(std::ostream& out) {
	out << "o@";
};

void Zolw::akcja() {
	if (rand() % 100 + 1 > 75) {
		Zwierze::akcja();
	}
}

void Zolw::kolizja(Organizm* kolizator) {
	if (kolizator->getSila() < 5) {
		kolizator->setPolozenie(kolizator->getPopPolozenie());
	}
	//if(Zolw* drugi = dynamic_cast<Zolw*>(kolizator))
}