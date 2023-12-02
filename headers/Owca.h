#pragma once
#include "Zwierze.h"
#include <iostream>
class Owca : public Zwierze {
public:
	Owca(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat,bool czyPoAkcji)
		: Zwierze(sila, inicjatywa, polozenie, swiat, czyPoAkcji) {};
	void rysowanie(std::ostream& out);
};