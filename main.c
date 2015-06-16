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

/* TODO:
 - Make read text write to the buffer provided
 - Begin creating objects: switches, bank, board
 - Create code to take commands from CL arguements
 - Create interface to use without command lind arguements
 - Create Code to figure out which port to use
 - Refactor code in to seperate headers and object files
 - Edit makefile to work right...
*/


int main(int argc, char** argv)  {

	// Intro text
	printf("GROVOLUTION CLI \n");
	printf("What would you like to do? ");

	printf("\n");

	sendText("R0L001\r");

		#ifdef _WIN32
			Sleep(1000);
		#else
			usleep(1000000);  /* sleep for 100 milliSeconds */
		#endif

	sendText("ST\r");
	unsigned char davesString[100];
	readText(davesString);
	printf("STRING: %s", davesString);

	return 0;

	/*

	struct relay* davesRelay = initRelay(davesRelay, 'P', 33);
	switchRelay(davesRelay);


	unsigned char davesString[100];
	readText(davesString);


	printf("davesString: %s \n", davesString);
    return 0;
    */
}
