#pragma once
#include "Roslina.h"
#include "point.h"
#include <string>
class WilczeJagody : public Roslina {

public:
	const static std::string symbol;
	WilczeJagody(Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Roslina("Jagody-", polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	void kolizja(Organizm* kolizja);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		WilczeJagody* a = new WilczeJagody(polozenie, swiat, true);
		return a;
	}

};