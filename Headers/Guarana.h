#pragma once
#include "Roslina.h"
#include "point.h"
#include <string>
class Guarana : public Roslina {

public:
	const static std::string symbol;
	Guarana(Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Roslina("Guarana-", polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	void kolizja(Organizm* kolizja);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Guarana* a = new Guarana(polozenie, swiat, true);
		return a;
	}

};