/* GROVOLUTION - relay.h
 * A header file for the relay class. Relays provide an interface
 * for modifying and storing data about the PLC's individual
 * relays.
 *
 * Author: Dave Martinez
 * Created: July 20, 2015
 * Modified: Aug. 13, 2015
 */

#ifndef RELAY_H
#define RELAY_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "../RS-232/rs232.h"
#include "../headers/comms.h"
#include "../headers/error.h"

/* Relay - an object class to provide controls and data storage for
 * relays/switches on a programmable logic controller.
 */
class Relay {
private:
	char label;		// identifying char for relay
	int number;		// identifying number fo relay
	bool status;	// status of relay, true for on, false for off
	RS232Connection* connection;	// connection to use for PLC communications
	gv_error error;		//check for error type in case of exception

public:
	// Constructors
	Relay();
	Relay(char, int);
	Relay(char, int, bool);

	// get member data
	char getLabel();
	int getNumber();
	bool getStatus();
	std::string getID();
	RS232Connection* getConnection();

	// set member data
	void setLabel(char);
	void setNumber(int);
	void setStatus(bool);
	void setConnection(RS232Connection*);

	// send signals to PLC to turn relays on, off or opposite
	void on();
	void off();
	void toggle();

	// Output data to terminal
	void report();

};

#endif
