#include "Roslina.h"
#include "WilczeJagody.h"
#include <iostream>
#include "Swiat.h"
void WilczeJagody::rysowanie(std::ostream& out) {
	out << this->symbol;
};
void WilczeJagody::kolizja(Organizm* zwierz) {
	this->getSwiat()->pushToRemove(zwierz);
	Roslina::kolizja(zwierz);
}
const std::string WilczeJagody::symbol = "&*";