#include "../headers/error.h"

std::vector<gv_error*> gv_errors;

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
	for (unsigned int i = 0; i< gv_errors.size(); i++) {
		if (gv_errors.at(i)->getE() == e) {
			gv_errors.at(i)->stateOutput();
			return gv_errors.at(i)->getTerminate();
		}
	}

	std::cout << "\n\nUNKNOWN ERROR\n\n";
	return true;
}

void load_errors(std::string filename, std::vector<gv_error*> container)
{
	int errorCode = 0;	//temp int to hold error code
	std::string errorType;	//temp string to hold error type
	bool terminate = true;	//temp bool to hold terminate value
	std::string buffer;	//buffer to read in text file

	std::ifstream errorfile(filename.c_str());

	if (errorfile.is_open())
	{
		while (!errorfile.eof())
		{
			getline(errorfile, buffer, ',');
			errorCode = stoi(buffer);

			getline(errorfile, buffer, ',');
			errorType = buffer;

			getline(errorfile, buffer, '\n');
			if (buffer == "true") terminate = true;
			else terminate = false;

			//push error into vector
			gv_errors.push_back(new gv_error(errorCode, errorType, terminate));
		}
		errorfile.close();
	}

	else std::cout << "File did not open." << std::endl;
}
/*
int main()
{
	std::vector<gv_error*> gv_errors;

	load_errors("errors.txt", gv_errors);

	check_errors(0);

    // this won't compile but its here for example
    // checklist
    //  make sure non-fatal error repeats on higher level function
    //  make sure fatal error does not repeat on higher level function
    //  move load_errors to main.cpp
    //  try it out in main program... but you don't have to

//    Bank davesBank* = new Bank("blah", 1, cool);

//    davesBank->userRename();

//    davesBank->fetchTimers();

	return 0;
}
*/
