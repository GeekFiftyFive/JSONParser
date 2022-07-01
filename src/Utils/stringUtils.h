#ifndef jp_STRING_UTILS
#define jp_STRING_UTILS

typedef struct jp_string *jp_string;

jp_string createString();

char *toCString(jp_string);

void appendString(jp_string, char *);

void appendChar(jp_string, char);

int getStringLength(jp_string);

void destroyString(jp_string);

char *stringifyInt(unsigned int);

#endif