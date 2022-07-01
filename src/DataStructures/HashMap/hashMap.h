#ifndef HASH_TABLE
#define HASH_TABLE

#include "../LinkedList/linkedList.h"

typedef struct jp_hashMap *jp_hashMap;

jp_hashMap createHashMap(int);

jp_hashMap createHashMapWithLoadFactor(int, float);

void insertIntoHashMap(jp_hashMap, char *, void *, void *);

void *getFromHashMap(jp_hashMap, char *);

jp_linkedList getHashesMatching(jp_hashMap, char *);

void printHashMap(jp_hashMap);

void destroyHashMap(jp_hashMap);

#endif