#include "../headers/bankcpp.h"

Bank::Bank() {
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

	return;
}

Bank::Bank(std::string fn) {
	this->_load(fn);
}

void Bank::_load(std::string fn) {
	std::ifstream fs(fn);

	if (!fs.is_open()) {
		throw 1;  // 1: file did not open
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
	std::string buffer;

	this->connection->sendText("TM\r");
	this->connection->readText(buffer);

	std::regex timer_format("\\[(\\d{5}),(\\d{5}),(\\d{5}),(\\d{5})\\]");
	std::smatch timers;

	// Check for well-formed response
	if (!std::regex_search(buffer, timers, timer_format)) {
		// Response not well-formed
		throw 1;
	}

	// Check for 4 timer matches
	if (timers.size() != 5) {
		// Search did not find four timers (and subject)
		throw 2;
	}

	this->wake_time = std::stoi(timers[1].str());
	this->light_duration = std::stoi(timers[2].str());
	this->spray_interval = std::stoi(timers[3].str());
	this->spray_duration = std::stoi(timers[4].str());

}

void Bank::_fetchRelays() {
	std::string buffer;

	this->connection->sendText("ST\r");
	this->connection->readText(buffer);

	std::regex status_format("\\b(\\d{22})\\b");
	std::smatch statuses;

	// Check for well-formed response
	if (!std::regex_search(buffer, statuses, status_format)) {
		// Response not well-formed
		throw 1;
	}

	// Iterate through the buffer, set statuses at
	// corresponding relays
	for (unsigned int i=0; i<buffer.length(); i++) {
		relays.at(i)->setStatus(buffer[i] - '0');
	}
}


// Bank::_setFileName - helper method to rename the Bank.
// @param nm - the string to set the Bank name to
// @pre - nm ends with '.json'
// @pre - nm contains only alpha or num or /-_.
// @pre - nm leads with alpha or num
// @throws 1 - doesn't end with .json
// @throws 2 - contains invalid chars
// @throws 3 - doesn't lead with alpha or num
// @post - Bank renamed
void Bank::_setFileName(std::string nm) {
	// REGEX: string ends with '.json'
	std::regex ends_with_json(".+.json$");
	if (!std::regex_match(nm, ends_with_json)) {
		// doesn't end with '.json'
		throw 1;
	}

	// REGEX: contains only alpha or num or /-_.
	std::regex not_valid_chars("[^a-zA-Z0-9\\._\\/]");
	if (std::regex_match(nm, not_valid_chars)) {
		// contains invalid chars
		throw 2;
	}

	// REGEX: leads with alpha or num
	std::regex leading_char("^[a-zA-Z0-9]");
	if (std::regex_match(nm, leading_char)) {
		// Doesn't lead with alpha or num
		throw 3;
	}

	// SUCCESS: Bank renamed
	this->file_name = nm;

}

// x hour to wake
void Bank::_setWakeTime(int x) {
	if (x < 0) {
		throw 1;
	}

	if (x > 23) {
		throw 1;
	}

	std::stringstream text_to_send;
	text_to_send << "TLI" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	//this->connection->sendText(text_to_send.str());
}

// x = hours
void Bank::_setLightDuration(int x) {
	if (x < 0) {
		throw 1;
	}

	if (x > 23) {
		throw 1;
	}

	std::stringstream text_to_send;
	text_to_send << "TLD" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	// this->connection->sendText(text_to_send.str());
}

// x = minutes
void Bank::_setSprayInterval(int x) {
	if (x < 0) {
		throw 1;
	}

	if (x > 3600) {
		throw 1;
	}

	std::stringstream text_to_send;
	text_to_send << "TSI" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	// this->connection->sendText(text_to_send.str());
}

// x = seconds
void Bank::_setSprayDuration(int x) {
	if (x < 0) {
		throw 1;
	}

	if (x > 30) {
		throw 1;
	}

	std::stringstream text_to_send;
	text_to_send << "TSD" << std::setw(3) << std::setfill('0')
				 << x << '\r';

	// this->connection->sendText(text_to_send.str());
}

void Bank::_setTimers(int wt, int ld, int si, int sd) {
	this->_setWakeTime(wt);
	this->_setLightDuration(ld);
	this->_setSprayInterval(si);
	this->_setSprayDuration(sd);
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
		if (user_response_2 == "y") {break;}

		std::cout << "What would you like the name to be? ";
	}

	try { this->_setFileName(user_response); }
	catch (int e) {
		std::cout << "ERROR #" << e << ": Unable to rename file." << std::endl;
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
		std::cin >> user_response_2;
		if (user_response_2 == "y") {break;}

		std::cout << "What should the wake time be? ";
	}

	this->_setWakeTime(user_response);

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
		std::cin >> user_response_2;
		if (user_response_2 == "y") {break;}

		std::cout << "What should the light duration be? ";
	}

	this->_setLightDuration(user_response);

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
		std::cin >> user_response_2;
		if (user_response_2 == "y") {break;}

		std::cout << "What should the spray interval be? ";
	}

	this->_setSprayInterval(user_response);

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
		std::cin >> user_response_2;
		if (user_response_2 == "y") {break;}

		std::cout << "What should the spray duration be? ";
	}

	this->_setSprayDuration(user_response);
}
