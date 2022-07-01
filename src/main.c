#include <stdlib.h>
#include "./IO/logger.h"
#include "./JSON/jsonParser.h"
#include "./IO/fileIO.h"

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    logError("Expected filename and json path");
    return 1;
  }

  char *file = readFile(argv[1]);

  jp_json json = jsonParse(file);

  logInfo(getJSONString(json, argv[2], NULL));

  free(file);

  destroyJSON(json);

  return 0;
}
