#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Jez : public Zwierze {

public:
	const static std::string symbol;
	Jez(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Zwierze("Jez-", sila, inicjatywa, polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Jez* a = new Jez(2, 3, polozenie, swiat, true);
		return a;
	}

};