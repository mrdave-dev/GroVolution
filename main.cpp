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

#define PIPORT 16
#define BAUDRATE 38400

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
            // fetch -- update a file
            Bank temp(arguements[1]);
            temp._setConnection(new RS232Connection(BAUDRATE, PIPORT));

            temp.fetch();
            temp.report();

            std::cout << "\n\nSUCCESS";

        } else if (arguements[0] == "add") {
            Bank temp(arguements[1]);
            temp._setConnection(new RS232Connection(BAUDRATE, PIPORT));

            temp.add(arguements[2]);
            temp.report();

            temp._save();

            std::cout << "\n\nSUCCESS";

        } else if (arguements[0] == "delete") {
            std::cout << "lol no\n";

        } else if (arguements[0] == "on") {
            Bank temp(arguements[1]);
            temp._setConnection(new RS232Connection(BAUDRATE, PIPORT));

            if (arguements[2] == "all") {
                temp.allOn();
            } else {
                temp.on(arguements[2]);
            }

            temp.fetch();
            temp.report();

            temp._save();

            std::cout << "\n\nSUCCESS";

        } else if (arguements[0] == "off") {
            Bank temp(arguements[1]);
            temp._setConnection(new RS232Connection(BAUDRATE, PIPORT));

            if (arguements[2] == "all") {
                temp.allOff();
            } else {
                temp.off(arguements[2]);
            }

            temp.fetch();
            temp.report();

            temp._save();

            std::cout << "\n\nSUCCESS";

        } else if (arguements[0] == "toggle") {
            std::cout << "lol no\n";

        } else {
            std::cout << "\n\nERROR: Unknown operation\n";
            std::cout << "FAILURE\n\n";
        }

        // End before going in to the main program if a command
        // line arguement is given.
        return 0;
    }

    // PROGRAM SETUP
    std::cout << "... creating connection ...\n";
    RS232Connection* cx = new RS232Connection(BAUDRATE, PIPORT);

    std::cout << "... creating empty bank ...\n";
    Bank* BankZero = new Bank();
    BankZero->_setConnection(cx);

    std::cout << "... almost done ...\n";
    std::string userResponse;

    std::cout << "... ready? FIGHT! ...\n\n";

    printHelp();

    while (userResponse != "exit") {
        std::cout << "Enter a command or 'exit': ";
        std::getline(std::cin, userResponse);

        // Extract user input
        std::vector<std::string> commands;
        std::istringstream raw_userResponse(userResponse);
        std::string temp_word;
        while (raw_userResponse >> temp_word) {
          commands.push_back(temp_word);
        }

      if (commands[0] == "add") {
        // Add to the current bank
        BankZero->add(commands[1]);

      } else if (commands[0] == "remove") {
        std::cout << "lol no.\n";

      } else if (commands[0] == "on") {
        if (commands[1] == "all") {
            BankZero->allOn();
        } else {
            BankZero->on(commands[1]);
        }

        BankZero->fetch();
        BankZero->report();

        BankZero->_save();

      } else if (commands[0] == "off") {
        if (commands[1] == "all") {
            BankZero->allOff();
        } else {
            BankZero->off(commands[1]);
        }

        BankZero->fetch();
        BankZero->report();

        BankZero->_save();

      } else if (commands[0] == "load") {
        BankZero->_load(commands[1]);
        BankZero->report();

      } else if (commands[0] == "save") {
        BankZero->_save();
        std::cout << "Bank saved.\n\n";

      } else if (commands[0] == "report") {
        BankZero->report();

      } else if (commands[0] == "fetch") {
        BankZero->fetch();
        BankZero->report();

      } else if (commands[0] == "help") {
        printHelp();

      } else if (commands[0] == "exit") {
        return 0;

      }
    } // end while(userResponse != "exit")
    return 0;
} // end main()


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
	std::cout << "\t\tSYNTAX: ./gv [on|off|fetch] [filename] [relay label|all]\n\n";

	return;
}
