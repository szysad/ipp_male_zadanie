#include <stdlib.h>
#include "list.h"


void addElementAfter(Tlist *list, int val){
	Tlist *new = malloc(sizeof(Tlist));
	new->value = val;
	new->next = list->next;
}

int getListLength(Tlist *list){
	int len = 0;

	while(list != NULL){
		len++;
		list = list->next;
	}

	return len;
}

int areListsEqual(Tlist *list1, Tlist *list2){

	int flag = 1;

	while(list1 != NULL && list2 != NULL && flag){
		if(list1->value != list2->value){
			flag = 0;
		}
		list1 = list1->next;
		list2 = list2->next;
	}

	return flag && list1 == NULL && list2 == NULL;
}

Tlist *makeListElement(Tlist *next, int val){
	Tlist *new = malloc(sizeof(Tlist));
	new->value = val;
	new->next = next;

	return new;
}

Tlist *addFirstElement(Tlist *next_elem, int val){
	Tlist *new = malloc(sizeof(Tlist));
	new->value = val;
	new->next = next_elem;

	return new;
}

void deleteList(Tlist *list){
	Tlist *tmp;

	while(list != NULL){
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void reverseList(Tlist** list){
	Tlist* nl = NULL;
	Tlist* tmp;

	while(*list != NULL){
		tmp = (*list)->next;
		(*list)->next = nl;
		nl = *list;
		*list = tmp;
	}
	*list = nl;
}

Tlist *buildList(Tlist *next, int val, int *first_elem_flag){
	if(*first_elem_flag){
		next = addFirstElement(NULL, val);
		*first_elem_flag = 0;
	}
	else{
		next = addFirstElement(next, val);
	}

	return next;
}