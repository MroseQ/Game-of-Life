#pragma once
#include "Organizm.h"
#include <iostream>
class Zwierze : public Organizm {
public:
	Zwierze(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat, bool czyPoAkcji = false)
		: Organizm(sila, inicjatywa, polozenie, swiat, czyPoAkcji) {};
	~Zwierze();
	virtual void akcja();
	virtual void kolizja(Organizm* kolizator);
	virtual void rysowanie(std::ostream& out);
	virtual Organizm* utworzDziecko(Swiat& swiat,Polozenie* polozenie) = 0;
	bool czyTenSamTyp(Zwierze* other);
	virtual void rozmnoz(Swiat& swiat, Polozenie alfa, Polozenie beta);
};