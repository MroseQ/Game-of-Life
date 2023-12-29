#pragma once
#include "Zwierze.h"
#include <iostream>
#include <string>
class Wilk : public Zwierze {

public:
	const static std::string symbol;
	Wilk(int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, std::string* id = nullptr)
		: Zwierze("Wilk-",sila, inicjatywa, polozenie, swiat, czyPoAkcji, id) {};

private:
	void rysowanie(std::ostream& out);
	Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) {
		Wilk* a = new Wilk(9, 5, polozenie, swiat,true);
		return a;
	}

};