#ifndef COMMS_H
#define COMMS_H

#include <stdio.h>		// printf
#include <unistd.h> 	// usleep

// Outside libraries
#include "../RS-232/rs232.h"

// Custom defintions
#include "../sources/constants.c"

int sendText(const char* tx);
void readText(unsigned char* rx);

#endif
