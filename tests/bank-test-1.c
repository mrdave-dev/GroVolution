#include <stdlib.h>		// strcpy
#include <stdio.h>		// printf
#include <string.h>
#include <unistd.h> 	// usleep

// Outside libraries
#include "../RS-232/rs232.h"

// Custom definitions
#include "../headers/relay.h"
#include "../headers/comms.h"
#include "../headers/bank.h"

void enterToContinue() {
	printf("\n\nPress enter to continue...");
	getchar();
}

int main(int argc, char** argv) {
	printf("*** BANK TEST ***\n");
	printf("*** INITIALIZING BANK ***\n");

	struct Bank* davesBank = bankInit();
	printf("*** BANK ADDRESS: %p ***\n", (void *) davesBank);
	bankReport(davesBank);

	enterToContinue();

	printf("*** ADDING RELAYS ***\n");
	bankAddRelay(davesBank, 'P', 1);
	bankAddRelay(davesBank, 'P', 2);
	bankAddRelay(davesBank, 'V', 1);
	bankAddRelay(davesBank, 'V', 2);
	bankAddRelay(davesBank, 'V', 3);
	bankAddRelay(davesBank, 'L', 1);
	bankAddRelay(davesBank, 'L', 2);
	bankAddRelay(davesBank, 'L', 3);
	bankAddRelay(davesBank, 'L', 4);
	bankAddRelay(davesBank, 'L', 5);
	bankAddRelay(davesBank, 'L', 6);
	bankAddRelay(davesBank, 'L', 7);
	bankAddRelay(davesBank, 'L', 8);
	bankAddRelay(davesBank, 'L', 9);
	bankAddRelay(davesBank, 'L', 10);
	bankAddRelay(davesBank, 'L', 11);
	bankAddRelay(davesBank, 'L', 12);
	bankAddRelay(davesBank, 'L', 13);
	bankAddRelay(davesBank, 'L', 14);
	bankAddRelay(davesBank, 'L', 15);
	bankAddRelay(davesBank, 'L', 16);
	bankAddRelay(davesBank, 'L', 17);

	printf("*** DONE ADDING RELAYS ***\n");
	printf("*** TESTING FETCH STATUS FUNCTION *** \n");
	enterToContinue();

	bankReport(davesBank);
	bankFetchStatus(davesBank);
	bankReport(davesBank);
	bankFetchStatus(davesBank);
	bankReport(davesBank);


	printf("*** DONE TESTING FETCH STATUS ***\n");
	printf("*** TESTING TIMER FETCH FUNCTION *** \n");
	enterToContinue();

	bankFetchTimers(davesBank);
	bankReport(davesBank);

	printf("*** DONE TESTING FETCH ***\n");
	printf("*** TESTING ALL OFF ***\n");
	enterToContinue();

	bankTurnAllOff(davesBank);
	bankReport(davesBank);

	printf("*** DONE TESTING ALL OFF ***");
	printf("*** TESTING ALL ON ***");
	enterToContinue();


	bankTurnAllOn(davesBank);
	bankReport(davesBank);

	printf("*** DONE TESTING ALL ON ***");
	printf("*** TURNING ARBITRARY SWITCHES OFF FOR INVERSE TEST *** \n");
	enterToContinue();

	bankTurnRelayOff(davesBank, 'P', 1);
	bankTurnRelayOff(davesBank, 'V', 1);
	bankTurnRelayOff(davesBank, 'V', 3);
	bankTurnRelayOff(davesBank, 'L', 1);
	bankTurnRelayOff(davesBank, 'L', 3);
	bankTurnRelayOff(davesBank, 'L', 5);
	bankTurnRelayOff(davesBank, 'L', 7);
	bankTurnRelayOff(davesBank, 'L', 9);
	bankTurnRelayOff(davesBank, 'L', 11);
	bankTurnRelayOff(davesBank, 'L', 13);
	bankTurnRelayOff(davesBank, 'L', 15);
	bankTurnRelayOff(davesBank, 'L', 17);

	printf("*** ARBITRARY SWITCHES DONE ***\n");
	printf("*** TURNING INVERSE ***\n");
	enterToContinue();

	bankTurnInverse(davesBank);

	printf("*** DONE TURN INVERSE ***");
	printf("*** TESTING  TURN INVERSE ***");
	enterToContinue();

	bankTurnInverse(davesBank);
	bankReport(davesBank);

	printf("*** DONE TURN INVERSE ***");
	printf("*** TURNING ALL OFF ***\n");
	enterToContinue();

	bankTurnAllOff(davesBank);

	return 0;
}
