#include "Organizm.h"
#include "Swiat.h"
#include <cstdlib>
#include <ctime>
#include <random>

int Organizm::_kolejneID = 0;


Organizm::Organizm(std::string prefiks, int sila, int inicjatywa, Polozenie* polozenie, Swiat* swiat,  bool czyPoAkcji, string* id) 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, N);
	if (id == nullptr) {
		this->_id = prefiks + to_string(this->getKolejneID());
	}
	else {
		this->_id = *id;
	}
	this->_stun = 0;
	this->_sila = sila;
	this->_poczatkowaSila = sila;
	this->_inicjatywa = inicjatywa;
	this->_poczatkowaInicjatywa = inicjatywa;
	this->_swiat = swiat;
	this->_swiat->pushToWorld(this);
	this->_poprzedniePolozenie = { -1,-1 };
	this->_czyPoAkcji = czyPoAkcji;
	this->_zywyOdTury = this->_swiat->getTura();
	int nowyX, nowyY;
	if (polozenie == nullptr) {
		do {
			nowyX = dist(gen);
			nowyY = dist(gen);
		} while (this->_swiat->czyObiektNaPolozeniu(nowyX,nowyY));
		this->_polozenie.x = nowyX;
		this->_polozenie.y = nowyY;
	}
	else {
		this->_polozenie = *polozenie;
	}
}

std::string Organizm::getType() {
	string result;
	result = typeid(*this).name();
	result = result.substr(6);
	return result;
}