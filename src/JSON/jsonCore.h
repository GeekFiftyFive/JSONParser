#ifndef JP_JSON_CORE
#define JP_JSON_CORE

#include <stdbool.h>

typedef struct jp_json *jp_json;
typedef struct jp_jsonObject *jp_jsonObject;
typedef struct jp_jsonArray *jp_jsonArray;
typedef union jp_jsonNumber jp_jsonNumber;
typedef bool jp_jsonBoolean;

bool isJSONObject(jp_json);

bool isJSONArray(jp_json);

bool isJSONInteger(jp_json);

bool isJSONFloat(jp_json);

bool isJSONNumber(jp_json);

bool isJSONString(jp_json);

bool isJSONBool(jp_json);

bool isJSONArray(jp_json);

char *getJSONFieldName(jp_json);

int jsonToInt(jp_json);

float jsonToFloat(jp_json);

char *jsonToString(jp_json);

bool jsonToBool(jp_json);

jp_json *jsonToArray(jp_json);

int jsonArrayLength(jp_json);

jp_json getJSONField(jp_json, const char *);

jp_json parseJSON(const char *);

void jsonObjectIterate(jp_json, void (*callback)(void *, void *), void *);

void destroyJSON(jp_json);

#endif
