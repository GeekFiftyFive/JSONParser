#ifndef TUPLE
#define TUPLE

typedef struct
{
    float x;
    float y;
} jp_tuple;

jp_tuple productTuple(jp_tuple, jp_tuple);

jp_tuple multiplyTuple(float, jp_tuple);

jp_tuple divideTuple(jp_tuple, jp_tuple);

jp_tuple addTuple(jp_tuple, jp_tuple);

jp_tuple subtractTuple(jp_tuple, jp_tuple);

jp_tuple normaliseTuple(jp_tuple);

void printTuple(jp_tuple);

#endif