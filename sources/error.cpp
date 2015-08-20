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

	if (check_errors(0)) {

		std::cout << "FATAL" << std::endl;
	}

	return 0;
}
