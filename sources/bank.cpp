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

// Bank::_rename - helper method to rename the Bank.
// @param nm - the string to set the Bank name to
// @pre - nm ends with '.json'
// @pre - nm contains only alpha or num or /-_.
// @pre - nm leads with alpha or num
// @throws 1 - doesn't end with .json
// @throws 2 - contains invalid chars
// @throws 3 - doesn't lead with alpha or num
// @post - Bank renamed
void Bank::_rename(std::string nm) {
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
