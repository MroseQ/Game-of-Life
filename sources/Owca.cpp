#include "Zwierze.h"
#include "Owca.h"
#include <iostream>
void Owca::rysowanie(std::ostream& out) {
	out << this->symbol;
};

const std::string Owca::symbol = "C)";