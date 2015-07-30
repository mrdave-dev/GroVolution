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
	std::ifstream fs(fn, std::ifstream::binary);

	if (!fs.is_open()) {
		throw 1;
	}

	std::string _fn_p = "{\"(.*)\"\:\\s*{\\s*\\n";

	try {
		std::regex fn_pattern (_fn_p);

	std::smatch match;
	std::string test1 = "{\"web/webready.json\": {";
	std::regex_search(test1, match, fn_pattern);
	std::cout << "MATCH (if any): " << match.size() << std::endl;


	std::string buffer;
	while (fs >> buffer) {
		if (std::regex_search(buffer, match, fn_pattern)) {
			std::cout << "MATCH MADE." << std::endl;
			std::cout << match.size() << std::endl;
		}
	}
	} catch (std::regex_error e ) {
		if (std::regex_constants::error_escape == e.code()) {
			std::cout << "Error: bad escape\n";
		}

		std::cout << "ERROR: " << e.code() << std::endl;
	}

}


