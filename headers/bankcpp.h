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
#include "../headers/comms.h"
#include "../headers/relay.h"

class Bank {
private:
	std::string file_name;

	int count,
		relay_capacity,
		wake_time,
		light_duration,
		spray_interval,
		spray_duration;

	std::vector<Relay*> relays;
	std::vector<Relay*>::iterator current_relay;

public:
	Bank();
	Bank(std::string);

	void _load(std::string);

	std::string getName();
	int getCount();
	int getWakeTime();
	int getLightDuration();
	int getSprayInterval();
	int getSprayDuration();

	void setName();
	void setWakeTime();
	void setLightDuration();
	void setSprayInterval();
	void setSprayDuration();
	void setTimers(int, int, int, int);

	Relay* _findRelayByID(std::string);

	// System functions. These throw exceptions.
	void _relayAdd(Relay*);
	void _relayDel(Relay*);
	void _relayOn(Relay*);
	void _relayOff(Relay*);
	void _relayToggle(Relay*);

	// Bank functions below use the currentRelay
	// iterator or prompts the user
	void add();
	void remove();
	void on();
	void off();
	void next();
	void prev();
	void rename();
	void inverse();
	void report();
	void report(Relay *);
	void reportAll();
	void reportTimers();
	void help();

};

#endif
