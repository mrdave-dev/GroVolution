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
	std::ifstream fs(fn, std::ofstream::out);

	if (!fs.is_open()) {
		throw 1;
	}

	// REFERENCE: http://insanecoding.blogspot.ca/2011/11/how-to-read-in-file-in-c.html
	std::string contents;		// create a string
	fs.seekg(0, std::ios::end);	// find the end of the file
	contents.resize(fs.tellg());// resize string to size of file
	fs.seekg(0, std::ios::beg);	// go back to beg. of file
	fs.read(&contents[0], contents.size()); // read from beg. to end to str
	fs.close();					// close

	std::cout << contents;

	rapidjson::Document d;
	d.Parse(contents.c_str());
	std::cout << d["untitled.json"]["count"].GetString() << std::endl;





}


