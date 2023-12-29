#include "Zwierze.h"
#include "Zolw.h"
#include <iostream>
#include <random>
#include <string>
void Zolw::rysowanie(std::ostream& out) {
	out << this->symbol;
};

void Zolw::akcja() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> percentage(1, 100);
	if (percentage(gen) > 75) {
		Zwierze::akcja();
	}
}

const std::string Zolw::symbol = "o@";