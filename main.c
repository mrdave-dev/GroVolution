#include <stdlib.h>		// strcpy
#include <stdio.h>		// printf
#include <string.h>
#include <unistd.h> 	// usleep
#include <math.h>

// Outside libraries
#include "RS-232/rs232.h"

// Custom definitions
#include "headers/relay.h"
#include "headers/comms.h"
#include "headers/bank.h"
#include "headers/fileops.h"

/* TODO:
 - Create Code to figure out which port to use

   ISSUES:
 - Fetch should be able to handle some issues with getting either corrupted data
   or data that isn't complete or data that's not well formed (no null char).
 - In one instance, errors were occuring with bad syncage between status fetches.
   Watch out and try to replicate.
*/

void printHelp();

int main(int argc, char** argv)  {
	printf("... initializing bank ...\n");
	struct Bank* bankZero = bankInit();
/*
	printf("... adding relays ...\n");
	bankAddRelay(bankZero, 'P', 1);
	bankAddRelay(bankZero, 'P', 2);
	bankAddRelay(bankZero, 'V', 1);
	bankAddRelay(bankZero, 'V', 2);
	bankAddRelay(bankZero, 'V', 3);
	bankAddRelay(bankZero, 'L', 1);
	bankAddRelay(bankZero, 'L', 2);
	bankAddRelay(bankZero, 'L', 3);
	bankAddRelay(bankZero, 'L', 4);
	bankAddRelay(bankZero, 'L', 5);
	bankAddRelay(bankZero, 'L', 6);
	bankAddRelay(bankZero, 'L', 7);
	bankAddRelay(bankZero, 'L', 8);
	bankAddRelay(bankZero, 'L', 9);
	bankAddRelay(bankZero, 'L', 10);
	bankAddRelay(bankZero, 'L', 11);
	bankAddRelay(bankZero, 'L', 12);
	bankAddRelay(bankZero, 'L', 13);
	bankAddRelay(bankZero, 'L', 14);
	bankAddRelay(bankZero, 'L', 15);
	bankAddRelay(bankZero, 'L', 16);
	bankAddRelay(bankZero, 'L', 17);

	printf("... fetching relay status ...\n");
	bankFetchStatus(bankZero);

	printf("... fetching timer status ...\n");
	bankFetchTimers(bankZero);
*/
	/* COMMAND LINE ARGUEMENTS INTERFACE */
	if (argc > 1) {
		if (strcmp(argv[1], "all") == 0) {
			if (strcmp(argv[2], "on") == 0) {
				bankTurnAllOn(bankZero);
				return 0;
			} else if (strcmp(argv[2], "off") == 0) {
				bankTurnAllOff(bankZero);
				return 0;
			}
		} else if (strcmp(argv[1], "fetch") == 0) {
			bankFetchStatus(bankZero);
			return 0;
		} else if (strcmp(argv[1], "on") == 0) {
			char targetChar = argv[2][0];
			int  targetInt = argv[2][1] - '0';
			bankTurnRelayOn(bankZero, targetChar, targetInt);
			return 0;

		} else if (strcmp(argv[1], "off") == 0) {
			char targetChar = argv[2][0];
			int  targetInt = argv[2][1] - '0';
			bankTurnRelayOff(bankZero, targetChar, targetInt);
			return 0;
		}
	}

	printf("... almost done ...\n");
	char userResponse[80];

	printf("Setup complete!\n\n");

	printHelp();

	while (strcmp(userResponse, "quit") != 0) {

		printf("What would you like to do? ");
		gets(userResponse);

		// Break down user response
		char firstWord[20];
		char firstChar;
		int firstNum;

		char* firstSpace = strstr(userResponse, " ");
		if (firstSpace == NULL) {
			// entry is only one word long
			strcpy(firstWord, userResponse);
			// printf("DEBUG: firstSpace == NULL\n");
			// printf("DEBUG: firstWord = %s\n", firstWord);
		} else {
			// Assign first char and first num
			// printf("DEBUG: firstSpace = %p\n", (void *)firstSpace);
			// printf("DEBUG: &userresponse = %p\n", (void *)&userResponse);
			// how many bytes does it take to get to space?
			int bytesToSpace = (int) firstSpace - (int) &userResponse;
			// printf("DEBUG: bytesToSpace = %i\n", bytesToSpace);

			firstChar = userResponse[bytesToSpace + 1];
			firstNum = (int) userResponse[bytesToSpace + 2] - '0';

			//printf("DEBUG: firstChar = %c\n", firstChar);
			//printf("DEBUG: firstNum = %i\n", firstNum);

			// TODO: add additional verifications: range char andnum
		}

		// TODO: Ditch the strstr function and use the strtok to break apart
		// the user's entry. this will help if/else tree to be more accurate
		if (strstr(userResponse, "add") != NULL) {
			//printf("Add\n");
			bankAddRelay(bankZero, firstChar, firstNum);

		} else if (strcmp(userResponse, "report") == 0) {
			//printf("Report\n");
			bankReport(bankZero);

		} else if (strcmp(userResponse, "fetch") == 0) {
			//printf("Fetch\n");
			bankFetchStatus(bankZero);
			bankFetchTimers(bankZero);

		} else if (strstr(userResponse, "switch") != NULL) {
			//printf("Switch\n");
			bankRelaySwitch(bankZero, firstChar, firstNum);

		} else if (strstr(userResponse, "save") != NULL) {
			bankSave(bankZero);

		} else if (strstr(userResponse, "load") != NULL) {
			printf("load\n");

			// should i destroy this memory after use?
			char *word = strtok(userResponse, " ");
			word = strtok(NULL, " ");
			printf("%s \n", word);

			bankZero = bankLoad(word);
			if (bankZero != NULL) {
				bankReport(bankZero);
			}

		} else if (strcmp(userResponse, "all on") == 0) {
			//printf("All on\n");
			bankTurnAllOn(bankZero);

		} else if (strcmp(userResponse, "all off") == 0) {
			//printf("All off\n");
			bankTurnAllOff(bankZero);

		} else if (strstr(userResponse, "on") != NULL) {
			//printf("On\n");
			bankTurnRelayOn(bankZero, firstChar, firstNum);

		} else if (strstr(userResponse, "off") != NULL) {
			//printf("Off\n");
			bankTurnRelayOff(bankZero, firstChar, firstNum);

		} else if (strcmp(userResponse, "invert") == 0) {
			bankTurnInverse(bankZero);

		} else if (strcmp(userResponse, "help") == 0) {
			//printf("Help\n");
			printHelp();

		} else if (strcmp(userResponse, "quit") == 0) {
			// do nothing
		} else {
			printf("Sorry, that's not an option. :( \n\n");
		}
	}

	return 0;
}


void printHelp() {
	printf(" GROVOLUTION CLI \n");
	printf(" OPTIONS: \n");
	printf("\t add [char][#]\t\t- add a relay, i.e.: ./gv add P3 \n");
	printf("\t report\t\t\t- show the current status of relays \n");
	printf("\t fetch\t\t\t- get the current status of the relays from the PLC \n");
	printf("\t switch [char][#]\t- turn a relay to its opposite status i.e.: ./gv switch P3\n");
	printf("\t on [char][#]\t\t- turn relay on\n");
	printf("\t off [char][#]\t\t- turn relay off\n");
	printf("\t all on\t\t\t- turn all relays on\n");
	printf("\t all off\t\t- turn all relays off\n");
	printf("\t invert\t\t\t- turns on switches on and off switches off\n");
	printf("\t help\t\t\t- show this screen again\n");
	printf("\t quit\t\t\t- exit the program\n\n");

	printf(" You may also this program with command line arguements: \n\n");
	printf("\t\tSYNTAX: ./gv [on|off|all on|all off|fetch] (char)(#)\n\n");

	return;
}
