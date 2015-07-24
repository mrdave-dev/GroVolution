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

	// prompt to add relays
	// print help


}

Bank::Bank(std::string fn) {
	std::cout << "Test: bank with fn\n";
}
