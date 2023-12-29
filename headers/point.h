#pragma once
#include "Wyjatek.h"
#include <iostream>
#include <cmath>
#include "Settings.h"
struct Polozenie{
public:
	int x;
	int y;

	bool operator==(const Polozenie& other) const {
		return x == other.x && y == other.y;
	}

	friend std::ostream& operator<<(std::ostream& out, const Polozenie& polozenie) {
		out << polozenie.x << "," << polozenie.y;
		return out;
	}

	// Operator s¹siednich po³o¿eñ - 
	// przyjmuje dwa po³o¿enia i zwraca wszystkie s¹siaduj¹ce po³o¿enia.
	std::pair<Polozenie*,int> operator^(const Polozenie& other) const {
		Polozenie* lista = new Polozenie[4];
		int size = 4;
		if (this->x == other.x && this->y == other.y) {
			lista = new Polozenie[8];
			int x = this->x;
			int y = this->y;
			int index = 0;
			if (x > 1) {
				lista[index] = Polozenie{ x - 1,y };
				index++;
				if (y > 1) {
					lista[index] = Polozenie{ x - 1,y - 1 };
					index++;
				}
				if (y < N) {
					lista[index] = Polozenie{ x - 1,y + 1 };
					index++;
				}
			}
			if (x < N) {
				lista[index] = Polozenie{ x + 1,y };
				index++;
				if (y > 1) {
					lista[index] = Polozenie{ x + 1,y - 1 };
					index++;
				}
				if (y < N) {
					lista[index] = Polozenie{ x + 1,y + 1 };
					index++;
				}
			}
			if (y > 1) {
				lista[index] = Polozenie{ x ,y - 1 };
				index++;
			}
			if (y < N) {
				lista[index] = Polozenie{ x ,y + 1 };
				index++;
			}
			size = index;
		}
		else {
			if (this->y == other.y) {
				int index = 0;
				if (this->y + 1 <= N) {
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
				if (this->x + 1 <= N) {
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
				int distanceX = std::pow((this->x - other.x), 2), distanceY = std::pow((this->y - other.y), 2);
				if (distanceX == 1 && distanceY == 1) {
					size = 2;
					lista[0] = Polozenie{ this->x,other.y };
					lista[1] = Polozenie{ other.x,this->y };
				}
				else {
					throw Wyjatek("Polozenia nie sa sasiadujace.");
				}
			}
		}
		return std::make_pair(lista,size);
	}
};