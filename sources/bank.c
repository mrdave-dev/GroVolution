#include "../headers/bank.h"

struct Bank * bankInit() {
	// Allocate some memory
	struct Bank* t = malloc(sizeof(struct Bank));

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
	if (b->count >= b->relayCapacity) {
		printf("ERROR: Bank at capacity.\n");
		return;
	}

	b->relays[b->count] = initRelay(ab, r);
	b->count++;
}

void bankTurnRelayOn(struct Bank *b, char ab, int r) {
	for (int i = 0; i < b->count; i++) {
		if (b->relays[i]->label == ab) {
			if (b->relays[i]->number == r) {
				onRelay((b->relays[i]));
			}
		}
	}
}

void bankTurnRelayOff(struct Bank *b, char ab, int r) {
	for (int i = 0; i < b->count; i++) {
		if (b->relays[i]->label == ab) {
			if (b->relays[i]->number == r) {
				offRelay((b->relays[i]));
			}
		}
	}
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
	printf("\n\n");
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
	printf("\n\n");
}


void bankReportTimers(struct Bank *b) {
	printf("\n\nBANK REPORT \n");
	printf("COUNT: %i\t\tCAPACITY: %i\n", b->count, b->relayCapacity);
	printf("WAKE TIME %i\t\tLIGHT DURATION: %i\n", b->wakeTime, b->lightDuration);
	printf("SPRAY INT.: %i\t\tSPRAY DURATION: %i\n", b->sprayInterval, b->sprayDuration);
	printf("\n\n");
}

void bankFetchStatus(struct Bank *b) {
	// Get the status from PLC, store in a string
	printf("Fetching status from PLC...\n");
	unsigned char statusHolder[b->relayCapacity + 1];

	sendText("ST\r");
	readText(statusHolder);
	printf("STATUS FROM PLC: %s\n", statusHolder);

	int statusHolderCount = 0;
	unsigned char* statusHolderPtr = statusHolder;
	while (*statusHolderPtr != '\0') {
		statusHolderCount++;
		statusHolderPtr++;
	}

	// Adjust for \r
	statusHolderCount--;

	// Print error if number of relays don't match
	if (statusHolderCount != b->count) {
		printf("STATUS HOLDER SIZE: %i\n", sizeof(statusHolder));

		printf("STATUS FETCH ERROR: Number of relays do not match\n");
		return;
	}

	// Iterate through each character of string,
	// compare to status of relay
		// print something if there's a discrepncy
		// change relay status to reflect what PLC says
	for (int i = 0; i < statusHolderCount; i++) {
		if (b->relays[i]->status != (statusHolder[i]- '0')) {
			printf("STATUS FETCH ERROR: Relay #%i does not match PLC. Adjusting relay status.\n", i);
			b->relays[i]->status = statusHolder[i] - '0';
		}
	}
}

void bankFetchTimers(struct Bank *b) {
	printf("Fetching timers from PLC...\n");
	unsigned char timerHolder[25];

	sendText("TM\r");
	readText(timerHolder);

	// NOTE: THIS SHOULD BE REFACTORED TO THE READ FUNCTION
	// ASSIGN LAST CHAR TO '\0';
	int BUFFER_LAST = 24;
	timerHolder[BUFFER_LAST] = '\0';

	printf("TIMERS FROM PLC: %s\n", timerHolder);

	unsigned char *timerHolderPtr = timerHolder;

	int timerBaseIndex = 0;
	for (int i=0; i<4; i++) {
		// sum the number from ASCII
		int x = 0;
		for (int j=4; j >= 0; j--) {
			x = x + ((timerHolderPtr[timerBaseIndex + j] - '0') * pow(10, 4-j));
		}

		// assign to various variables
		switch (i) {
			case 0:
				b->wakeTime = x;
				break;
			case 1:
				b->lightDuration = x;
				break;
			case 2:
				b->sprayInterval = x;
				break;
			case 3:
				b->sprayDuration = x;
				break;
		}

		// iterate
		timerBaseIndex += 3;
		timerHolderPtr += 3;
	}







}

/*



void bankFetchTimers(struct Bank *b);
int bankSetTimer(int t, int v);
int bankSetTimers(int a, int b, int c, int d);

*/
