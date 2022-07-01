#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct jp_linkedList *jp_linkedList;

typedef struct jp_iterator *jp_iterator;

jp_linkedList createLinkedList();

void appendWithFree(jp_linkedList, void *, char *, void *);

void append(jp_linkedList, void *, char *);

void appendList(jp_linkedList, jp_linkedList);

void removeFromListMatchPointer(jp_linkedList, void *);

void removeFromList(jp_linkedList, char *);

void dangerouslyAddFreeFunc(jp_linkedList, void *);

void *getFromList(jp_linkedList, char *);

void listForEach(jp_linkedList, void (*callback)(void *, void *, char *), void *);

char *listToString(jp_linkedList);

int listLength(jp_linkedList);

jp_iterator getIterator(jp_linkedList);

void *iteratorNext(jp_iterator);

void destroyIterator(jp_iterator);

void destroyLinkedList(jp_linkedList);

#endif