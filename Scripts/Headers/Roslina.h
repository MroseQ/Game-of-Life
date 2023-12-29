#pragma once
#include "Organizm.h"
#include <iostream>
#include <string>
class Roslina : public Organizm {

protected:
	Roslina(std::string prefiks, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, string* id = nullptr)
		: Organizm(prefiks, 0, 0, polozenie, swiat, czyPoAkcji, id) {};
	virtual void kolizja(Organizm* kolizator);

private:
	virtual void akcja();
	virtual void rysowanie(std::ostream& out) = 0;
	virtual Organizm* utworzDziecko(Swiat* swiat, Polozenie* polozenie) = 0;
	virtual void rozmnoz(Swiat* swiat, Polozenie alfa);

};