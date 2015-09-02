#ifndef GV_ERROR_H
#define GV_ERROR_H

#include <iostream>
#include <string>
#include <vector>

// class gv_error - a struct to hold error reasons and
// 		a bool for whether the function or method should
// 		end.
// @member std::string output - text to provide user
// @member bool terminate - true if error is fatal
// 		false if error is non-fatal
class gv_error {
private:
	int e_number;
	std::string output;
	bool terminate;



public:
	gv_error(int, std::string, bool);
	int getE();
	void stateOutput();
	bool getTerminate();

};

// std::vector<gv_error*> gv_errors;

bool check_errors(int);




#endif
