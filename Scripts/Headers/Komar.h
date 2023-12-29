#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Komar : public Zwierze {

public:
	const static std::string symbol;
	Komar(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Zwierze("Komar-", sila, inicjatywa, polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	void akcja();
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Komar* a = new Komar(1, 1, polozenie, swiat, true);
		return a;
	}
};