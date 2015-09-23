#include "../headers/bank.h"

Bank::Bank() {
	/*
	// prompt for filename
	std::cout << "NEW BANK \nPlease enter a filename: ";

	std::string user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "FILENAME: " << user_response << "\nIs that correct? (y/n) ";

		std::cin >> user_response;
		if (user_response == "y") {break;}

		std::cout << "NEW BANK \nPlease enter a filename: ";

	}
	this->file_name = user_response;
	*/

	this->connection = nullptr;

	return;
}

Bank::Bank(std::string fn) {
	this->_load(fn);
	this->connection = nullptr;
}

void Bank::_load(std::string fn) {
	std::ifstream fs(fn);

	if (!fs.is_open()) {
		throw 200;  // 1: file did not open
	}

	// put a line in the buffer
	std::string buffer;
	std::smatch match;

	std::regex json_regex("\"(\\S*)\":\\s?\"?([\\d\\w-]*)\"?,?");
	while (std::getline(fs, buffer)) {
		std::regex_search(buffer, match, json_regex);

		if (match[1].str().find(".json") != std::string::npos) {
			// filename
			this->file_name = match[1].str();
		} else if (match[1] == "count") {
			// count
			this->count = std::stoi(match[2].str());
		} else if (match[1] == "relay_capacity") {
			this->relay_capacity = std::stoi(match[2].str());
		} else if (match[1] == "wake_time") {
			this->wake_time = std::stoi(match[2].str());
		} else if (match[1] == "spray_interval") {
			this->spray_interval = std::stoi(match[2].str());
		} else if (match[1] == "spray_duration") {
			this->spray_duration = std::stoi(match[2].str());
		} else if (match[1] == "relays") {
			std::regex relay_regex("\"label\"\\s?:\\s?\"(\\w+)\",\\s?\"number\":\\s?(\\d+),\\s?\"status\":\\s?(\\d+)");
			std::getline(fs, buffer);
			while (std::regex_search(buffer, match, relay_regex)) {
				// extract and type cast matches
				char lb; 	int nm; 	bool st;
				lb = (char) match[1].str()[0];
				nm = std::stoi(match[2]);
				if (match[3] == "1") { st = true;
				} else { st = false; }

				// add to vector
				relays.push_back(new Relay(lb, nm, st));

				// iterate line
				std::getline(fs, buffer);
			}
		}
	}
}


void Bank::_save() {
	// Open the file
	std::ofstream file(this->file_name);

	// filename
	file << "{\"" << this->file_name << "\": {\n";

	// data
	file << "\t\"count\":" << this->count << ",\n";
	file << "\t\"relay_capacity\":" << this->relay_capacity << ",\n";
	file << "\t\"wake_time\":" << this->wake_time << ",\n";
	file << "\t\"light_duration\":" << this->light_duration << ",\n";
	file << "\t\"spray_interval\":" << this->spray_interval << ",\n";
	file << "\t\"spray_duration\":" << this->spray_duration << ",\n";

	// relays
	file << "\t\"relays\": [\n";
	for (unsigned int i=0; i<relays.size(); i++) {
		file << "\t\t\t{\"label\": \"" << relays.at(i)->getLabel() << "\", ";
		file << "\"number\": " << relays.at(i)->getNumber() << ", ";
		file << "\"status\": " << relays.at(i)->getStatus() << "}";
		if (i != (relays.size() - 1)) {
			 file << ",";
		}
		file << "\n";
	}
	file << "\t\t]\n";

	file << "\t}\n";
	file << "}\n";

}


void Bank::_fetchTimers() {
	if (!this->connection) {
        throw 0;	//Unable to fetch timers: Connection not set
	}

	std::string buffer;

	this->connection->sendText("TM\r");
	this->connection->readText(buffer);

	std::regex timer_format("(\\d{5}),(\\d{5}),(\\d{5}),(\\d{5})\\.");
	std::smatch timers;

	// Check for well-formed response
	if (!std::regex_search(buffer, timers, timer_format)) {
		// Timer response not well-formed
		throw 201;
	}

	// Check for 4 timer matches
	if (timers.size() != 5) {
		// Search did not find four timers (and subject)
		throw 202;
	}

	this->wake_time = std::stoi(timers[1].str());
	this->light_duration = std::stoi(timers[2].str());
	this->spray_interval = std::stoi(timers[3].str());
	this->spray_duration = std::stoi(timers[4].str());

}

void Bank::_fetchRelays() {
	if (!this->connection) {
        throw 0;	//Unable to fetch relays: Connection not set
	}

	std::string buffer;

	this->connection->sendText("ST\r");
	this->connection->readText(buffer);

	std::regex status_format("\\b(\\d{22})\\.");
	std::smatch statuses;

	// Check for well-formed response
	if (!std::regex_search(buffer, statuses, status_format)) {
		// Relay response not well-formed
		throw 	203;
	}

	// Iterate through the buffer, set statuses at
	// corresponding relays
	for (unsigned int i=0; i<(buffer.length()-1); i++) {
		relays.at(i)->setStatus(buffer[i] - '0');
	}
}


// Bank::_setFileName - helper method to rename the Bank.
// @param nm - the string to set the Bank name to
// @pre - nm ends with '.json'
// @pre - nm contains only alpha or num or /-_.
// @pre - nm leads with alpha or num
// @throws 206 - doesn't end with .json
// @throws 207 - contains invalid chars
// @throws 208 - doesn't lead with alpha or num
// @post - Bank renamed
void Bank::_setFileName(std::string nm) {
	// REGEX: string ends with '.json'
	std::regex ends_with_json(".+\\.json$");
	if (!std::regex_match(nm, ends_with_json)) {
		// doesn't end with '.json'
		throw 204;
	}

	// REGEX: contains only alpha or num or /-_.
	std::regex not_valid_chars("[^a-zA-Z0-9\\._\\/\\-]");
	if (std::regex_match(nm, not_valid_chars)) {
		// contains invalid chars
		throw 205;
	}

	// REGEX: leads with alpha or num
	std::regex leading_char("^[a-zA-Z0-9]");
	if (std::regex_match(nm, leading_char)) {
		// Doesn't lead with alpha or num
		throw 206;
	}

	// SUCCESS: Bank renamed
	this->file_name = nm;

}

// x hour to wake
void Bank::_setWakeTime(int x) {
	if (x < 0) {
		throw 207;	//invalid wake time
	}

	if (x > 23) {
		throw 207;	//invalid wake time
	}

	std::stringstream text_to_send;
	text_to_send << "TLI" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	if (!this->connection) {
		throw 0;	//Unable to set wake time: Connection not set
	} else {
		this->connection->sendText(text_to_send.str());
		this->_fetchTimers();
	}

}

// x = hours
void Bank::_setLightDuration(int x) {
	if (x < 0) {
		throw 208;	//invalid light duration time
	}

	if (x > 23) {
		throw 208;	//invalid light duration time
	}

	std::stringstream text_to_send;
	text_to_send << "TLD" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	if (!this->connection) {
		throw 0;	//Unable to set light duration: Connection not set
	} else {
		this->connection->sendText(text_to_send.str());
		this->_fetchTimers();
	}
}

// x = minutes
void Bank::_setSprayInterval(int x) {
	if (x < 0) {
		throw 209;	//Invalid spray interval value
	}

	if (x > 3600) {
		throw 209;	//Invalid spray interval value
	}

	std::stringstream text_to_send;
	text_to_send << "TSI" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	if (!this->connection) {
		throw 0;	//Unable to set spray interval: Connection not set
	} else {
		this->connection->sendText(text_to_send.str());
		this->_fetchTimers();
	}
}

// x = seconds
void Bank::_setSprayDuration(int x) {
	if (x < 0) {
		throw 210;	//Invalid spray duration value
	}

	if (x > 30) {
		throw 210;	//Invalid spray duration value
	}

	std::stringstream text_to_send;
	text_to_send << "TSD" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	if (!this->connection) {
		throw 0;
	} else {
		this->connection->sendText(text_to_send.str());
		this->_fetchTimers();
	}
}

void Bank::_setTimers(int wt, int ld, int si, int sd) {
	this->_setWakeTime(wt);
	this->_setLightDuration(ld);
	this->_setSprayInterval(si);
	this->_setSprayDuration(sd);
}

void Bank::_setConnection(RS232Connection* c) {
	this->connection = c;
}

std::string Bank::getName() {
	return this->file_name;
}

int Bank::getCount() {
	return this->count;
}

int Bank::getWakeTime() {
	return this->wake_time;
}

int Bank::getLightDuration() {
	return this->light_duration;
}

int Bank::getSprayInterval() {
	return this->spray_interval;
}

int Bank::getSprayDuration() {
	return this->spray_duration;
}


void Bank::userSetName() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "What would you like the name to be? ";

	std::string user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "NEW FILENAME: " << user_response << "\nIs that correct? (y/n) ";

		std::string user_response_2;
		std::cin >> user_response_2;
		if (user_response_2 == "y") {
			try {
				this->_setFileName(user_response);
				return;
			} catch (int e) {
				if (check_errors(e)) {
					return;
				}
			}
		}
		std::cout << "What would you like the name to be? ";
	}
}

void Bank::userSetWakeTime() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "WAKE TIME: " << this->wake_time << std::endl;
	std::cout << "What should the wake time be? ";

	int user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "NEW WAKE TIME: " << user_response << std::endl;
		std::string user_response_2;
		std::cout << "Is that correct (y/n)? ";
		std::cin >> user_response_2;
		if (user_response_2 == "y") {
			try {
				this->_setWakeTime(user_response);
				return;
			} catch (int e) {
			    if (check_errors(e)) {
				    return;
			    }
            }
		}
		std::cout << "What should the wake time be? ";
	}
}

void Bank::userSetLightDuration() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "LIGHT DURATION: " << this->light_duration << std::endl;
	std::cout << "What should the light duration be? ";

	int user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "NEW LIGHT DURATION: " << user_response << std::endl;
		std::string user_response_2;
		std::cout << "Is that correct (y/n)? ";
		std::cin >> user_response_2;
		if (user_response_2 == "y") {
			try {
				this->_setLightDuration(user_response);
				return;
			} catch (int e) {
				if(check_errors(e)){
					return;	//terminate
				}
			}
		}

		std::cout << "What should the light duration be? ";
	}
}

void Bank::userSetSprayInterval() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "SPRAY INTERVAL: " << this->spray_interval << std::endl;
	std::cout << "What should the spray interval be? ";

	int user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "NEW SPRAY INTERVAL: " << user_response << std::endl;
		std::string user_response_2;
		std::cout << "Is that correct (y/n)? ";
		std::cin >> user_response_2;
		if (user_response_2 == "y") {
			try {
				this->_setSprayInterval(user_response);
				return;
			} catch (int e) {
				if (check_errors(e)) {
					return;	//terminate
				}
			}
		}

		std::cout << "What should the spray interval be? ";
	}
}

void Bank::userSetSprayDuration() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "SPRAY DURATION: " << this->spray_duration << std::endl;
	std::cout << "What should the spray duration be? ";

	int user_response;
	while (std::cin >> user_response) {
		std::cin.ignore(256, '\n');
		std::cin.clear();

		std::cout << "NEW SPRAY DURATION: " << user_response << std::endl;
		std::string user_response_2;
		std::cout << "Is that correct (y/n)? ";
		std::cin >> user_response_2;
		if (user_response_2 == "y") {
			try {
				this->_setSprayDuration(user_response);
				return;
			} catch (int e) {
				if(check_errors(e)) {
					return;	//terminate
				}
			}
		}
		std::cout << "What should the spray duration be? ";
	}
}

void Bank::userSetTimers() {
	this->userSetWakeTime();
	this->userSetLightDuration();
	this->userSetSprayInterval();
	this->userSetSprayDuration();
}


Relay* Bank::_findRelayByID(std::string tv) {
	// This simple linear search could maybe be refactored
	// if the underlying structure for the relays variable
	// was built as a tree or hash table...
	for (unsigned int i=0; i<this->relays.size(); i++) {
		if (this->relays[i]->getID() == tv) {
			return this->relays[i];
		}
	}

	return nullptr;
}

Relay* Bank::_findRelayByID(char lb, int nm) {
	for (unsigned int i=0; i<this->relays.size(); i++) {
		if (this->relays[i]->getLabel() == lb) {
			if (this->relays[i]->getNumber() == nm) {
				return this->relays[i];
			}
		}
	}

	return nullptr;
}

void Bank::_relayAdd(char label, int num) {
	std::stringstream ID;
	ID << label << num;

	if (this->_findRelayByID(ID.str())) {
		throw 211;	//Relay ID already exists
	}

	if (num > 100) {
		throw 212;	//Invalid number value
	}

	if (num < 0) {
		throw 212;	//Invalid number value
	}

	this->relays.push_back(new Relay(label, num));
}

void Bank::_relayDel(char label, int num) {
	std::stringstream ID;
	ID << label << num;

	for (unsigned int i=0; i<relays.size(); i++) {
		if (relays[i]->getID() == ID.str()) {
			relays.erase(relays.begin() + i);
			return;
		}
	}
}

void Bank::_relayOn(char label, int num) {
	if (!this->connection) {
        throw 0;
	}

	std::stringstream ID;
	ID << label << num;

	Relay* rl = _findRelayByID(ID.str());

	if (!rl) {
		throw 213;	//Relay ID not found
	}

	rl->setConnection(this->connection);
	rl->on();
}

void Bank::_relayOff(char label, int num) {
	if (!this->connection) {
        throw 0;
	}

	std::stringstream ID;
	ID << label << num;

	Relay* rl = _findRelayByID(ID.str());

	if (!rl) {
		throw 213;	//Relay ID not found
	}

    rl->setConnection(this->connection);
	rl->off();
}

void Bank::_relayToggle(char label, int num) {
	if (!this->connection) {
        throw 0;
	}

	std::stringstream ID;
	ID << label << num;

	Relay* rl = _findRelayByID(ID.str());

	if (!rl) {
		throw 213;
	}

    rl->setConnection(this->connection);
	rl->toggle();
}

int _getIntFromUser() {
	int t;

	std::string user_response;

	int RELAY_NUM_LOWER_LIMIT = 0;
	int RELAY_NUM_UPPER_LIMIT = 100;



	while (user_response != "q") {
		std::cout << "Please enter a number [" << RELAY_NUM_LOWER_LIMIT
				  << " - " << RELAY_NUM_UPPER_LIMIT << "] or q to quit: ";
		std::getline(std::cin, user_response);

		if (user_response == "q") {
			throw 214;	//User quit
		}

		if (!isdigit(user_response.at(0))) {
			// Doesn't contain digit in first char, not convertible
			std::cout << "That's not a valid number!\n";
		} else if (user_response.length() > 3) {
			// Too long of a sequence
			std::cout << "That's not a valid number!\n";
		} else {
			t = stoi(user_response);
			if (t < RELAY_NUM_LOWER_LIMIT || t > RELAY_NUM_UPPER_LIMIT) {
				// Not in range
				std::cout << "That's not a valid number!\n";
			} else {
				// Success
				return t;
			}
		}

	}

	throw 214;	//User quit
	return t;
}

char _getCharFromUser() {
	char t;
	std::string user_response;

	while (user_response != "quit") {
		std::cout << "Please enter a character [a-zA-Z] or 'quit': ";
		std::getline(std::cin, user_response);

		if (user_response == "quit") {
			throw 214;
		}

		if (user_response.length() > 1) {
			std::cout << "That's not a valid character!\n";
		} else {
			t = user_response[0];
			if (!isalpha(t)) {
				std::cout << "That's not a valid character!\n";
			} else {
				return t;
			}
		}
	}

	throw 214;
	return t;
}

void Bank::add() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "ADD NEW RELAY" << std::endl;

	char label;
	int num;

	std::string user_response;
	while (user_response != "y") {
		try {
			label = _getCharFromUser();
			num = _getIntFromUser();
		} catch (int e) {
			if (check_errors(e)) {
				std::cout << "Bank add failed.";
				return;		//terminate
			}
		}

		std::cout << "Add relay " << label << num << ", is that correct (y/n)? ";
		std::cin >> user_response;

		if (user_response == "y") {
			try {
				this->_relayAdd(label, num);
				return;
			} catch (int e) {
				if(check_errors(e)) {
					return;	//terminate
				}
			}
		}
	}
}

void Bank::add(std::string ab) {
    std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "ADD NEW RELAY" << std::endl;
	std::cout << "INPUT: " << ab << std::endl;

	char a;
	int b;

    a = ab.at(0);
    b = ab.at(1) - '0';

    try {
        this->_relayAdd(a, b);

    } catch (int e) {
        if(check_errors(e)) {
        	return;	//terminate
        }
    }
}

void Bank::remove() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "REMOVE RELAY" << std::endl;

	char label;
	int num;

	std::string user_response;
	while (user_response != "y") {
		try {
			label = _getCharFromUser();
			num = _getIntFromUser();
		} catch (int e) {
			if(check_errors(e)) {
				std::cout << "Bank remove failed.";
				return;		//terminate
			}
		}

		std::cout << "Remove relay " << label << num << ", is that correct (y/n)? ";
		std::cin >> user_response;
        std::cin.ignore(256, '\n');

		if (user_response == "y") {
			try {
				this->_relayDel(label, num);
				return;
			} catch (int e) {
				if(check_errors(e)) {
					return;	//terminate
				}
			}
		}
	}
}

void Bank::on() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "ON: " << std::endl;

	char label;
	int num;

	try {
		label = _getCharFromUser();
		num = _getIntFromUser();
		this->_relayOn(label, num);
	} catch (int e) {
		if (check_errors(e)) {
			std::cout << "On failed.";
			return;		//terminate
		}
	}

	if (Relay* x = _findRelayByID(label, num)) {
		x->report();
	}

}

void Bank::on(std::string ab) {
    std::cout << "BANK: " << this->file_name << std::endl;
    std::cout << "ON: " << ab << std::endl;

    char a;
    int b;
    std::stringstream t;

    a = ab.at(0);

    for (unsigned int i=1; i<ab.length(); i++) {t << ab.at(i);}
    t >> b;
    std::cout << b << std::endl;

    try {
        this->_relayOn(a, b);

    } catch (int e) {
       if(check_errors(e)) {
    	   return;	//terminate
       }
    }
}

void Bank::off() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "OFF: " << std::endl;

	char label;
	int num;

	try {
		label = _getCharFromUser();
		num = _getIntFromUser();
		this->_relayOff(label, num);
	} catch (int e) {
		if(check_errors(e)) {
			std::cout << "Off failed.";
			return;		//terminate
		}
	}

	if (Relay* x = _findRelayByID(label, num)) {
		x->report();
	}
}

void Bank::off(std::string ab) {
    std::cout << "BANK: " << this->file_name << std::endl;
    std::cout << "OFF: " << ab << std::endl;

    char a;
    int b;
    std::stringstream t;

    a = ab.at(0);

    for (unsigned int i=1; i<ab.length(); i++) {t << ab.at(i);}
    t >> b;
    std::cout << b << std::endl;

    try {
        this->_relayOff(a, b);

    } catch (int e) {
        if(check_errors(e)) {
        	return;	//terminate
        }
    }
}

void Bank::allOn() {
    for (unsigned i = 0; i<relays.size(); i++) {
        this->relays.at(i)->setConnection(this->connection);
        this->relays.at(i)->on();
    }
}

void Bank::allOff() {
    for (unsigned i = 0; i<relays.size(); i++) {
        this->relays.at(i)->setConnection(this->connection);
        this->relays.at(i)->off();
    }
}

void Bank::fetch() {
    try {
        this->_fetchTimers();
        this->_fetchRelays();
    } catch (int e) {
        if(check_errors(e)) {
        	return;
        }
    }
}

// void Bank::next() - reports the next relay
void Bank::report() {
	std::cout << "BANK: " << this->file_name << std::endl;
	std::cout << "WAKE TIME: " << this->wake_time << "\t\t";
	std::cout << "LIGHT DUR.: " << this->light_duration << "\t\t\n";
	std::cout << "SPRAY INT.: " << this->spray_interval << "\t\t";
	std::cout << "SPRAY DUR.: " << this->spray_duration << "\t\t\n";
	std::cout << "RELAYS:\n";
	for (unsigned int i=0; i<this->relays.size(); i++) {
		std::cout << "\t" << relays.at(i)->getID() << "\t";
		std::cout << "STATUS: " << relays.at(i)->getStatus();
		std::cout << "\n";
	}
	std::cout << std::endl;
}
