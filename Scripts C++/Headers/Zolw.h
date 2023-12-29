#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Zolw : public Zwierze {

public:
	const static std::string symbol;
	Zolw(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Zwierze("Zolw-", sila, inicjatywa, polozenie, swiat,  czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	void akcja();
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Zolw* a = new Zolw(2, 1, polozenie, swiat, true);
		return a;
	}

};