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

class RS232Connection {
	private:
		int baudrate;
		int piport;
		char mode[4];

	public:
		RS232Connection();
		RS232Connection(int, int);

		int getBaudRate();
		int getPiPort();

		void sendText(std::string);
		void readText(std::string rx);

};


#endif
