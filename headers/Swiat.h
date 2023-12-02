#pragma once
#include "Organizm.h"
#include "SystemEventow.h"
#include <list>
#include <algorithm>
using namespace std;

class Swiat{
public:
	list<Organizm*> organizmySwiata, organizmyDoDodaniaDoSwiata;
	list<SystemEvent*> listaEventow;
	int rozmiar;
	int tura;
	Polozenie* doNarysowania;
	Swiat(int rozmiar);
	void wykonajTure();
	void rysujSwiat();
	void dodajDziecko(Organizm* organizm);
	Organizm* sprawdzKolizjeNaPolozeniu(Polozenie* p,Organizm* napastnik = nullptr);
	bool czyObiektNaPolozeniu(Polozenie* p);
};