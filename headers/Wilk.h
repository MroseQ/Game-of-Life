#pragma once
#include "Zwierze.h"
#include <iostream>
class Wilk : public Zwierze {
public:
	Wilk(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat, bool czyPoAkcji = false)
		: Zwierze(sila, inicjatywa, polozenie, swiat, czyPoAkcji) {};
	void rysowanie(std::ostream& out);
	Organizm* utworzDziecko(Swiat& swiat, Polozenie* polozenie) {
		Wilk* a = new Wilk(6, 5, polozenie, swiat,true);
		return a;
	}
};