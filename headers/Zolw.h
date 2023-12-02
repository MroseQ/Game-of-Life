#pragma once
#include "Zwierze.h"
#include <iostream>
class Zolw : public Zwierze {
public:
	Zolw(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat, bool czyPoAkcji)
		: Zwierze(sila, inicjatywa, polozenie, swiat, czyPoAkcji) {};
	void rysowanie(std::ostream& out);
	void akcja();
	void kolizja(Organizm* kolizator);
};