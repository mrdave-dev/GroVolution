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

void sendText(std::string tx) {

}
