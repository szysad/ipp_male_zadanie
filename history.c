#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"
#include "history.h"


uint64_t safeAverage(uint64_t a, uint64_t b){
	return (a/2) + (b/2) + (a & b & 1);
}

void printNode(Ttrienode *node){

	if(node == NULL){
		printf("%s\n", "node is NULL");
		return;
	}

	printf("energy: %llu\n", node->energy);
	printf("is energy set: %d\n", node->is_energy_set);
	printf("relation next: %p\n", node->relation_next);
	printf("zero: %p\n", node->zero);
	printf("one: %p\n", node->one);
	printf("two: %p\n", node->two);
	printf("three: %p\n", node->three);
}

Ttrienode *newNode(uint64_t energy){
	Ttrienode *new = malloc(sizeof(Ttrienode));
	new->energy = energy;
	new->is_energy_set = 0;
	new->relation_next = new;
	new->zero = NULL;
	new->one = NULL;
	new->two = NULL;
	new->three = NULL;

	return new;
}

Ttrienode *getHistoryNode(Ttrienode *history, Tlist *path){
	assert(path != NULL);
	while(path != NULL){
		switch(path->value){
			case 0:
				history = history->zero;
				break;
			case 1:
				history = history->one;
				break;
			case 2:
				history = history->two;
				break;
			case 3:
				history = history->three;
				break;
		}
		path = path->next;
	}
	return history;
}

void setHistoriesInRelationEnergy(Ttrienode *history, uint64_t energy){
	Ttrienode *start = history;
	do{
		history->is_energy_set = 1;
		history->energy = energy;
		history = history->relation_next;
	}while(history != start);
}

void setHistoryEnergy(Ttrienode *history, Tlist *path, uint64_t energy){
	setHistoriesInRelationEnergy(getHistoryNode(history, path), energy);
}

int areHistoriesInRelation(Ttrienode *history1, Ttrienode *history2){
	Ttrienode *start = history1;

	history1 = history1->relation_next;

	while((history1 != start) && (history1 != history2)){
		history1 = history1->relation_next;
	}

	return history1 == history2;
}

void removeNodeFromRelation(Ttrienode *node){
	Ttrienode *elem = node;

	while(elem != NULL && elem->relation_next != node){
		elem = elem->relation_next;
	}

	elem->relation_next = node->relation_next;
}

void removeTreeNode(Ttrienode **node){
	if(*node == NULL){
		return;
	}

	removeNodeFromRelation(*node);

	removeTreeNode(&((*node)->zero));
	removeTreeNode(&((*node)->one));
	removeTreeNode(&((*node)->two));
	removeTreeNode(&((*node)->three));

	free(*node);
	(*node)->is_energy_set = 0;
	(*node)->energy = 0;
	(*node)->relation_next = NULL;
	*node = NULL;
}

void removeHistory(Ttrienode *history, Tlist *path){
	if(path == NULL){
		return;
	}

	while(history != NULL && path->next != NULL){
		switch(path->value){
			case 0:
				history = history->zero;
				break;
			case 1:
				history = history->one;
				break;
			case 2:
				history = history->two;
				break;
			case 3:
				history = history->three;
				break;
		}
		path = path->next;
	}

	if(history == NULL){
		return;
	}

	switch(path->value){
		case 0:
			removeTreeNode(&(history->zero));
			history->zero = NULL;
			break;
		case 1:
			removeTreeNode(&(history->one));
			history->one = NULL;
			break;
		case 2:
			removeTreeNode(&(history->two));
			history->two = NULL;
			break;
		case 3:
			removeTreeNode(&(history->three));
			history->three = NULL;
			break;
	}
}

void makeHistoriesEqual(Ttrienode *history, Tlist *path1, Tlist *path2){
	if(path1 == path2){
		return;
	}

	Ttrienode *path1_node = getHistoryNode(history, path1);
	Ttrienode *path2_node = getHistoryNode(history, path2);
	Ttrienode *path1_relation_next = path1_node->relation_next;
	Ttrienode *path2_relation_next = path2_node->relation_next;
	uint64_t new_value;

	if(areHistoriesInRelation(path1_node, path2_node)){
		return;
	}

	if(path1_node->is_energy_set + path2_node->is_energy_set == 2){
		new_value = safeAverage(path1_node->energy, path2_node->energy);
	}
	else if(path1_node->is_energy_set + path2_node->is_energy_set == 1){	
		if(path1_node->is_energy_set){
			new_value = path1_node->energy;
		}
		else if(path2_node->is_energy_set){
			new_value = path2_node->energy;
		}
	}

	path2_node->relation_next = path1_relation_next;
	path1_node->relation_next = path2_relation_next;

	setHistoriesInRelationEnergy(path1_node, new_value);
}

uint64_t getHistoryEnergy(Ttrienode *history, Tlist *path){
	Ttrienode *history_state = getHistoryNode(history, path);

	return history_state->energy;
}

int isHistoryEnergySet(Ttrienode *history, Tlist *path){
	Ttrienode *history_state = getHistoryNode(history, path);

	return history_state->is_energy_set;
}

int isHistoryValid(Ttrienode *history, Tlist *path){
	while(history != NULL && path != NULL){
		switch(path->value){
			case 0:
				history = history->zero;
				break;
			case 1:
				history = history->one;
				break;
			case 2:
				history = history->two;
				break;
			case 3:
				history = history->three;
				break;
		}
		path = path->next;
	}
	return (history != NULL);
}

void allowHistory(Ttrienode *history, Tlist *path){
	if(history == NULL || path == NULL){
		return;
	}
	switch(path->value){
		case 0:
			if(history->zero == NULL){
				history->zero = newNode(0);
			}
			allowHistory(history->zero, path->next);
			break;
		case 1:
			if(history->one == NULL){
				history->one = newNode(0);
			}
			allowHistory(history->one, path->next);
			break;
		case 2:
			if(history->two == NULL){
				history->two = newNode(0);
			}
			allowHistory(history->two, path->next);
			break;
		case 3:
			if(history->three == NULL){
				history->three = newNode(0);
			}
			allowHistory(history->three, path->next);
			break;
		default:
			return;
			break;
	}
}

void printHistory(Ttrienode *history){
	if(history == NULL){
		return;
	}

	if(history->zero != NULL){
		printf("[%d]", 0);
		printHistory(history->zero);
		printf("\n");
	}
	if(history->one != NULL){
		printf("[%d]", 1);
		printHistory(history->one);
		printf("\n");
	}
	if(history->two != NULL){
		printf("[%d]", 2);
		printHistory(history->two);
		printf("\n");
	}
	if(history->three != NULL){
		printf("[%d]", 3);
		printHistory(history->three);
		printf("\n");
	}
}

void cleanHistory(Ttrienode **history){
	removeTreeNode(history);
	free(*history);
}

void printList(Tlist *l){
	while(l != NULL){
		printf("[%d]", l->value);
		l = l->next;
	}
	printf("\n");
}


int main(){

	Ttrienode *data = newNode(0);
	Tlist *history1 = NULL;
	Tlist *history2 = NULL;

	int h1_arr[5] = {1,2,3,1,2};
	int h2_arr[5] = {1,2,3,1,2};

	int f = 1;

	for(int i=0; i<5; i++){
		history1 = buildList(history1, h1_arr[i], &f);
	}
	f = 1;
	for(int i=0; i<5; i++){
		history2 = buildList(history2, h2_arr[i], &f);
	}

	reverseList(&history1);
	reverseList(&history2);

	allowHistory(data, history1);

	printHistory(data);

	removeHistory(data, history2);

	printHistory(data);

	return 0;
}