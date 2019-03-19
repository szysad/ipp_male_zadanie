#ifndef LIST_H
#define LIST_H


typedef struct list {
	int value;
	struct list *next;
} Tlist;


extern Tlist *makeListElement();

extern void addElementAfter();

extern Tlist *addFirstElement();

extern void deleteList();

extern void reverseList();

extern int getListLength();

extern int areListsEqual();

extern Tlist *buildList();


#endif