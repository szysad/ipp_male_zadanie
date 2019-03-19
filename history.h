#ifndef HISTORY_H
#define HISTORY_H

typedef struct trieNode{
	uint64_t energy;
	int is_energy_set;
	struct trieNode *relation_next;
	struct trieNode *zero;
	struct trieNode *one;
	struct trieNode *two;
	struct trieNode *three;
} Ttrienode;

#endif