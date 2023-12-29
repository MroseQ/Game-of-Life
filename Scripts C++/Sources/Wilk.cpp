#include "Zwierze.h"
#include "Wilk.h"
#include <iostream>
void Wilk::rysowanie(std::ostream& out){
	out << this->symbol;
};
const std::string Wilk::symbol = "^^";