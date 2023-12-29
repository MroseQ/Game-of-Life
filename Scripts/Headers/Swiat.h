#pragma once
#include "Settings.h"
#include "Organizm.h"
#include "SystemEventow.h"
#include "Legenda.h"
#include <vector>
#include <algorithm>
using namespace std;

class Swiat{
public:
	vector<Organizm*> organizmySwiata;
	Swiat(int rozmiar = N, int tura = 0);
	void wykonajTure();
	void rysujSwiat();
	void fetch();
	void zapiszSwiat();
	Swiat* wczytajSwiat();

	void operator=(Swiat* other);

	Organizm* sprawdzKolizjeNaPolozeniu(Polozenie p,Organizm* napastnik = nullptr);
	bool czyObiektNaPolozeniu(Polozenie* p);
	bool czyObiektNaPolozeniu(int x, int y);
	Organizm* zwrocObiektZPolozenia(Polozenie* p);
	Organizm* zwrocObiektZPolozenia(int x, int y);

	Organizm* utworzObiekt(string nazwaKlasy, string* id,int sila,int inicjatywa,Polozenie* polozenie, Swiat* swiat);

	int getTura() { return _tura; }

	void pushEvent(SystemEvent* e);
	void pushToRemove(Organizm* o);
	void pushToWorld(Organizm* o);


private:
	int _rozmiar;
	int _tura;
	Legenda* _legenda;
	vector<SystemEvent*> _listaEventow;

	void _usunZeSwiata();
	void _posortujOrganizmy();
	static int _inputNumber();
	static std::string _inputName();
	static void _printLine(char code);
	static void _printSpace(int iterations);
	static std::pair<std::string, std::string> _getSlowo(std::string linia, char separator);
};