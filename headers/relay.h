/* GROVOLUTION - relay.h
 * A header file for the relay class. Relays provide an interface
 * for modifying and storing data about the PLC's individual
 * relays.
 *
 * Author: Dave Martinez
 * Created: July 20, 2015
 * Modified:
 */

#ifndef RELAY_H
#define RELAY_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "../RS-232/rs232.h"
#include "../headers/comms.h"

class Relay {
private:
	char label;
	int number;
	bool status;
	RS232Connection* connection;

public:
	Relay();
	Relay(char, int);
	Relay(char, int, bool);

	char getLabel();
	int getNumber();
	bool getStatus();
	std::string getID();
	RS232Connection* getConnection();

	void setLabel(char);
	void setNumber(int);
	void setStatus(bool);
	void setConnection(RS232Connection*);

	void on();
	void off();
	void toggle();
	void report();

};

#endif
