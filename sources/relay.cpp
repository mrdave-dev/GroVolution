/* GROVOLUTION - relay.cpp
 * A source file for the Relay class. Relays provide an interface
 * for modifying and storing data about the PLC's individual
 * relays.
 *
 * Author: Dave Martinez
 * Created: July 20, 2015
 * Modified:
 */

#include "../headers/relay.h"

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
	if (this->label == '\0') {throw 0;}
	return this->label;
}

int Relay::getNumber() {
	if (this->number == -1) {throw 0;}
	return this->number;
}

bool Relay::getStatus() {
	if (this->number == -1 || this->label == '\0') {throw 0;}
	return this->status;
}

RS232Connection* Relay::getConnection() {
	if (this->connection == 0) {throw 0;}
	return this->connection;
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

void Relay::setConnection(RS232Connection* cx) {
	this->connection = cx;
}

void Relay::on() {
	if(this->connection == 0) {throw 0;}

	std::string tx;

	tx += 'R';
	tx += '1';
	tx += this->label;
	tx += '0';
	if (this->number >= 10) {
		int firstDigit = this->number;
		firstDigit /= 10;

		tx += firstDigit + '0';
		tx += (this->number % 10) + '0';
	} else {
		tx += '0';
		tx += this->number + '0';
	}

	tx += '\r';
	tx += '\0';

	try {
		this->connection->sendText(tx);
	} catch (int e) {
		switch (e) {
			case 0:
				std::cout << "ERROR: RS232 connection variables not set.\n";
				break;

			case 1:
				std::cout << "ERROR: Unable to make RS232 connection.\n";
				break;

			default:
				std::cout << "ERROR: Unknown error (" << e << ")\n";
		}
	}
}

void Relay::off() {
	std::string tx;

	tx += 'R';
	tx += '0';
	tx += this->label;
	tx += '0';
	if (this->number >= 10) {
		int firstDigit = this->number;
		firstDigit /= 10;

		tx += firstDigit + '0';
		tx += (this->number % 10) + '0';
	} else {
		tx += '0';
		tx += this->number + '0';
	}

	tx += '\r';
	tx += '\0';

	try {
		this->connection->sendText(tx);
	} catch (int e) {
		switch (e) {
			case 0:
				std::cout << "ERROR: RS232 connection not set.\n";
				break;

			case 1:
				std::cout << "ERROR: Unable to make RS232 connection.\n";
				break;

			default:
				std::cout << "ERROR: Unknown error (" << e << ")\n";
		}
	}
}

void Relay::toggle() {
	std::string tx;

	tx += 'R';

	if (this->status) {tx += '1';}
	else {tx += '0';}

	tx += this->label;
	tx += '0';
	if (this->number >= 10) {
		int firstDigit = this->number;
		firstDigit /= 10;

		tx += firstDigit + '0';
		tx += (this->number % 10) + '0';
	} else {
		tx += '0';
		tx += this->number + '0';
	}

	tx += '\r';
	tx += '\0';

	try {
		this->connection->sendText(tx);
	} catch (int e) {
		switch (e) {
			case 0:
				std::cout << "ERROR: RS232 connection not set.\n";
				break;

			case 1:
				std::cout << "ERROR: Unable to make RS232 connection.\n";
				break;

			default:
				std::cout << "ERROR: Unknown error (" << e << ")\n";
		}
	}
}

void Relay::report() {
	std::cout << "RELAY | " << this->label << this->number
	<< "\t | STATUS: " << this->status << "\n";
}
