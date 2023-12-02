#pragma once
#include "Wyjatek.h"
#include <iostream>
struct Polozenie{
public:
	int x;
	int y;

	bool operator==(const Polozenie& other) const {
		return x == other.x && y == other.y;
	}
	/*
	Polozenie operator=(Polozenie other) {
		if (this != &other) {
			this->x = other.x;
			this->y = other.y;
		}
		return *this;
	}
	*/

	friend std::ostream& operator<<(std::ostream& out, const Polozenie& polozenie) {
		out << "Polozenie: x=" << polozenie.x << "   y=" << polozenie.y;
		return out;
	}

	std::pair<Polozenie*,int> operator^(const Polozenie& other) const {
		Polozenie* lista = new Polozenie[4];
		int size = 4;
		if (this->x == other.x && this->y == other.y) {
			throw Wyjatek("Sasiednie pozycje jednego po³ozenia.");
		}
		if (this->y == other.y) {
			int index = 0;
			if (this->y + 1 <= 20) {
				lista[index] = Polozenie{ this->x,this->y + 1 };
				index++;
				lista[index] = Polozenie{ other.x, this->y + 1 };
				index++;
			}
			else {
				size -= 2;
			}
			if (this->y - 1 > 0) {
				lista[index] = Polozenie{ this->x, this->y - 1 };
				index++;
				lista[index] = Polozenie{ other.x, this->y - 1 };
				index++;
			}
			else {
				size -= 2;
			}
		}
		else if (this->x == other.x) {
			int index = 0;
			if (this->x + 1 <= 20) {
				lista[index] = Polozenie{ this->x + 1,this->y };
				index++;
				lista[index] = Polozenie{ this->x + 1, other.y };
				index++;
			}
			else {
				size -= 2;
			}
			if (this->x - 1 > 0) {
				lista[index] = Polozenie{ this->x - 1, this->y };
				index++;
				lista[index] = Polozenie{ this->x - 1, other.y };
				index++;
			}
			else {
				size -= 2;
			}
		}
		else {
			int distanceX = pow((this->x - other.x),2), distanceY = pow((this->y - other.y),2);
			if (distanceX == 1 && distanceY == 1) {
				size = 2;
				lista[0] = Polozenie{this->x,other.y};
				lista[1] = Polozenie{other.x,this->y};
			}
			else {
				throw Wyjatek("Polozenia nie sa sasiadujace.");
			}
		}
		return std::make_pair(lista,size);
	}
};