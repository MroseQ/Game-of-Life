#pragma once
#include <iostream>
#include <string>
#include <string.h>
struct SystemEvent {

public:
	SystemEvent(std::string wiadomosc) {
		this->wiadomosc = wiadomosc;
	}
	void wypiszEvent(std::ostream& out) {
		out << this->wiadomosc << std::endl;
	}
	std::string getEvent() { return this->wiadomosc; }

private:
	std::string wiadomosc;

};