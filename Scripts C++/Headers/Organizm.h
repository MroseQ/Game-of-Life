#pragma once
#include "point.h"
#include <iostream>
#include <string>
using namespace std;
class Swiat;
class Organizm {

public:
	~Organizm() { }
	virtual void akcja() = 0;
	virtual void kolizja(Organizm* kolizator) = 0;
	virtual void rysowanie(std::ostream& out) = 0;

	bool getCzyPoAkcji() { return _czyPoAkcji; }
	void setCzyPoAkcji(bool b) { this->_czyPoAkcji = b; }

	int getStun() { return _stun; }
	void setStun(int value) { this->_stun = value; }

	int getAliveSince() { return _zywyOdTury; }
	void setAliveSince(int tura) { this->_zywyOdTury = tura; }

	static int getKolejneID() { return _kolejneID++; }
	static void setKolejneID(int value) { _kolejneID = value; }

	std::string getID() { return _id; }
	void setID(std::string message) { this->_id = message; }

	int getSila() { return _sila; }
	void setSila(int value) { this->_sila = value; }
	void incSila() { this->_sila++; }

	std::string getType();

	bool getCzyMartwy() { return _czyMartwy; }
	void setCzyMartwy(bool _czyMartwy) { this->_czyMartwy = _czyMartwy; }

	Polozenie getPolozenie() { return this->_polozenie; }
	void setPolozenie(Polozenie p) { this->_polozenie = p; }
	void setPolozenie(int x, int y) { this->_polozenie = Polozenie{ x,y }; }
	void addPolozenie(int x, int y) { this->_polozenie.x += x; this->_polozenie.y += y; }

	int getInicjatywa() { return _inicjatywa; }
	void incInicjatywa() { this->_inicjatywa++; }

	Polozenie getPopPolozenie() { return _poprzedniePolozenie; }
	void setPopPolozenie(Polozenie p) { this->_poprzedniePolozenie = p; }

	Swiat* getSwiat() { return _swiat; }
	void setSwiat(Swiat* swiat) { this->_swiat = swiat; }

protected:
	Organizm(std::string prefiks, int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat, bool _czyPoAkcji = false, string* id = nullptr);

private:
	bool _czyMartwy, _czyPoAkcji;
	static int _kolejneID;
	int _stun, _sila, _inicjatywa, _poczatkowaSila, _poczatkowaInicjatywa, _zywyOdTury;
	std::string _id;
	Swiat* _swiat;
	Polozenie _polozenie, _poprzedniePolozenie;
};
