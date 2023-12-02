#pragma once
#include <iostream>
#include <string>
#include <string.h>
struct SystemEvent {
public:
	std::string wiadomosc;
	void wypiszEvent(std::ostream& out) {
		out << wiadomosc << std::endl;
	}
};