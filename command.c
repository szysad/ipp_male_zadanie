#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "list.h"
#include "history.h"


Tcommand *addCommand(char command_caption[], int id){
	int first_elem_flag = 1;
	Tlist *caption;
	Tcommand *command = malloc(sizeof(Tcommand));

	for(int i = 0; i < strlen(command_caption); i++){
		caption = buildList(caption, command_caption[i], &first_elem_flag);
	}

	reverseList(&caption);

	command->caption = caption;
	command->id = id;

	return command;
}

int getCommandId(Tlist *command, Tcommand *command_set[], int commands_number, int command_not_found){

	for(int i = 0; i < commands_number; i++){
		if(areListsEqual(command, command_set[i]->caption)){
			return getCommandId(command);
		}
	}

	return command_not_found;
}

int getCommandId(Tcommand *command){
	return command->id;
}

int areDeclareCommandArgumentsValid(Tlist *first_param, Tlist *second_param){
	return second_param == NULL;
}

int areRemoveCommandArgumentsValid(Tlist *first_param, Tlist *second_param){
	return second_param == NULL; 
}

int areValidCommandArgumentsValid(Tlist *first_param, Tlist *second_param){
	return second_param == NULL;
}

int areEnergyOneParamCommandArgumentsValid(Ttrienode *history, Tlist *first_param, Tlist *second_param){
	if(second_param != NULL){
		return 0;
	}

	return isHistoryValid(first_param);
}

int areEnergyTwoParamCommandArgumentsValid(Tlist *first_param, Tlist *second_param){
	if(second_param == NULL){
		return 0;
	}

	return isHistoryValid(first_param);
}