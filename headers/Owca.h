#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Owca : public Zwierze {

public:
	const static std::string symbol;
	Owca(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Zwierze("Owca-", sila, inicjatywa, polozenie, swiat,  czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Owca* a = new Owca(4, 4, polozenie, swiat, true);
		return a;
	}

};