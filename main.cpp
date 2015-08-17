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
  // Create a new Bank
  Bank* BankZero = nullptr;

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
            return 0;

        } else if (arguements[0] == "add") {
            Bank temp(arguements[1]);
            temp._setConnection(new RS232Connection(BAUDRATE, PIPORT));

            temp.add(arguements[2]);
            temp.report();

            temp._save();

            std::cout << "\n\nSUCCESS";
            return 0;

        } else if (arguements[0] == "delete") {
            std::cout << "lol no\n";
            return 0;

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
            return 0;

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
            return 0;

        } else if (arguements[0] == "toggle") {
            std::cout << "lol no\n";
            return 0;

        } else if (arguements[0] == "load") {
            BankZero = new Bank(arguements[1]);

        } else {
            std::cout << "\n\nERROR: Unknown operation\n";
            std::cout << "FAILURE\n\n";
              return 0;
        }
    }

    // PROGRAM SETUP
    std::cout << "... creating connection ...\n";
    RS232Connection* cx = new RS232Connection(BAUDRATE, PIPORT);
    cx->sendText("0");

    if (!BankZero) {
      std::cout << "... creating empty bank ...\n";
      BankZero = new Bank();
    }

    std::cout << "... setting bank connction ...\n";
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
	std::cout << "\t add [label]\t\t- add a relay, i.e.: ./gv add P3 \n";
	std::cout << "\t report\t\t\t- show the current status of relays \n";
	std::cout << "\t fetch\t\t\t- get the current status of the relays from the PLC \n";
	std::cout << "\t load [str]\t\t- Load a file, usually .json\n";
	std::cout << "\t save\t\t\t- Save a file.\n";
	std::cout << "\t on [label | all]\t\t- turn relay on\n";
	std::cout << "\t off [label | all]\t\t- turn relay off\n";
	std::cout << "\t help\t\t\t- show this screen again\n";
	std::cout << "\t quit\t\t\t- exit the program\n\n";

	std::cout << " You may also this program with command line arguements: \n\n";
	std::cout << "\t\tSYNTAX: ./gv [action] [filename] [arguements]\n\n";

	return;
}
