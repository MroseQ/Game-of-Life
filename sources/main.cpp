#include "Swiat.h"
#include "Zwierze.h"
#include "Wilk.h"
#include "Owca.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Roslina.h"
#include "Trawa.h"
#include "Komar.h"
#include "Guarana.h"
#include "Jez.h"
#include "WilczeJagody.h"
#include "Zolw.h"
#include <limits>
#include <cctype>
using namespace std;

int main() {
	Swiat* s1 = new Swiat();
	Komar* k1 = new Komar(2, 1, nullptr, s1);

	//Przyk³ad konstruktora kopiuj¹cego;
	/*
	Komar kt = *k1;
	Komar* kt2 = &kt;
	kt2.setPolozenie(Polozenie{ 8,7 });
	kt2.getSwiat()->pushToWorld(&kt);
	cout << kt.getPolozenie() << "  " << kt2->getPolozenie();
	delete kt2;
	*/

	Komar* k3 = new Komar(2, 1, nullptr, s1);
	Owca* o1 = new Owca(4, 4, nullptr, s1);
	Owca* o2 = new Owca(4, 4, nullptr, s1);
	Wilk* w1 = new Wilk(9, 5, nullptr, s1);
	Wilk* w2 = new Wilk(9, 5, nullptr, s1);
	Trawa* t1 = new Trawa(nullptr, s1);
	//Trawa t2(nullptr, s1);
	//Trawa t3(nullptr, s1);
	WilczeJagody* wj1 = new WilczeJagody(nullptr, s1);
	WilczeJagody* wj2 = new WilczeJagody(nullptr, s1);
	
	Zolw* z1 = new Zolw(2, 1, nullptr, s1);
	Zolw* z2 = new Zolw(2, 1, nullptr, s1);
	Zolw* z3 = new Zolw(2, 1, nullptr, s1);
	
	Zebra* zb1 = new Zebra(4, 6, nullptr, s1);
	Zebra* zb2 = new Zebra(4, 6, nullptr, s1);

	Jez* j1 = new Jez(2,3,nullptr,s1);
	Jez* j2 = new Jez(2, 3, nullptr, s1);
	Jez* j3 = new Jez(2, 3, nullptr, s1);

	Guarana* g1 = new Guarana(nullptr, s1);
	Guarana* g2 = new Guarana(nullptr, s1);
	//Guarana* g3 = new Guarana(nullptr, s1);
	
	bool pass = false;
	char klawisz;
	while (1) {
		pass = false;
		s1->rysujSwiat();
		while (!pass) {
			klawisz = _getch();
			if (klawisz == 's') {
				s1->zapiszSwiat();
			}
			else if (klawisz == 'l') {
				//usuwanie poprzednich organizmow z poprzedniego swiata
				Swiat* newSwiat = s1->wczytajSwiat();
				if (newSwiat != nullptr) {
					*s1 = newSwiat;
					delete newSwiat;
					for (auto it = s1->organizmySwiata.begin(); it != s1->organizmySwiata.end(); ++it)
					{
						(*it)->setSwiat(s1);
					}
				}
				klawisz = _getch();
				pass = true;
			}
			else if (klawisz == 'f') {
				s1->fetch();
			}
			else {
				s1->wykonajTure();
				pass = true;
			}
		}
	}
	delete s1;
	return 0;
}
