#pragma once
#include <string>
class Wyjatek
{

public:
	Wyjatek(const char* tx)
	{
		this->tekst = tx;
	}
	Wyjatek(std::string s) {
		this->tekst = s.c_str();
	}
	const char* getTekst() {
		return this->tekst;
	}

private:
	const char* tekst;

};