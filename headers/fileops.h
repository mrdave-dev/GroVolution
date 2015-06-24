/* GROVOLUTION - fileops.h
 * File operation functions for the GroVolution CLI
 *
 * Author: Dave Martinez
 * Created: June 23, 2015
 * Modified:
 *
 */

#ifndef FILEOPS_H
#define FILEOPS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <errno.h>

#include "../RS-232/rs232.h"

#include "../headers/comms.h"
#include "../headers/relay.h"
#include "../headers/bank.h"

int bankSave(struct Bank *b);
struct Bank* bankLoad(char* fn);


#endif
