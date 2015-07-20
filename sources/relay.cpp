/* GROVOLUTION - relay.cpp
 * A source file for the Relay class. Relays provide an interface
 * for modifying and storing data about the PLC's individual
 * relays.
 *
 * Author: Dave Martinez
 * Created: July 20, 2015
 * Modified:
 */

#include "../headers/relaycpp.h"

Relay::Relay() {
	this->label = '\0';
	this->number = -1;
	this->status = 0;
}

Relay::Relay(char ab, int n) {
	this->label = ab;
	this->number = n;
	this->status = 0;
}

Relay::Relay(char ab, int n, bool s) {
	this->label = ab;
	this->number = n;
	this->status = s;
}

char Relay::getLabel() {
	return this->label;
}

int Relay::getNumber() {
	return this->number;
}

bool Relay::getStatus() {
	return this->status;
}

void Relay::setLabel(char ab) {
	this->label = ab;
}

void Relay::setNumber(int n) {
	this->number = n;
}

void Relay::setStatus(bool s) {
	this->status = s;
}

void Relay::on() {
	string tx;

	tx += 'R';
	tx += '1';
	tx += this->label;
	tx += '0';
	if (this->number >= 10) {
		int firstDigit = this->number;
		firstDigit /= 10;

		tx += firstDigit + '0';
		tx += (r->number % 10) + '0';
	} else {
		tx += '0';
		tx += r->number + '0';
	}

	tx += '\r';
	tx += '\0';

	try {
		this->connection->sendText(tx);
	} catch (int e) {
		switch (e):
			0:
				std::cout << "ERROR: RS232 connection not set.\n";
				break;
			1:
				std:cout << "ERROR: Unable to make RS232 connection.\n";
	}

}
	Relay::off();
	Relay::toggle();
	Relay::report();
*/
