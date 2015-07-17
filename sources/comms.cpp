/* GROVOLUTION - comms.cpp
 * An implementation file of the comms.h header
 *
 * Author: Dave Martinez
 * Created: 7/16/15
 *
 */

#include "../headers/commscpp.h"

RS232Connection::RS232Connection() {
	this->baudrate = -1;
	this->piport = -1;
	mode[0] = 0; mode[1] = 0;
	mode[2] = 0; mode[3] = 0;

}

RS232Connection::RS232Connection(int b, int p) {
	this->baudrate = b;
	this->piport = p;
}

int RS232Connection::getBaudRate() {
	return this->baudrate;
}

int RS232Connection::getPiPort() {
	return this->piport;
}

void RS232Connection::sendText(std::string tx) {
	if (this->baudrate < 0
	|| this->piport < 0
	|| this->mode[0] == 0) {
		throw 0;	// 0: RS232 connection not set
	}

	int port_status = RS232_OpenComport(this->piport, this->baudrate, this->mode);
	if (port_status == 1) {
		throw 1; // 1: Unable to make RS232 connection
	}

	RS232_cputs(this->piport, tx.c_str());

	RS232_CloseComport(this->piport);
}

void RS232Connection::readText(std::string &rx) {
	if (this->baudrate < 0
	|| this->piport < 0
	|| this->mode[0] == 0) {
		throw 0;	// 0: RS232 connection not set
	}

	int port_status = RS232_OpenComport(this->piport, this->baudrate, this->mode);
	if (port_status == 1) {
		throw 1; // 1: Unable to make RS232 connection
	}

	int i=0;
	unsigned char buffer[100];
	while (i < 20) {
		int n = RS232_PollComport(this->piport, buffer, 99);

		if (n > 0) {
			buffer[n] = 0;

			for (int x=0; x<n; x++) {
				if (buffer[x] < 32) {
					buffer[x] = '.';
				}
			}
			break;
		}
		i++;
	}

	rx = (reinterpret_cast<char*>(buffer));

}
