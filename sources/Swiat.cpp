#include "Swiat.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

class PorownajInicjatywe {
public:
	bool operator()(Organizm* a, Organizm* b) const {
		if (a->getInicjatywa() == b->getInicjatywa())
			return a->getAliveSince() < b->getAliveSince();
		return a->getInicjatywa() > b->getInicjatywa();
	}
};

Swiat::Swiat(int rozmiar) {
	this->rozmiar = rozmiar;
	this->tura = 0;
}

void Swiat::rysujSwiat() {
	//system("CLS");
	cout << endl;
	cout << "   |";
	for (int i = 1; i <= rozmiar; i++) {
		string wynik = (i < 10) ? "0" + to_string(i) : to_string(i);
		cout << wynik+"|";
	}
	cout << endl;
	for (int j = 1; j <= rozmiar; j++) {
		
		cout << "----";
		for (int k = 0; k < rozmiar; k++) {
			cout << "---";
		}
		cout << endl;
		string wynik = (j < 10) ? "0" + to_string(j) : to_string(j);
		cout << wynik + " |";
		//tutaj coutowanie organizmów zamiast w przeciwnym razie ten for ni¿ej.
		for (int i = 1; i <= rozmiar; i++) {
			bool pass = false;
			for (Organizm* var : organizmySwiata) {
				if (var->polozenie.x == i && var->polozenie.y == j) {
					var->rysowanie(cout);
					pass = true;
				}
				/*
				if (doNarysowania != nullptr) {
					for (int k = 0; k < 4; k++) {
						try {
							if (doNarysowania[k].x == i && doNarysowania[k].y == j) {
								cout << "0";
								pass = true;
							}
						}
						catch (Wyjatek p) {
							cout << p.tekst;
						}
					}
				}
				*/
			}
			if (!pass) {
				cout << "  ";
			}
			cout << "|";
		}
		cout << endl;
	}
	cout << "====";
	for (int k = 0; k < rozmiar; k++) {
		cout << "===";
	}
	cout << endl <<  "Tura: " << this->tura;
	cout << endl;

	for (auto it = this->listaEventow.begin(); it != this->listaEventow.end(); ++it) {
		(*it)->wypiszEvent(std::cout);
		delete* it;
	}

	this->listaEventow.clear();
}

void Swiat::wykonajTure() {
	tura++;
	organizmySwiata.sort(PorownajInicjatywe());
	for (Organizm* var : organizmySwiata) {
		cout << var->getSila();
		if (!var->czyPoAkcji) {
			var->akcja();
		}
		else {
			this->listaEventow.push_back(new SystemEvent{ "Brak ruchu" });
			var->czyPoAkcji = false;
		}
	}
}
void Swiat::dodajDziecko(Organizm* organizm) {
	this->organizmyDoDodaniaDoSwiata.push_back(organizm);
}

bool Swiat::czyObiektNaPolozeniu(Polozenie* p) {
	for (Organizm* var : organizmySwiata) {
		if (*p == var->getPolozenie()) {
			return true;
		}
	}
	return false;
}

Organizm* Swiat::sprawdzKolizjeNaPolozeniu(Polozenie* p,Organizm* napastnik) {
	int count = 0;
	list<Organizm*> obiektyNaPolozeniu;
	for (Organizm* var : organizmySwiata) {
		if (*p == var->getPolozenie()) {
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
}

