#include "Roslina.h"
#include "Trawa.h"
#include <iostream>
void Trawa::rysowanie(std::ostream& out) {
	out << this->symbol;
};

const std::string Trawa::symbol = "##";