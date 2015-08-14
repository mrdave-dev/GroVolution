/* GROVOLUTION - comms.h
 * The header file for comms.cpp
 *
 * Author: Dave Martinez
 * Created: 7/16/15
 *
 */

#ifndef COMMS_H
#define COMMS_H

#include <iostream>
#include <string>

#include "../RS-232/rs232.h"

/* RS232Connection - this class holds data and operations for working
 * with an RS232 Serial connection. It is meant to provide access to
 * the RS-232 library from the GroVolution Bank and Relay system.
 */

class RS232Connection {
	private:
		int baudrate;		// baudrate - data rate at which to transmit
		int piport;			// piport - the port in /dev/ to use
		char mode[4];		// mode - usually set to 8 data bits, odd parity
										// and 1 stop bit.

	public:
		RS232Connection();
		RS232Connection(int, int);

		int getBaudRate();
		int getPiPort();

		void sendText(std::string);
		void readText(std::string &rx);

};

#endif
