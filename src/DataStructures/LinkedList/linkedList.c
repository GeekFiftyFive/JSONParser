#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linkedList.h"

typedef struct jp_listNode *jp_listNode;

struct jp_linkedList
{
  int length;
  jp_listNode head;
  jp_listNode tail;
};

struct jp_listNode
{
  char *key;
  void *data;
  void (*freeFunc)(void *);
  jp_listNode prev;
  jp_listNode next;
};

struct jp_iterator
{
  jp_listNode current;
  jp_listNode start;
  int length;
  int index;
};

jp_linkedList createLinkedList()
{
  jp_linkedList list = malloc(sizeof(struct jp_linkedList));
  list->head = NULL;
  list->tail = NULL;
  list->length = 0;
  return list;
}

void appendWithFree(jp_linkedList list, void *data, char *key, void *freeFunc)
{
  // Create a new node to store the data
  jp_listNode node = malloc(sizeof(struct jp_listNode));
  if (key)
  {
    char *keyCopy = malloc(strlen(key) + 1);
    node->key = strcpy(keyCopy, key);
  }
  else
  {
    node->key = NULL;
  }

  node->data = data;
  node->freeFunc = freeFunc;

  // Append the node to the list
  if (!list->tail)
  {
    list->head = node;
    node->next = node;
    node->prev = node;
  }
  else
  {
    jp_listNode tail = list->tail;
    tail->next = node;
    node->prev = tail;
    node->next = list->head;
    list->head->prev = node;
  }

  list->tail = node;
  list->length++;
}

void append(jp_linkedList list, void *data, char *key)
{
  appendWithFree(list, data, key, NULL);
}

void appendListCallback(void *elementData, void *callbackData, char *elementKey)
{
  jp_linkedList dest = (jp_linkedList)callbackData;
  append(dest, elementData, elementKey);
}

void appendList(jp_linkedList dest, jp_linkedList src)
{
  listForEach(src, appendListCallback, dest);
}

void removeNode(jp_linkedList list, jp_listNode node)
{
  if (list->head == node)
  {
    if (list->length == 1)
    {
      list->head = NULL;
    }
    else
    {
      list->head = node->next;
    }
  }
  if (list->tail == node)
  {
    if (list->length == 1)
    {
      list->tail = NULL;
    }
    else
    {
      list->tail = node->prev;
    }
  }
  jp_listNode next = node->next;
  jp_listNode prev = node->prev;
  next->prev = prev;
  prev->next = next;
  if (node->freeFunc)
  {
    node->freeFunc(node->data);
  }
  if (node->key)
  {
    free(node->key);
  }
  list->length--;
}

void removeFromListMatchPointer(jp_linkedList list, void *ptr)
{
  if (!list->head)
    return;

  jp_listNode current = list->head;

  do
  {
    if (ptr == current->data)
    {
      removeNode(list, current);
      return;
    }
    current = current->next;
  } while (current != list->head);
}

void removeFromList(jp_linkedList list, char *key)
{
  if (!list->head)
    return;

  jp_listNode current = list->head;

  do
  {
    if (strcmp(current->key, key) == 0)
    {
      removeNode(list, current);
      return;
    }
    current = current->next;
  } while (current != list->head);
}

void dangerouslyAddFreeFunc(jp_linkedList list, void *freeFunc)
{
  if (list->length == 0)
    return;
  jp_listNode current = list->head;

  do
  {
    current->freeFunc = freeFunc;
    current = current->next;
  } while (current != list->head);
}

void *getFromList(jp_linkedList list, char *key)
{
  if (!list->head)
    return NULL;

  jp_listNode current = list->head;

  do
  {
    if (strcmp(current->key, key) == 0)
      return current->data;
    current = current->next;
  } while (current != list->head);

  return NULL;
}

void listForEach(jp_linkedList list, void (*callback)(void *, void *, char *), void *data)
{
  if (list->length == 0)
    return;
  jp_listNode current = list->head;

  do
  {
    callback(current->data, data, current->key);
    current = current->next;
  } while (current != list->head);
}

char *listToString(jp_linkedList list)
{
  if (list->length == 0)
  {
    char *blank = malloc(3);
    strcpy(blank, "[]");
    return blank;
  }

  // Accumulate length of keys
  // TODO: Re-allocate the length of the string instead of traversing the list twice
  int accLength = 0;
  jp_listNode current = list->head;

  do
  {
    accLength += strlen(current->key);
    current = current->next;
  } while (current != list->head);

  char *out = malloc(accLength + 4 * (list->length - 1) + 1);
  size_t offset = 0;

  do
  {
    if (current->next == list->head)
    {
      sprintf(out + offset, "%s", current->key);
    }
    else
    {
      sprintf(out + offset, "%s -> ", current->key);
      offset += strlen(current->key) + 4;
    }

    current = current->next;
  } while (current != list->head);

  return out;
}

int listLength(jp_linkedList list)
{
  return list->length;
}

jp_iterator getIterator(jp_linkedList list)
{
  jp_iterator iterator = malloc(sizeof(struct jp_iterator));
  iterator->current = NULL;
  iterator->start = list->head;
  iterator->length = list->length;
  iterator->index = 0;
  return iterator;
}

void *iteratorNext(jp_iterator iterator)
{
  if (!iterator->current)
  {
    iterator->current = iterator->start;
  }
  else if (iterator->length - 1 == iterator->index)
  {
    return NULL;
  }
  else
  {
    iterator->current = iterator->current->next;
    iterator->index++;
  }

  if (!iterator->current)
  {
    return NULL;
  }

  return iterator->current->data;
}

void destroyIterator(jp_iterator iterator)
{
  free(iterator);
}

void destroyLinkedList(jp_linkedList list)
{
  if (list->length == 0)
  {
    free(list);
    return;
  }

  jp_listNode current = list->head;

  do
  {
    if (current->freeFunc)
    {
      current->freeFunc(current->data);
    }
    if (current->key)
    {
      free(current->key);
    }
    jp_listNode next = current->next;
    free(current);
    current = next;
  } while (current != list->head);

  free(list);
}