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

// Relay() - no arg constructor
// sets: label to null, number to -1, status to 0;
Relay::Relay() {
	this->label = '\0';
	this->number = -1;
	this->status = 0;
}

// Relay(char, int) - construct with label and number
// @param char ab - the label character
// @param int n - the label number
Relay::Relay(char ab, int n) {
	this->label = ab;
	this->number = n;
	this->status = 0;
}

// Relay(char, int, bool) - construct with label, num. and status
// @param char ab - the label character
// @param int n - the label number
// @param bool s - the relay status to start with
Relay::Relay(char ab, int n, bool s) {
	this->label = ab;
	this->number = n;
	this->status = s;
}

// Relay::getLabel() - return the relay label
// @throws 0 - not set
// @ret label character
char Relay::getLabel() {
	if (this->label == '\0') {throw 0;}
	return this->label;
}

// Relay::getNumber() - returns the relay number
// @throws 0 - not set
// @ret label int
int Relay::getNumber() {
	if (this->number == -1) {throw 0;}
	return this->number;
}

// Relay::getStatus() - returns the relay status
// @throws 0 - not set
// @ret status boolean
bool Relay::getStatus() {
	if (this->number == -1 || this->label == '\0') {throw 0;}
	return this->status;
}

// Relay::getID() - returns the full Relay ID as a string
// @ret the label and number, without extra zeros
std::string Relay::getID() {
	std::stringstream ret_val;
	ret_val << this->getLabel();
	ret_val << this->getNumber();
	return ret_val.str();
}

// Relay::getConnection() - Returns the addr. of the
// relay's RS232Connection
// @throws 0 - not set
// @ret RS232Connection pointer
RS232Connection* Relay::getConnection() {
	if (this->connection == 0) {throw 0;}
	return this->connection;
}

// Relay::setLabel(char) - sets label char
// @param char ab - the character for the label
// @post relay label is ab
void Relay::setLabel(char ab) {
	this->label = ab;
}

// Relay::setNumber(int) - sets Relay number
// @param int n - sets the Relay number
// @post number is n
void Relay::setNumber(int n) {
	this->number = n;
}

// Relay::setStatus(bool) - sets Relay status
// @param bool s - the boolean val to set to
// @post status is s
void Relay::setStatus(bool s) {
	this->status = s;
}

// Relay::setConnection(RS232Connection) - sets the RS232 connection
// @param RS232Connection cx - the addr. of RS232Connection to set to
// @post connection is cx
void Relay::setConnection(RS232Connection* cx) {
	this->connection = cx;
}

// Relay::on() - sends signal to PLC via RS232Connection to turn relay on
// @note output to PLC may contain extra zeros according to PLC communication
// 		standards. However, all references to Relay ID should be done without
//		any leading or trailing zeros or other extra characters
// @throws 0 - RS232Connection not set
// @post relay is on on PLC, status is boolean True
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
		this->status = true;
	} catch (int e) {
		if (check_errors(e)) {
			return;
		}
	}
}

// Relay::off() - sends signal to PLC via RS232Connection to turn relay off
// @note output to PLC may contain extra zeros according to PLC communication
// 		standards. However, all references to Relay ID should be done without
//		any leading or trailing zeros or other extra characters
// @throws 0 - RS232Connection not set
// @post relay is off on PLC, status is boolean false
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
		this->status = false;
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

// Relay::on() - sends signal to PLC via RS232Connection to turn relay on
// @note output to PLC may contain extra zeros according to PLC communication
// 		standards. However, all references to Relay ID should be done without
//		any leading or trailing zeros or other extra characters
// @throws 0 - RS232Connection not set
// @post relay is on on PLC, status is boolean True

// Relay::toggle() - sends signal to PLC via RS232Connection to toggle relay
// @note output to PLC may contain extra zeros according to PLC communication
// 		standards. However, all references to Relay ID should be done without
//		any leading or trailing zeros or other extra characters
// @throws 0 - RS232Connection not set
// @post relay if on if it began as off, or off if on
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

// Relay::report() - outputs text about relay
void Relay::report() {
	std::cout << "RELAY | " << this->label << this->number
	<< "\t | STATUS: " << this->status << "\n";
}
