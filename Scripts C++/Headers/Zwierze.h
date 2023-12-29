#pragma once
#include "Organizm.h"
#include <iostream>
#include <string>
class Zwierze : public Organizm {

protected:
	Zwierze(std::string prefiks, int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool czyPoAkcji = false, std::string* id = nullptr)
		: Organizm(prefiks, sila, inicjatywa, polozenie, swiat,  czyPoAkcji, id) {};
	virtual void akcja();
	virtual void kolizja(Organizm* kolizator);

private:
	void walka(Organizm* obronca);
	void rozmnoz(Swiat* swiat, Polozenie alfa, Polozenie beta);
	virtual Organizm* utworzDziecko(Swiat* swiat,Polozenie* polozenie) = 0;
	virtual void rysowanie(std::ostream& out) = 0;

};