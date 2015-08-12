#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "RS-232/rs232.h"
#include "headers/comms.h"
#include "headers/relay.h"
#include "headers/bankcpp.h"

// FUNCTION DECLARATIONS
void printHelp();


int main(int argc, char** argv) {
    // Check for command line arguements
    if (argc > 1) {
        std::vector<std::string> arguements;
        for (int i=1; i<argc; i++) {
            // Copy the arguements in to a vector of strings
            //std::string t = argv[i];
            arguements.push_back(argv[i]);
        }

        // This is just to out put for debugging... This will be gone
        // Before merge to master
        for (unsigned int i=0; i<arguements.size(); i++) {
            std::cout << "Arg " << i << ": " << arguements.at(i) << std::endl;
        }

        // Basic syntax of command line arguements:
        // ./gv [action] [file] [arguements]
        if (arguements[0] == "fetch") {
            try {
                Bank temp(arguements[1]);
                temp._setConnection(new RS232Connection(38400, 14));
                temp.fetch();
                temp.report();

                // Need to create fail safe for RS232 connection on bank
                // init. I gotta default the connection to a nullptr
                // so we don't get segfaults if no connection is set
            } catch (int e) {

            }
        } else if (arguements[0] == "add") {

        } else if (arguements[0] == "on") {

        } else if (arguements[0] == "off") {

        } else if (arguements[0] == "toggle") {

        } else {
            std::cout << "\n\nERROR: Unknown operation\n";
            std::cout << "FAILURE\n\n";
        }


        return 0;
    }




    return 0;
}


// FUNCTION DEFINITIONS
void printHelp() {
	std::cout << " GROVOLUTION CLI \n";
	std::cout << " OPTIONS: \n";
	std::cout << "\t add [char][#]\t\t- add a relay, i.e.: ./gv add P3 \n";
	std::cout << "\t report\t\t\t- show the current status of relays \n";
	std::cout << "\t fetch\t\t\t- get the current status of the relays from the PLC \n";
	std::cout << "\t switch [char][#]\t- turn a relay to its opposite status i.e.: ./gv switch P3\n";
	std::cout << "\t rename [str]\t\t- Rename a bank. NOTE: name is used to save file.\n";
	std::cout << "\t load [str]\t\t- Load a file, usually .json\n";
	std::cout << "\t save\t\t\t- Save a file. NOTE: the bank's name is used as the filename\n";
	std::cout << "\t on [char][#]\t\t- turn relay on\n";
	std::cout << "\t off [char][#]\t\t- turn relay off\n";
	std::cout << "\t all on\t\t\t- turn all relays on\n";
	std::cout << "\t all off\t\t- turn all relays off\n";
	std::cout << "\t invert\t\t\t- turns on switches on and off switches off\n";
	std::cout << "\t help\t\t\t- show this screen again\n";
	std::cout << "\t quit\t\t\t- exit the program\n\n";

	std::cout << " You may also this program with command line arguements: \n\n";
	std::cout << "\t\tSYNTAX: ./gv [on|off|all on|all off|fetch] (char)(#)\n\n";

	return;
}
