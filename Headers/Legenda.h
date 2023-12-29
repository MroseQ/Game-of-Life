#pragma once
#include <vector>
#include <algorithm>
#include "Organizm.h"

#include "Komar.h"
#include "Wilk.h"
#include "Owca.h"
#include "Trawa.h"
#include "Guarana.h"
#include "Zolw.h"
#include "Jez.h"
#include "WilczeJagody.h"
#include "Zebra.h"

#include <string>
class Legenda {

public:
	void resize(std::vector<Organizm*> lista);
	int getDlugosc() { return _dlugosc; }
	int getWysokosc() { return _wysokosc; }
	std::vector<std::string>& getStringi() { return _listaStringow; }

private:
	std::vector<const type_info*> _listaTypow;
	int _dlugosc = 0,_wysokosc = 0;
	std::vector<std::string> _listaStringow;
	
	std::vector<std::string> _nazwyDoStringow(std::vector<const type_info*> listaTypow);
	std::string _pobierzSymbol(const type_info& typ);
};