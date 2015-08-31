#include "../headers/error.h"

gv_error::gv_error(int e, std::string o, bool t) {
	this->e_number = e;
	this->output = o;
	this->terminate = t;
}

int gv_error::getE() {
	return this->e_number;
}

bool gv_error::getTerminate() {
	return this->terminate;
}

void gv_error::stateOutput() {
	std::cout << "\n\nERROR ";
	std::cout << this->e_number;
	std::cout << ": ";
	std::cout << this->output;
	std::cout << "\n\n";
}

bool check_errors(int e) {
	for (unsigned int i=0; i<gv_errors.size(); i++) {
		if (gv_errors.at(i)->getE() == e) {
			gv_errors.at(i)->stateOutput();
			return gv_errors.at(i)->getTerminate();
		}
	}

	std::cout << "\n\nUNKNOWN ERROR\n\n";
	return true;
}



int main() {

gv_errors.push_back(new gv_error(0, "RS232 Connection settings not set.", true));
gv_errors.push_back(new gv_error(1, "Unable to make RS232 connection.", true));
gv_errors.push_back(new gv_error(100, "Relay label not set.", true));
gv_errors.push_back(new gv_error(101, "Relay number not set.", true));
gv_errors.push_back(new gv_error(102, "Relay status not set.", true));
gv_errors.push_back(new gv_error(200, "File not open.", false));
gv_errors.push_back(new gv_error(201, "Timer response not properly formed.", true));
gv_errors.push_back(new gv_error(202, "Search didn't find all timers.", true));
gv_errors.push_back(new gv_error(203, "Relay response not proerly formed.", true));
gv_errors.push_back(new gv_error(204, "File name not set: Doesn't end with .json.", false));
gv_errors.push_back(new gv_error(205, "File name not set: Contains invalid characters.", false));
gv_errors.push_back(new gv_error(206, "File name not set: Must lead with alpha or num.", false));
gv_errors.push_back(new gv_error(207, "Invalid wake time: Value must be 0-23.", false));
gv_errors.push_back(new gv_error(208, "Invalid light duration: Value must be 0-23.", false));
gv_errors.push_back(new gv_error(209, "Invalid spray interval: Value must be 0-3600.", false));
gv_errors.push_back(new gv_error(210, "Invalid spray duration: Value must be 0-30.", false));
gv_errors.push_back(new gv_error(211, "Relay ID already exists.", false));
gv_errors.push_back(new gv_error(212, "Invalid number value: Value must be 0-100.", false));
gv_errors.push_back(new gv_error(213, "Relay ID not found.", true));
gv_errors.push_back(new gv_error(214, "User quit.", true));


	if (check_errors(0)) {

		std::cout << "FATAL" << std::endl;
	}

	return 0;
}
