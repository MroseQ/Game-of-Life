#include "Organizm.h"
#include <cstdlib>
#include <iostream>
#include "Swiat.h"

Organizm::Organizm(int sila, int inicjatywa, Polozenie* polozenie, Swiat& swiat, bool czyPoAkcji) {
	this->sila = sila;
	this->poczatkowaSila = sila;
	this->inicjatywa = inicjatywa;
	this->poczatkowaInicjatywa = inicjatywa;
	this->swiat = &swiat;
	this->swiat->organizmySwiata.push_back(this);
	this->poprzedniePolozenie = { -1,-1 };
	this->czyPoAkcji = czyPoAkcji;
	this->zywyOdTury = this->swiat->tura;
	if (polozenie == nullptr) {
		this->polozenie.x = rand() % swiat.rozmiar + 1;
		this->polozenie.y = rand() % swiat.rozmiar + 1;
	}
	else {
		this->polozenie = *polozenie;
	}
}