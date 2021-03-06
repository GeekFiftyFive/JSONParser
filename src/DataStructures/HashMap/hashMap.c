#include <stdlib.h>
#include "hashMap.h"
#include "../../IO/logger.h"

#define DEFAULT_LOAD_FACTOR 0.8

struct jp_hashMap
{
  jp_linkedList *entries;
  jp_linkedList insertions;
  int size;
  int usage;
  float loadFactor;
};

struct dataWithFree
{
  void *data;
  void (*freeFunc)(void *);
};

jp_hashMap createHashMap(int initCapacity)
{
  return createHashMapWithLoadFactor(initCapacity, DEFAULT_LOAD_FACTOR);
}

jp_hashMap createHashMapWithLoadFactor(int initCapacity, float loadFactor)
{
  jp_hashMap map = malloc(sizeof(struct jp_hashMap));

  map->entries = malloc(initCapacity * sizeof(jp_linkedList));
  map->size = initCapacity;
  map->loadFactor = loadFactor;
  map->usage = 0;

  // Initialise every linkedList
  for (int i = 0; i < initCapacity; i++)
  {
    map->entries[i] = createLinkedList();
  }

  map->insertions = createLinkedList();

  return map;
}

int hash(char *key)
{
  int hashAddress = 0;
  for (int i = 0; key[i] != '\0'; i++)
  {
    hashAddress = key[i] + (hashAddress << 6) + (hashAddress << 16) - hashAddress;
  }

  return hashAddress > 0 ? hashAddress : -hashAddress;
}

void addToNewTable(void *nodeData, void *accData, char *key)
{
  jp_hashMap map = (jp_hashMap)accData;
  struct dataWithFree *pair = (struct dataWithFree *)nodeData;
  insertIntoHashMap(map, key, pair->data, pair->freeFunc);
}

void insertIntoHashMap(jp_hashMap map, char *key, void *data, void *freeFunc)
{
  int location = hash(key) % map->size;

  if (freeFunc)
    appendWithFree(map->entries[location], data, key, freeFunc);
  else
    append(map->entries[location], data, key);

  struct dataWithFree *pair = malloc(sizeof(struct dataWithFree));
  pair->data = data;
  pair->freeFunc = freeFunc;
  appendWithFree(map->insertions, pair, key, free);

  map->usage++;

  if ((float)map->usage / map->size > map->loadFactor)
  {
    jp_hashMap newMap = createHashMapWithLoadFactor(map->size * 2, map->loadFactor);
    listForEach(map->insertions, addToNewTable, newMap);
    for (int i = 0; i < map->size; i++)
    {
      dangerouslyAddFreeFunc(map->entries[i], NULL);
      destroyLinkedList(map->entries[i]);
    }
    map->size *= 2;
    map->entries = newMap->entries;
    destroyLinkedList(newMap->insertions);
    free(newMap);
  }
}

void *getFromHashMap(jp_hashMap map, char *key)
{
  int location = hash(key) % map->size;
  return getFromList(map->entries[location], key);
}

jp_linkedList getHashesMatching(jp_hashMap map, char *key)
{
  int location = hash(key) % map->size;
  return map->entries[location];
}

void printHashMap(jp_hashMap map)
{
  logInfo("HashMap: Usage %d, Size %d [\n", map->usage, map->size);
  for (int i = 0; i < map->size; i++)
  {
    char *listString = listToString(map->entries[i]);
    logInfo("%s\n", listString);
    free(listString);
  }
  logInfo("]\n");
}

void destroyHashMap(jp_hashMap map)
{
  for (int i = 0; i < map->size; i++)
  {
    destroyLinkedList(map->entries[i]);
  }

  destroyLinkedList(map->insertions);
  free(map->entries);
  free(map);
}