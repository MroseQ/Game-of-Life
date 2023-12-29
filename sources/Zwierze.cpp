#include "Organizm.h"
#include "Zwierze.h"
#include <cstdlib>
#include <iostream>
#include "Swiat.h"
#include "Wilk.h"
#include "Zolw.h"
#include "SystemEventow.h"
#include <string>
#include <random>
#include "Komar.h"
#include "Jez.h"
#include "Roslina.h"
#include "Zebra.h"

void Zwierze::rysowanie(std::ostream& out) {
	std::cout << "EZ";
}

void Zwierze::akcja()  {
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> threeWay(-1, 1);
	std::uniform_int_distribution<int> doubleWay(0, 1);
	int randX, randY;
	do {
		if (this->getPolozenie().x == 1) randX = doubleWay(gen);
		else if (this->getPolozenie().x == N) randX = doubleWay(gen) - 1;
		else randX = threeWay(gen);

		if (this->getPolozenie().y == 1) randY = doubleWay(gen);
		else if (this->getPolozenie().y == N) randY = doubleWay(gen) - 1;
		else randY = threeWay(gen);
		
	} while (randX == 0 && randY == 0);
	this->setPopPolozenie(this->getPolozenie());
	this->addPolozenie(randX, randY);
	if (Organizm* kolizator = this->getSwiat()->sprawdzKolizjeNaPolozeniu(this->getPolozenie(), this)) {
		this->kolizja(kolizator);
	}
	else {
		this->getSwiat()->pushEvent(new SystemEvent("Ruch obiektu " + this->getID() + 
			" na -> (" + to_string(this->getPolozenie().x) + "," + to_string(this->getPolozenie().y) + ")"));
	}
}

void Zwierze::kolizja(Organizm* kolizator){
	const type_info& typKolizatora = typeid(*kolizator);
	const type_info& typObiektu = typeid(*this);
	if (typObiektu == typKolizatora) {
		this->setPolozenie(this->getPopPolozenie());
		this->rozmnoz(this->getSwiat(), this->getPolozenie(), kolizator->getPolozenie());
		kolizator->setCzyPoAkcji(true);
	}
	else {
		if (dynamic_cast<Roslina*>(kolizator) != nullptr) {
			kolizator->kolizja(this);
		}
		else {
			if (typeid(Zolw) == typKolizatora && this->getSila() < 5) {
				this->getSwiat()->pushEvent(new SystemEvent{ kolizator->getID() + " obronil sie przed " + this->getID()});
				this->setPolozenie(this->getPopPolozenie());
			}
			//Jezeli zebra zostanie zaatakowana w parzystej turze to ucieka przed napastnikiem, 
			// na pole wczesniej zajmowane przez napastnika
			else if (typeid(Zebra) == typKolizatora && this->getSwiat()->getTura() % 2 == 0) {
				this->getSwiat()->pushEvent(new SystemEvent{ kolizator->getID() + " uciekla przed " + this->getID() });
				kolizator->setPolozenie(this->getPopPolozenie());
			}
			else {
				this->walka(kolizator);
			}
		}
	}
}

void Zwierze::walka(Organizm* obronca) {
	Organizm* wygrany;
	Organizm* przegrany;
	bool przegranyPrzezywa = false;
	if (obronca->getSila() > this->getSila()) {
		wygrany = obronca;
		przegrany = this;
	}
	else {
		wygrany = this;
		przegrany = obronca;
	}
	if (typeid(*przegrany) == typeid(Komar)) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> coin(0,1);
		if (coin(gen) == 1) {
			przegranyPrzezywa = true;
		}
	}
	if (typeid(*przegrany) == typeid(Jez)) {
		this->getSwiat()->pushEvent(new SystemEvent
			{przegrany->getID() + " okaleczyl i zestunowal obiekt " + wygrany->getID()}
		);
		wygrany->setStun(2);
	}
	if (!przegranyPrzezywa) {
		this->getSwiat()->pushToRemove(przegrany);
		this->getSwiat()->pushEvent(new SystemEvent
			{ wygrany->getID() + " wygral walke z obiektem " + przegrany->getID() });
	}
	else {
		if (typeid(*przegrany) == typeid(Komar)) {
			this->getSwiat()->pushEvent(new SystemEvent
				{ przegrany->getID() + " przezyl walke z obiektem " + wygrany->getID() });
			przegrany->setPolozenie(przegrany->getPopPolozenie());
		}
	}
}

void Zwierze::rozmnoz(Swiat* swiat, Polozenie alfa, Polozenie beta) {
	try {
		pair<Polozenie*,int> lista = alfa ^ beta;
		Polozenie* mozliwePolozenia = lista.first;
		Polozenie* polozenieNowegoOsobnika = nullptr;

		//sprawdzanie dostêpnych s¹siaduj¹cych pozycji, czy przynajmniej jedno nie jest zajête.
		for (int i = 0; i < lista.second; i++) {
			if (!this->getSwiat()->czyObiektNaPolozeniu(&mozliwePolozenia[i])) {
				polozenieNowegoOsobnika = &mozliwePolozenia[i];
				break;
			}
		}

		// je¿eli nie ma ¿adnego obiektu na mo¿liwym po³o¿eniu, to tworzone jest dziecko.
		if (polozenieNowegoOsobnika != nullptr) {
			this->getSwiat()->pushEvent(new SystemEvent("Gatunek " + this->getType() 
				+ " urodzil dziecko na -> (" + to_string(polozenieNowegoOsobnika->x) + "," + to_string(polozenieNowegoOsobnika->y) +")"));
			Organizm* a = this->utworzDziecko(this->getSwiat(), polozenieNowegoOsobnika);
		}

		// je¿eli wszystkie pozycje s¹ zajête, gatunek siê wstydzi i nie tworzy dziecka.
		else {
			this->getSwiat()->pushEvent(new SystemEvent( "Gatunek " + this->getType() + " byl niesmialy wiec nie bylo dziecka."));
		}
	}
	
	//wyj¹tek dla przypadkowego wprowadzenia dwóch po³o¿eñ nies¹siaduj¹cych lub tego samego po³o¿enia.
	catch (Wyjatek& w) {
		cout << "Wyjatek: " << w.getTekst();
	}
	
}