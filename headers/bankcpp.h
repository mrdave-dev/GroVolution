/* GROVOLUTION - bank.h
 * A header file for the Bank class. A Bank provides
 * a interface for a collection of relays.
 *
 * Author: Dave Martinez
 * Created: July 23, 2015
 * Modified:
 */

#ifndef BANK_H
#define BANK_H

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

#include "../RS-232/rs232.h"
#incldue "../headers/comms.h"
#include "../headers/relay.h"

class Bank {
private:
	std::string fileName;

	int count,
		relayCapacity,
		wakeTime,
		lightDuration,
		sprayInterval,
		sprayDuration;



}

#endif
