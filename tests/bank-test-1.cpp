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
		 aBank->_setFileName("yeah/cool/awes-om.wow.jjson");
	 } catch (int e) {
		 std::cout << "RENAME ERROR: " << e << std::endl;
	 }

	 aBank->_setConnection(new RS232Connection(38400, 16));

	 aBank->userSetName();
	 aBank->userSetWakeTime();
	 aBank->userSetLightDuration();
	 aBank->userSetSprayInterval();
	 aBank->userSetSprayDuration();

	 std::cout << "getName(): " << aBank->getName() << std::endl;
	 std::cout << "getCount(): " << aBank->getCount() << std::endl;
	 std::cout << "getWakeTime(): " << aBank->getWakeTime() << std::endl;
	 std::cout << "getLightDuration(): " << aBank->getLightDuration() << std::endl;
	 std::cout << "getSprayInterval(): " << aBank->getSprayInterval() << std::endl;
	 std::cout << "getSprayDuration(): " << aBank->getSprayDuration() << std::endl;

	 std::cout << "_findRelayByID(std::string): " << aBank->_findRelayByID("P1")->getStatus() << std::endl;
	 std::cout << "_findRelayByID(char, int): " << aBank->_findRelayByID('P', 1)->getStatus() << std::endl;






	 aBank->report();

	 // aBank->_save();



	 std::cout << "End \n";

return 0;
}
