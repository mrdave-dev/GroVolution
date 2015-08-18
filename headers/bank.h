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
#include <cctype>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

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

	RS232Connection* connection;

public:
	Bank();
	Bank(std::string);

	// Internal file functions
	void _load(std::string);
	void _save();

	// Internal functions to fetch from the PLC
	void _fetchTimers();
	void _fetchRelays();

	// Internal functions to set things
	void _setFileName(std::string);
	void _setWakeTime(int);
	void _setLightDuration(int);
	void _setSprayInterval(int);
	void _setSprayDuration(int);
	void _setTimers(int, int, int, int);
	void _setConnection(RS232Connection*);

	// Get methods
	std::string getName();
	int getCount();
	int getWakeTime();
	int getLightDuration();
	int getSprayInterval();
	int getSprayDuration();

	void userSetName();
	void userSetWakeTime();
	void userSetLightDuration();
	void userSetSprayInterval();
	void userSetSprayDuration();
	void userSetTimers();

	Relay* _findRelayByID(std::string);
	Relay* _findRelayByID(char, int);

	// System functions. These throw exceptions.
	void _relayAdd(char, int);
	void _relayDel(char, int);
	void _relayOn(char, int);
	void _relayOff(char, int);
	void _relayToggle(char, int);

	// Bank functions below use the currentRelay
	// iterator or prompts the user
	void add();
	void add(std::string);
	void remove();
	void remove(std::string);
	void on();
	void on(std::string);
	void off();
	void off(std::string);
	void allOn();
	void allOff();
	//void next();
	//void prev();
	//void rename();
	//void inverse();
	void fetch();
	void report();
	//void report(Relay *);
	//void reportAll();
	//void reportTimers();
	//void help();

};

#endif
