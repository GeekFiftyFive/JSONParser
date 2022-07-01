#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stringUtils.h"

struct jp_string
{
  char *cString;
  int capacity;
  int length;
};

jp_string createString()
{
  jp_string string = malloc(sizeof(struct jp_string));

  string->capacity = 4;
  string->cString = malloc(string->capacity);
  string->length = 0;

  return string;
}

char *toCString(jp_string string)
{
  char *out = malloc(string->length + 1);
  strcpy(out, string->cString);
  return out;
}

static void expand(jp_string string, int length)
{
  if (string->length + length > string->capacity / 2)
  {
    string->capacity *= (2 * (1 + length / string->capacity));
    string->cString = realloc(string->cString, string->capacity);
  }
}

void appendString(jp_string string, char *app)
{
  int len = strlen(app);

  expand(string, len);

  memcpy(string->cString + string->length, app, len);
  string->length += len;
  string->cString[string->length] = '\0';
}

void appendChar(jp_string string, char chr)
{
  expand(string, 1);

  string->cString[string->length] = chr;
  string->cString[string->length + 1] = '\0';
  string->length++;
}

int getStringLength(jp_string string)
{
  return string->length;
}

void destroyString(jp_string string)
{
  free(string->cString);
  free(string);
}

char *stringifyInt(unsigned int num)
{
  char *str = malloc((int)ceil(log10((num ? num : 1) + 1)) + 1);
  sprintf(str, "%d", num);
  return str;
}
