#include "Roslina.h"
#include "Guarana.h"
#include <iostream>
#include <string>
void Guarana::rysowanie(std::ostream& out) {
	out << this->symbol;
};
void Guarana::kolizja(Organizm* zwierze) {
	zwierze->setSila(zwierze->getSila() + 3);
	Roslina::kolizja(zwierze);
}

const std::string Guarana::symbol = "GU";