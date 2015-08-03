/* GROVOLUTION - relay-test-1.cpp
 * A testing program for the Relay class.
 *
 * Author: Dave Martinez
 * Created: 7/21/15
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <regex>

#include "../RS-232/rs232.h"
#include "../headers/comms.h"
#include "../headers/relay.h"
#include "../headers/bankcpp.h"

int main(int argc, char** argv) {
	 Bank *aBank = new Bank("untitled.json");
	 try {
		 aBank->_rename("test-1.json");
	 } catch (int e) {
		 std::cout << "RENAME ERROR: " << e << std::endl;
	 }

	 aBank->_save();



	 std::cout << "End \n";

return 0;
}
