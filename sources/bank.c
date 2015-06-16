#include "../headers/bank.h"

struct Bank * bankInit(struct Bank *b) {
	// Allocate some memory
	struct Bank *t = malloc(sizeof(struct Bank));

	// initialize ints to 0
	t->count = 0;
	t->wakeTime = 0;
	t->lightDuration = 0;
	t->sprayInterval = 0;
	t->sprayDuration = 0;

	// Initialize the relay pointer array
	t->relayCapacity = 30;

	return t;
}

void bankAddRelay(struct Bank *b, char ab, int r) {
	b->relays[b->count] = initRelay(ab, r);
	b->count++;
}

void bankTurnAllOn(struct Bank *b) {
	for (int i = 0; i < b->count; i++) {
		onRelay(b->relays[i]);
	}
}

void bankTurnAllOff(struct Bank *b) {
	for (int i = 0; i < b->count; i++) {
		offRelay(b->relays[i]);
	}
}

void bankTurnInverse(struct Bank *b) {
	for (int i = 0; i < b->count; i++) {
		switchRelay(b->relays[i]);
	}
}

void bankReport(struct Bank *b) {
	printf("\n\nBANK REPORT \n");
	printf("COUNT: %i\t\tCAPACITY: %i\n", b->count, b->relayCapacity);
	printf("WAKE TIME %i\t\tLIGHT DURATION: %i\n", b->wakeTime, b->lightDuration);
	printf("SPRAY INT.: %i\t\tSPRAY DURATION: %i\n", b->sprayInterval, b->sprayDuration);
	printf("RELAYS:\n");
	for (int i = 0; i < b->count; i++) {
		printf("RELAY #%i\t| %c%i\t| STATUS: %i\n", i, b->relays[i]->label, b->relays[i]->number, b->relays[i]->status);
	}

}

void bankReportByLabel(struct Bank *b, char* c) {
	printf("\n\nBANK REPORT \n");
	printf("COUNT: %i\t\tCAPACITY: %i\n", b->count, b->relayCapacity);
	printf("WAKE TIME %i\t\tLIGHT DURATION: %i\n", b->wakeTime, b->lightDuration);
	printf("SPRAY INT.: %i\t\tSPRAY DURATION: %i\n", b->sprayInterval, b->sprayDuration);
	printf("RELAYS:\n");

	char targetLabel = c[0];

	for (int i = 0; i < b->count; i++) {
		if (targetLabel == b->relays[i]->label) {
			printf("RELAY #%i\t| %c%i\t| STATUS: %i\n", i, b->relays[i]->label, b->relays[i]->number, b->relays[i]->status);
		}
	}
}


void bankReportTimers(struct Bank *b) {
	printf("\n\nBANK REPORT \n");
	printf("COUNT: %i\t\tCAPACITY: %i\n", b->count, b->relayCapacity);
	printf("WAKE TIME %i\t\tLIGHT DURATION: %i\n", b->wakeTime, b->lightDuration);
	printf("SPRAY INT.: %i\t\tSPRAY DURATION: %i\n", b->sprayInterval, b->sprayDuration);
}

void bankFetchStatus(struct Bank *b) {
	// Get the status from PLC, store in a string
	printf("Fetching status from PLC...\n");
	unsigned char statusHolder[b->relayCapacity + 1];

	sendText("ST\r");
	readText(statusHolder);

	// Print error if number of relays don't match
	if (sizeof(statusHolder) != b->count) {
		printf("STATUS FETCH ERROR: Number of relays do not match\n");
		return;
	}

	// Iterate through each character of string,
	// compare to status of relay
		// print something if there's a discrepncy
		// change relay status to reflect what PLC says
	for (int i = 0; i < b->relayCapacity; i++) {
		if (b->relays[i]->status != statusHolder[i]) {
			printf("STATUS FETCH ERROR: Relay #%i does not match PLC. Adjusting relay status.\n", i);
			b->relays[i]->status = statusHolder[i] - '0';
		}
	}
}

void bankFetchTimers(struct Bank *b) {
	printf("Fetching timers from PLC...\n");
	unsigned char timerHolder[24];

	sendText("TM\r");
	readText(timerHolder);

	int timerSelector = 0;
	int timerPlace = 0;
	int timerTemp = 0;
	while (timerHolder[timerPlace] != 0) {
		for (int i = 4; i >= 0; i--) {
			timerTemp += timerHolder[timerPlace] * (pow(10, i));
			timerPlace++;
		}

		switch (timerSelector) {
			case 0:
				b->wakeTime = timerTemp;
				break;
			case 1:
				b->lightDuration = timerTemp;
				break;
			case 2:
				b->sprayInterval = timerTemp;
				break;
			case 3:
				b->sprayDuration = timerTemp;
				break;
		}

		timerPlace += 5;
		timerSelector++;
	}






}

/*



void bankFetchTimers(struct Bank *b);
int bankSetTimer(int t, int v);
int bankSetTimers(int a, int b, int c, int d);

*/
