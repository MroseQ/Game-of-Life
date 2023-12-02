#include "Swiat.h"
#include "Zwierze.h"
#include "Wilk.h"
#include "Owca.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

int main() {
	Swiat s1(20);
	Polozenie a = { 5,1 };
	Polozenie b = { 6,1 };
	Polozenie c = { 5,2 };
	Polozenie d = { 6,2 };
	Wilk wilk(8, 5, &a, s1);
	Wilk wilk2(7, 5, &b, s1);
	Wilk wilk3(1, 5, &c, s1);
	Wilk wilk4(2, 5, &d, s1);
	//Owca o1(4, 4, nullptr, s1);
	bool pass = false;
	char klawisz;
	while (1) {
		s1.rysujSwiat();
		klawisz = _getch();
		s1.wykonajTure();
	}
	cout << endl;
	cout << wilk.inicjatywa << "   " << wilk.polozenie.x << " " << wilk.polozenie.y;
	
	return 0;
}