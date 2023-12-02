#pragma once
#include "point.h"
#include <iostream>
class Swiat;
class Organizm {
public:
	Organizm(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat, bool czyPoAkcji = false);
	Organizm() : sila(0), inicjatywa(0), polozenie({ 0, 0 }), swiat(nullptr) {};
	int sila, poczatkowaSila, zywyOdTury ,inicjatywa, poczatkowaInicjatywa;
	bool czyPoAkcji;
	Polozenie polozenie, poprzedniePolozenie;
	Swiat* swiat;
	virtual void akcja() = 0;
	virtual void kolizja(Organizm* kolizator) = 0;
	virtual void rysowanie(std::ostream& out) = 0;
	

	int getSila() { return sila; }
	int getInicjatywa() { return inicjatywa; }
	Polozenie getPolozenie() { return polozenie; }
	Polozenie getPopPolozenie() { return poprzedniePolozenie; }
	Swiat* getSwiat() { return swiat; }
	int getAliveSince() { return zywyOdTury; }
	void setAliveSince(int tura) { this->zywyOdTury = tura; }
	void setPolozenie(Polozenie p) { this->polozenie = p; }
};