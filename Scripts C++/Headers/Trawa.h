#pragma once
#include "Roslina.h"
#include "point.h"
#include <string>
class Trawa : public Roslina {

public:
	const static std::string symbol;
	Trawa(Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Roslina("Trawa-", polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Trawa* a = new Trawa(polozenie, swiat, true);
		return a;
	}

};