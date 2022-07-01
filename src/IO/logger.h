#ifndef LOGGER
#define LOGGER

#include <stdbool.h>

typedef enum
{
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_DEBUG
} jp_logLevel;

void logInfo(const char *, ...);

void logWarn(const char *, ...);

void logError(const char *, ...);

void logDebug(const char *, ...);

void setLevelEnabled(jp_logLevel, bool);

#endif