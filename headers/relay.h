/* GROVOLUTION - relay.h
 * Struct and function defintions for relay.
 *
 * Author: Dave Martinez
 * Created: June 4, 2015
 * Modified:
 *
 */

#ifndef RELAYS_H
#define RELAYS_H

#include <stdlib.h>
#include <stdio.h>

#include "../RS-232/rs232.h"

#include "../headers/comms.h"

struct relay {
	char 	label;
	int 	number;
	int 	status;
};

struct relay* 	initRelay(struct relay* r, char ab, int n);
void 	setRelayNum(struct relay* r, int n);
void 	setRelayLabel(struct relay* r, char ab);
int 	switchRelay(struct relay* r);
int 	onRelay(struct relay* r);
int		offRelay(struct relay* r);
char	getLabelRelay(struct relay* r);
int		getNumRelay(struct relay* r);
int		getStatusRelay(struct relay* r);
void	printRelay(struct relay* r);

#endif
