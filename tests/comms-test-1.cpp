/* GROVOLUTION - comms-test-1.cpp
 * A testing program for the RS232Connection class.
 *
 * Author: Dave Martinez
 * Created: 7/17/15
 */

 #include <iostream>
 #include <string>

 #include "../RS-232/rs232.h"
 #include "../headers/commscpp.h"

 int main(int argc, char** argv) {
 	std::cout << "COMMS TEST 1\n";
 	std::cout << "\n";
 	
 	std::cout << "01 - Does the class initialize? \n";
 	
 	std::cout << "Creating RS232Connection object, no args...\n";
 	RS232Connection *firstConnect = new RS232Connection();

 	if (firstConnect) {std::cout << "\nTEST PASSED: RS232 Connection Created\n\n";}
 	else {std::cout << "\nTEST FAILED: RS232Connection did not initialize.\n\n";} 	
 	

 	std::cout << "Creating RS232Connection object, with args...\n";
 	RS232Connection *secondConnect = new RS232Connection(38000, 14);

	if (secondConnect) {std::cout << "\nTEST PASSED: RS232Connection Created\n\n";}
 	else {std::cout << "\nTEST FAILED: RS232Connection did not initialize.\n\n";} 

 	std::cout << "firstConnect Addr.: " << firstConnect << "\n";
 	std::cout << "secondConnect Addr.: " << secondConnect << "\n";

 	std::cout << "02 - Get and set methods\n\n";

 	int testBaudRate = 38000;
 	int testPiPort = 14;

 	std::cout << "Testing unset rates...\n";
 	if (firstConnect->getBaudRate() == -1) {std::cout << "TEST PASSED: firstConnect baudrate == -1\n\n";}
 	else {std::cout << "TEST FAILED: firstConnect baudrate does not equal -1\n\n";};

	std::cout << "Testing unset piport...\n";
 	if (firstConnect->getPiPort() == -1) {std::cout << "TEST PASSED: firstConnect piport == -1\n\n";}
 	else {std::cout << "TEST FAILED: firstConnect piport does not equal -1\n\n";};








 	return 0;
 }
