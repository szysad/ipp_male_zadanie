#ifndef COMMAND_H
#define COMMAND_H

#include "list.h"


typedef struct command{
	Tlist *caption;
	int id;
} Tcommand;

extern Tcommand *addCommand();

extern int isCommandValid();

extern int getCommandId();

extern int areDeclareCommandArgumentsValid();

extern int areRemoveCommandArgumentsValid();

extern int areValidCommandArgumentsValid();

extern int areEnergyOneParamCommandArgumentsValid();

extern int areEnergyTwoParamCommandArgumentsValid();

extern int areEqualTwoParamCommandArgumentsValid();


#endif