/* GROVOLUTION - comms.cpp
 * An implementation file of the comms.h header
 *
 * Author: Dave Martinez
 * Created: 7/16/15
 *
 */

#include "../headers/comms.h"

// RS232Connection() - blank constructor
// Creates a new RS232Connection and sets baudrate and piport
// 		invalid values. Sets mode to 8 bits, odd parity, 1 stop
//		bit.
RS232Connection::RS232Connection() {

	this->baudrate = -1;
	this->piport = -1;
	mode[0] = '8'; mode[1] = 'O';
	mode[2] = '1'; mode[3] = '\0';

}

// RS232Connection(int, int) - constructor to enter
// 		piport and baudrate. Sets mode to 8 bits, odd parity
// 		and 1 stop bit.
// @param b - target baudrate
// @param p - target port
RS232Connection::RS232Connection(int b, int p) {
	this->baudrate = b;
	this->piport = p;
	mode[0] = '8'; mode[1] = 'O';
	mode[2] = '1'; mode[3] = '\0';
}

// RS232Connection::getBaudRate() - returns baud rate as int
// @ret int baudrate
int RS232Connection::getBaudRate() {
	return this->baudrate;
}

// RS232Connection::getPiPort() - returns the pi port
// @ret int piport
int RS232Connection::getPiPort() {
	return this->piport;
}

// RS232Connection::sendText(std::string) - sends text
// 		as serial communication over port using settings
// @throws 0 - connection not set
// @throws 1 - unable to connect
// @post data sent over port
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

// RS232Connection::readText(std::string &) - reads text
// 		from piport and saves to string
// @param std::string &rx - addr of string to save text to
// @throws 0 - connection not set
// @throws 1 - unable to connect
// @post rx = text read from piport
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
