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
	t->relays = (struct relay) malloc(t->relayCapacity * sizeof(struct relay)); // something wrong here
}

void bankAddRelay(struct Bank *b, char ab, int r) {
	b->relays[b->count] = initRelay(ab, r);
	b->count++;
}
/*
void bankTurnAllOn(struct Bank b);
void bankTurnAllOff(struct Bank b);
void bankTurnInverse(struct Bank b);
void bankReport(struct Bank b);
void bankReportByName(struct Bank b, char* c);
void bankReportTimers(struct Bank b);
void bankFetchStatus(struct Bank b);
void bankFetchTimers(struct Bank b);
int bankSetTimer(int t, int v);
int bankSetTimers(int a, int b, int c, int d);

*/
