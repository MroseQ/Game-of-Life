#include "Legenda.h"

void Legenda::resize(std::vector<Organizm*> lista) {
	_listaTypow.clear();
	for (Organizm* var : lista) {
		bool match = false;
		if (_listaTypow.size() != 0) {
			for (const type_info* typ : _listaTypow) {
				if (typ == &typeid(*var)) {
					match = true;
					break;
				}
			}
		}
		if (match) {
			continue;
		}
		else {
			_listaTypow.push_back(&typeid(*var));
		}
	}
	_wysokosc = _listaTypow.size();
	_dlugosc = 0;
	_listaStringow = _nazwyDoStringow(_listaTypow);
}

std::vector<std::string> Legenda::_nazwyDoStringow(std::vector<const type_info*> listaTypow) {
	std::vector<std::pair<std::string, std::string>*> listaDoObrobienia;
	for (const type_info* typ : listaTypow) {
		int liczbaLiter = 8;
		std::string s = typ->name();
		s = s.substr(6);
		listaDoObrobienia.push_back(new std::pair<std::string, std::string>(s, _pobierzSymbol(*typ)));
		for (char znak : s) {
			liczbaLiter++;
		}
		if (liczbaLiter > _dlugosc) _dlugosc = liczbaLiter;
	}
	std::vector<std::string> listaGotowychStringow;
	for (std::pair<std::string, std::string>* s : listaDoObrobienia) {
		std::string gotowiec = "| " + s->first + ": " + s->second;
		while (gotowiec.length() < _dlugosc - 2) {
			gotowiec += " ";
		}
		gotowiec += " |";
		listaGotowychStringow.push_back(gotowiec);
	}
	return listaGotowychStringow;
}

std::string Legenda::_pobierzSymbol(const type_info& typ) {
	if (typ == typeid(Komar)) {
		return Komar::symbol;
	}
	else if (typ == typeid(Owca)) {
		return Owca::symbol;
	}
	else if (typ == typeid(Wilk)) {
		return Wilk::symbol;
	}
	else if (typ == typeid(WilczeJagody)) {
		return WilczeJagody::symbol;
	}
	else if (typ == typeid(Guarana)) {
		return Guarana::symbol;
	}
	else if (typ == typeid(Jez)) {
		return Jez::symbol;
	}
	else if (typ == typeid(Zolw)) {
		return Zolw::symbol;
	}
	else if (typ == typeid(Trawa)) {
		return Trawa::symbol;
	}
	else if (typ == typeid(Zebra)) {
		return Zebra::symbol;
	}
	else {
		return "??";
	}
}