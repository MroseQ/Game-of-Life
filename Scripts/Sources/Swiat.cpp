#include "Swiat.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>

void Swiat::_posortujOrganizmy(){
	for (int i = 0; i < organizmySwiata.size() - 1; i++) {
		for (int j = 0; j < organizmySwiata.size() - i - 1; j++) {
			if (organizmySwiata[j]->getInicjatywa() < organizmySwiata[j + 1]->getInicjatywa() ||
				(organizmySwiata[j]->getInicjatywa() == organizmySwiata[j + 1]->getInicjatywa() &&
				 organizmySwiata[j]->getAliveSince() > organizmySwiata[j + 1]->getAliveSince())) {
				std::swap(organizmySwiata[j], organizmySwiata[j + 1]);
			}
		}
	}
}

Swiat::Swiat(int rozmiar, int tura) {
	this->_rozmiar = rozmiar;
	this->_tura = tura;
	this->_legenda = new Legenda();
}

void Swiat::rysujSwiat() {
	system("CLS");
	this->_legenda->resize(this->organizmySwiata);
	cout << "Autor: Marek Krasinski 192573";
	cout << endl << endl;

	if (this->_listaEventow.size() != 0) {
		_printSpace(fetchSize - 4);
		cout << "----- L I S T A   E V E N T O W -----" << endl;
		for (auto it = this->_listaEventow.begin(); it != this->_listaEventow.end(); ++it) {
			_printSpace(fetchSize - 10);
			(*it)->wypiszEvent(std::cout);
			delete* it;
		}
		_printSpace(fetchSize - 4);
		cout << "===== K O N I E C   L I S T Y   =====" << endl;
		this->_listaEventow.clear();
	}

	cout << endl << "   |";
	for (int i = 1; i <= _rozmiar; i++) {
		string wynik = (i < 10) ? "0" + to_string(i) : to_string(i);
		cout << wynik+"|";
	}
	cout << "   LEGENDA:";
	cout << endl;
	for (int j = 1; j <= _rozmiar; j++) {
		
		cout << "----";
		for (int k = 0; k < _rozmiar; k++) {
			cout << "---";
		}
		cout << endl;
		string wynik = (j < 10) ? "0" + to_string(j) : to_string(j);
		cout << wynik + " |";
		
		for (int i = 1; i <= _rozmiar; i++) {
			bool pass = false;
			for (Organizm* var : organizmySwiata) {
				if (var->getPolozenie().x == i && var->getPolozenie().y == j) {
					var->rysowanie(cout);
					pass = true;
				}
			}
			if (!pass) {
				cout << "  ";
			}
			cout << "|";
		}
		cout << "   ";
		if (j == 1 || j == _legenda->getWysokosc() + 2) {
			for (int i = 0; i < _legenda->getDlugosc(); i++) {
				cout << "=";
			}
		}
		else if (j > 1 && j < _legenda->getWysokosc() + 2) {
			int indeksSzukanegoElementu = j-2;
			auto iterator = _legenda->getStringi().begin();

			std::advance(iterator, indeksSzukanegoElementu);
			if (iterator != _legenda->getStringi().end()) {
				cout << *iterator;
			}
		}
		cout << endl;
	}
	cout << "====";
	for (int k = 0; k < _rozmiar; k++) {
		cout << "===";
	}
	cout << endl <<  "Tura: " << this->_tura;

}

bool Swiat::czyObiektNaPolozeniu(Polozenie* p) {
	for (Organizm* var : organizmySwiata) {
		if (*p == var->getPolozenie()) {
			return true;
		}
	}
	return false;
}

bool Swiat::czyObiektNaPolozeniu(int x, int y) {
	for (Organizm* var : organizmySwiata) {
		if (x == var->getPolozenie().x && y == var->getPolozenie().y) {
			return true;
		}
	}
	return false;
}

Organizm* Swiat::zwrocObiektZPolozenia(Polozenie* p) {
	for (Organizm* var : organizmySwiata) {
		if (*p == var->getPolozenie()) {
			return var;
		}
	}
	return nullptr;
}

Organizm* Swiat::zwrocObiektZPolozenia(int x, int y) {
	for (Organizm* var : organizmySwiata) {
		if (x == var->getPolozenie().x && y == var->getPolozenie().y) {
			return var;
		}
	}
	return nullptr;
}

Organizm* Swiat::sprawdzKolizjeNaPolozeniu(Polozenie p,Organizm* napastnik) {
	int count = 0;
	vector<Organizm*> obiektyNaPolozeniu;
	for (Organizm* var : organizmySwiata) {
		if (p == var->getPolozenie()) {
			count++;
			obiektyNaPolozeniu.push_back(var);
		}
	}
	if (count <= 1) return nullptr;
	else {
		for (Organizm* var : obiektyNaPolozeniu) {
			//if (napastnik == var)
			if (napastnik != var) return var;
		}
	}
	return nullptr;
}

std::pair<std::string,std::string> Swiat::_getSlowo(std::string linia, char separator) {
	size_t pozycja = 0;
	std::string slowo;
	pozycja = linia.find(separator);
	slowo = linia.substr(0, pozycja);
	linia.erase(0, pozycja + 1);
	return make_pair(slowo,linia);
}

Swiat* Swiat::wczytajSwiat() {
	_printLine('=');
	cout << endl << "| L O A D: ";
	_printSpace(11);
	cout << "|" << endl << "| Wprowadz nazwe pliku: ";
	string nazwaZapisu = _inputName();
	_printSpace(24 + nazwaZapisu.length() -4);
	cout << "|" << endl;
	std::ifstream graDoWczytania(nazwaZapisu);
	if (!graDoWczytania.is_open()) {
		cerr << "| Nie mozna otworzyc " << nazwaZapisu;
		_printSpace(21 + nazwaZapisu.length());
		cout << "|";
		_printLine('X');
		return nullptr;
	}
	int rozmiar, tura, kolejneID;

	string line;

	getline(graDoWczytania, line);

	pair<string,string> result = _getSlowo(line, ';');
	line = result.second;
	rozmiar = stoi(result.first);

	result = _getSlowo(line, ';');
	line = result.second;
	tura = stoi(result.first);

	result = _getSlowo(line, ';');
	line = result.second;
	kolejneID = stoi(result.first);
	Swiat* newSwiat = new Swiat(rozmiar, tura);
	Organizm::setKolejneID(kolejneID);
	while (getline(graDoWczytania, line)) {
		if (line == "END") {
			break;
		}
		string id, rawPolozenie,type;
		Polozenie* polozenie = new Polozenie;
		int aliveSince, sila, inicjatywa, stun;

		pair<string, string> result = _getSlowo(line, ';');
		line = result.second;
		id = result.first;

		result = _getSlowo(line, ';');
		line = result.second;
		rawPolozenie = result.first;
		pair<string, string> fixedPolozenie = _getSlowo(rawPolozenie, ',');
		polozenie->x = stoi(fixedPolozenie.first);
		polozenie->y = stoi(fixedPolozenie.second);

		result = _getSlowo(line, ';');
		line = result.second;
		aliveSince = stoi(result.first);

		result = _getSlowo(line, ';');
		line = result.second;
		sila = stoi(result.first);

		result = _getSlowo(line, ';');
		line = result.second;
		inicjatywa = stoi(result.first);

		result = _getSlowo(line, ';');
		line = result.second;
		stun = stoi(result.first);

		result = _getSlowo(line, ';');
		line = result.second;
		type = result.first;

		try {
			Organizm* organizm = utworzObiekt(type, &id, sila, inicjatywa, polozenie, newSwiat);
			organizm->setAliveSince(aliveSince);
			organizm->setStun(stun);
		}
		catch (Wyjatek& w) {
			cerr << "| BLAD: " << w.getTekst() << type;
			_printSpace(8 + strlen(w.getTekst()) + type.length());
			cout << "|";
			_printLine('X');
			return nullptr;
		}
		delete polozenie;
	}
	cout << "| Wczytano plik: " << nazwaZapisu;
	_printSpace(17 + nazwaZapisu.length());
	cout << "|";
	_printLine('=');
	graDoWczytania.close();
	return newSwiat;
}

Organizm* Swiat::utworzObiekt(string nazwaKlasy, string* id, int sila, int inicjatywa, Polozenie* polozenie,Swiat* swiat) {
	Organizm* object;
	if (nazwaKlasy == "Wilk") {
		object = new Wilk(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Owca") {
		object = new Owca(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Trawa") {
		object = new Trawa(polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Guarana") {
		object = new Guarana(polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "WilczeJagody") {
		object = new WilczeJagody(polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Jez") {
		object = new Jez(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Zolw") {
		object = new Zolw(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Komar") {
		object = new Komar(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else if (nazwaKlasy == "Zebra") {
		object = new Zebra(sila, inicjatywa, polozenie, swiat, false, id);
	}
	else {
		throw Wyjatek("Zla nazwa klasy ");
	}
	return object;
}

void Swiat::zapiszSwiat() {
	_printLine('=');
	cout << endl << "| S A V E: ";
	_printSpace(11);
	cout << "|" << endl << "| Wprowadz nazwe pliku: ";
	string nazwaZapisu = _inputName();
	_printSpace(24 + nazwaZapisu.length()-4);
	cout << "|" << endl << "| ";
	ofstream zapisanaGra;
	string result;
	int chars;
	zapisanaGra.open(nazwaZapisu.c_str());
	if (zapisanaGra.is_open())
	{
		zapisanaGra << _rozmiar << ";" << _tura << ";" << Organizm::getKolejneID() << "\n";
		for (auto it = this->organizmySwiata.begin(); it != this->organizmySwiata.end(); ++it)
		{
			if (*it != nullptr){
				zapisanaGra << (*it)->getID() << ";" << (*it)->getPolozenie() << ";" << (*it)->getAliveSince()
					<< ";" << (*it)->getSila() << ";" << (*it)->getInicjatywa() << ";" << (*it)->getStun() << ";" << (*it)->getType() << "\n";
			}
		}
		zapisanaGra << "END";
		zapisanaGra.close();
		result = "Zapisano jako " + nazwaZapisu;
		chars = 16 + nazwaZapisu.length();
	}
	else
	{
		result = "Zapis nieudany!";
		chars = 17;
	}
	cout << result;
	_printSpace(chars);
	cout << "|";
	_printLine('=');
}


std::string Swiat::_inputName() {
	std::string word;
	while (word.length() == 0) {
		char c = _getch();
		while (!std::isspace(c)) {
			word.push_back(c);
			cout << c;
			c = _getch();
		}
	}
	return word+".txt";
}

int Swiat::_inputNumber()
{
	std::string word;
	while (word.length() == 0) {
		char c = _getch();
		while (std::isdigit(c))
		{
			word.push_back(c);
			std::cout << c;
			c = _getch();
		}
	}
	return stoi(word);
}

void Swiat::_printLine(char code) {
	cout << endl;
	for (int i = 0; i <= fetchSize; i++) {
		cout << code;
	}
}

void Swiat::_printSpace(int iterations) {
	if (fetchSize - iterations >= 0) {
		for (int i = 0; i < fetchSize - iterations; i++) {
			cout << " ";
		}
	}
}

void Swiat::fetch() {
	int posX, posY;
	_printLine('=');
	cout << endl << "| F E T C H : ";
	_printSpace(14);
	cout << "|" << endl << "| X: ";
	posX = this->_inputNumber();
	cout << "  Y: ";
	posY = this->_inputNumber();
	_printSpace(10 + to_string(posX).length() + to_string(posY).length());
	cout << "|" << endl;
	Organizm* obiekt = zwrocObiektZPolozenia(posX, posY);
	if (obiekt == nullptr) {
		cout << "| Brak obiektu na X: " << posX << " Y: " << posY;
		_printSpace(25 + to_string(posX).length() + to_string(posY).length());
	}
	else {
		string wynik = zwrocObiektZPolozenia(posX, posY)->getID();
		cout << "| Wynik: " << wynik;
		_printSpace(9 + wynik.length());
		cout << "|" << endl << "| Parametry:";
		_printSpace(12);
		cout << "|" << endl << "| Sila: " << obiekt->getSila()
			<< "  Inicjatywa: " << obiekt->getInicjatywa();
		_printSpace(22 + to_string(obiekt->getSila()).length() + to_string(obiekt->getInicjatywa()).length());
	}
	cout << "|";
	_printLine('=');
}

void Swiat::operator=(Swiat* other) {
	this->_rozmiar = other->_rozmiar;
	this->_tura = other->_tura;
	for (int i = 0; i < organizmySwiata.size(); i++) {
		delete organizmySwiata[i];
	}
	this->organizmySwiata.clear();
	for (int i = 0; i < _listaEventow.size(); i++) {
		delete organizmySwiata[i];
	}
	this->_listaEventow.clear();
	for (auto it = other->organizmySwiata.begin(); it != other->organizmySwiata.end(); ++it) 
	{
		this->pushToWorld(*it);
	}
}

void Swiat::wykonajTure() {
	_tura++;
	_posortujOrganizmy();
	for (int i = 0; i < organizmySwiata.size();i++) {
		Organizm* var = organizmySwiata[i];
		if (var->getCzyPoAkcji()) {
			this->pushEvent(new SystemEvent{ "Obiekt " + var->getID() + " nie mial akcji." });
			var->setCzyPoAkcji(false);
		}
		else if (var->getStun() != 0) {
			this->pushEvent(new SystemEvent{ "Obiekt " + var->getID() + " jest zatrzymany." });
			var->setStun(var->getStun() - 1);
		}
		else {
			var->akcja();
		}
	}
	this->_usunZeSwiata();
}

void Swiat::_usunZeSwiata() {
	for (int i = organizmySwiata.size() - 1; i >= 0; --i) {
		if (organizmySwiata[i]->getCzyMartwy()) {
			Organizm* obiekt = organizmySwiata[i];
			organizmySwiata.erase(organizmySwiata.begin() + i);
			delete obiekt;
		}
	}
}

void Swiat::pushEvent(SystemEvent* e) {
	bool doNotPush = false;
	for (SystemEvent* event : _listaEventow) {
		if (e->getEvent() == event->getEvent()) {
			doNotPush = true;
			break;
		}
	}
	if (!doNotPush) {
		this->_listaEventow.push_back(e);
	}
}

void Swiat::pushToRemove(Organizm* o) {
	this->pushEvent(new SystemEvent("Obiekt " + o->getID() + " umiera. [*]"));
	o->setPolozenie({ -1,-1 });
	o->setCzyMartwy(true);
	o->setCzyPoAkcji(true);
}

void Swiat::pushToWorld(Organizm* o) {
	this->organizmySwiata.push_back(o);
}

