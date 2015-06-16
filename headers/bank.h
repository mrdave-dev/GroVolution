/* GROVOLUTION - bank.h
 * Struct and function defintions for bank.
 *
 * Author: Dave Martinez
 * Created: June 4, 2015
 * Modified:
 *
 */

#ifndef BANK_H
#define BANK_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../RS-232/rs232.h"

#include "../headers/comms.h"
#include "../headers/relay.h"

struct Bank {


	int count,
		relayCapacity,
		wakeTime,
		lightDuration,
		sprayInterval,
		sprayDuration;

	struct relay *relays[30];
};

struct Bank * bankInit(struct Bank *b);
void bankAddRelay(struct Bank *b, char ab, int r);
void bankTurnAllOn(struct Bank *b);
void bankTurnAllOff(struct Bank *b);
void bankTurnInverse(struct Bank *b);
void bankReport(struct Bank *b);
void bankReportByLabel(struct Bank *b, char* c);
void bankReportTimers(struct Bank *b);
void bankFetchStatus(struct Bank *b);
void bankFetchTimers(struct Bank *b);
int bankSetTimer(int t, int v);
int bankSetTimers(int a, int b, int c, int d);

#endif
