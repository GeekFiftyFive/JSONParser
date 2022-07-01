#include <math.h>
#include "../../IO/logger.h"
#include "tuple.h"

jp_tuple productTuple(jp_tuple a, jp_tuple b)
{
  return (jp_tuple){a.x * b.x, a.y * b.y};
}

jp_tuple multiplyTuple(float multiple, jp_tuple tuple)
{
  return (jp_tuple){multiple * tuple.x, multiple * tuple.y};
}

jp_tuple divideTuple(jp_tuple a, jp_tuple b)
{
  return (jp_tuple){a.x / b.x, a.y / b.y};
}

jp_tuple addTuple(jp_tuple a, jp_tuple b)
{
  return (jp_tuple){a.x + b.x, a.y + b.y};
}

jp_tuple subtractTuple(jp_tuple a, jp_tuple b)
{
  return (jp_tuple){a.x - b.x, a.y - b.y};
}

jp_tuple normaliseTuple(jp_tuple tuple)
{
  float hyp = sqrt(tuple.x * tuple.x + tuple.y * tuple.y);
  return (jp_tuple){tuple.x / hyp, tuple.y / hyp};
}

void printTuple(jp_tuple tuple)
{
  logInfo("{ %f, %f }\n", tuple.x, tuple.y);
}
