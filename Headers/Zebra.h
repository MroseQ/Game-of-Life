#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Zebra : public Zwierze {

public:
	const static std::string symbol;
	Zebra(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Zwierze("Zebra-", sila, inicjatywa, polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	void akcja();
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Zebra* a = new Zebra(4, 6, polozenie, swiat, true);
		return a;
	}
};