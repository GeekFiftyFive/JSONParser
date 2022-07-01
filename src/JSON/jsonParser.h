#ifndef JSON_PARSER
#define JSON_PARSER
#include "jsonCore.h"

typedef enum
{
  JSON_NO_ERROR,
  JSON_ERROR
} jp_jsonError;

typedef enum
{
  JSON_NUMBER,
  JSON_BOOL,
  JSON_STRING,
  JSON_OTHER
} jp_jsonType;

jp_json jsonParse(char *);

jp_json getJSONObject(jp_json, char *, jp_jsonError *);

int getJSONInt(jp_json, char *, jp_jsonError *);

bool getJSONBool(jp_json, char *, jp_jsonError *);

double getJSONDouble(jp_json, char *, jp_jsonError *);

char *getJSONString(jp_json, char *, jp_jsonError *);

bool jsonFieldExists(jp_json, char *);

bool isJSONFieldArray(jp_json, char *);

bool isJSONFieldBoolean(jp_json, char *);

void jsonArrayForEach(jp_json, char *, void (*callback)(jp_json, void *), void *);

void jsonObjectForEach(jp_json, char *, void (*callback)(jp_json, void *), void *);

jp_jsonType getJSONType(jp_json);

char *getFieldName(jp_json);

int getJSONArrayLength(jp_json, char *);

void freeJson(jp_json);

#endif