<<<<<<< HEAD
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

	void setLabel(char);
	void setNumber(int);
	void setStatus(bool);

	void on();
	void off();
	void toggle();
	void report();

};

#endif
=======
/* GROVOLUTION - relay.c
 * Class definitions for the relay object.
 *
 * Author: Dave Martinez
 * Created: 7/16/15
 *
 */

 #ifndef RELAY_H
 #define RELAY_H

 class relay {
 	private:
 		int number;
 		bool status;
 		char label;
 		RS232Connection connection;

	public:
		int getNumber();
		bool getStatus();
		getLabel();

		void setNumber();
		void setStatus();
		void setLabel();

		void on();
		void off();

		void printInfo();

 }






 #endif
>>>>>>> refactor.comms
