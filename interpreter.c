#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdint.h>
#include "list.h"

#define COMMANDS_NUMBER 5

#define HASH_CODE 35
#define EOL 10
#define SPACE 32
#define BLANK 0


int is_comment_or_blank(){
	int input;

	input = getchar();
	ungetc(input, stdin);

	return input == HASH_CODE || input == EOL;
}

int getListInput(Tlist **command_p, Tlist **first_p, Tlist **second_p){
	Tlist* command = NULL;
	Tlist* first_param = NULL;
	Tlist* second_param = NULL;

	int command_state = 1;
	int first_param_state = 0;
	int second_param_state = 0;
	int space_state = 0;
	int flag = 1;

	int input;
	int first_elem_flag = 1;

	while((input = getchar()) != EOL && input != EOF && flag){
		if(input == SPACE){
			if(command_state){
				command_state = 0;
				first_param_state = 1;
			}
			else if(first_param_state){
				first_param_state = 0;
				second_param_state = 1;
			}
			//eliminate 2+ spaces in the row
			else if(space_state){
				flag = 0;
			}
			first_elem_flag = 1;
			space_state = 1;
		}
		else{
			if(command_state){
				//check if it is UPPERCASE
				if(!isupper(input)){
					flag = 0;
				}
				command = buildList(command, input, &first_elem_flag);
			}
			else if(first_param_state){
				//check if it is 0-3
				if(input < (int)'0' || input > (int)'3'){
					flag = 0;
				}
				first_param = buildList(first_param, input, &first_elem_flag);		
			}
			else if(second_param_state){
				//check if it is 0-9
				if(!isdigit(input)){
					flag = 0;
				}
				second_param = buildList(second_param, input, &first_elem_flag);
			}
			space_state = 0;
		}
	}
	//check if last char is EOL, if first param is entered, if there arent any spaces in row
	if(input != EOL || first_param == NULL || space_state){
		flag = 0;
	}
	if(!flag){
		deleteList(command);
		deleteList(first_param);
		deleteList(second_param);

		*command_p = NULL;
		*first_p = NULL;
		*second_p = NULL;
		if(input == EOF){
			return EOF;
		}
		else{
			return 0;
		}
	}
	else{
		reverseList(&command);
		reverseList(&first_param);
		reverseList(&second_param);

		*command_p = command;
		*first_p = first_param;
		*second_p = second_param;

		return 1;
	}
}

void print_list(Tlist *l){
	while(l != NULL){
		printf("(%c)", l->value);
		l = l->next;
	}
	printf("\n");
}

uint64_t isEnergyValid(Tlist *energy){
	uint64_t sum = 0;
	uint64_t pow = 1;

	reverseList(&energy);

	char tmp[1];

	while(energy != NULL){
		tmp[0] = energy->value;

		if(pow > UINT64_MAX/10){
			return 0;
		}
		
		if(sum > UINT64_MAX - (uint64_t)atoi(tmp) * pow){
			return 0;
		}

		sum = sum + (uint64_t)atoi(tmp) * pow;
		pow *= 10;
		energy = energy->next;
	}

	return sum;
}


int main(){

	Tlist *command;
	Tlist *first_param;
	Tlist *second_param;
	int flag;

	if(is_comment_or_blank()){
		return 0;
	}
	flag = getListInput(&command, &first_param, &second_param);

	if(flag){
		printf("%s\n", "command: ");
		print_list(command);
		printf("%s\n", "first_param");
		print_list(first_param);
		printf("%s\n", "second_param");
		print_list(second_param);
	}
	else{
		printf("%s\n", "ERROR");
	}

	/* problematyczna funkcja */
	uint64_t t = isEnergyValid(second_param);
	printf("wynik = %llu\n", t);


	return 0;
}