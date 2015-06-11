#include <stdlib.h>		// strcpy
#include <stdio.h>		// printf
#include <string.h>
#include <unistd.h> 	// usleep

// Outside libraries
#include "../RS-232/rs232.h"

// Custom definitions
#include "../headers/relay.h"
#include "../headers/comms.h"

int main(int argc, char** argv) {

	printf("*** CREATING RELAYS ***\n");

	struct relay* GVR_RELAYS[] = {initRelay('P', 1), initRelay('P', 2), initRelay('P', 3),
		initRelay('V', 1), initRelay('V', 2), initRelay('V', 3),
		initRelay('L', 1), initRelay('L', 2), initRelay('L', 3), initRelay('L', 4), initRelay('L', 5),
		initRelay('L', 6), initRelay('L', 7), initRelay('L', 8), initRelay('L', 9), initRelay('L', 10),
		initRelay('L', 11), initRelay('L', 12), initRelay('L', 13), initRelay('L', 14), initRelay('L', 15),
		initRelay('L', 16), initRelay('L', 17)};

	printf("*** INITIAL STATUS ***\n\n");
	sendText("ST\r");
	unsigned char davesString[100];
	readText(davesString);
	printf("\n\n");

	printf("*** SWITCHING ALL RELAYS ON ***");
	for (int i = 0; i<23; i++) {
		onRelay(GVR_RELAYS[i]);
	}


	printf("*** SHOULD BE ALL 1's ***\n\n");
	sendText("ST\r");
	printf("\n\n");

	printf("*** SWITCHING ALL RELAYS OFF ***");
	for (int i = 0; i<23; i++) {
		offRelay(GVR_RELAYS[i]);
	}

	printf("*** SHOULD BE ALL 0's ***\n\n");
	sendText("ST\r");
	printf("\n\n");

		#ifdef _WIN32
			Sleep(100);
		#else
			usleep(100000);  /* sleep for 100 milliSeconds */
		#endif

	return 0;


}
