#include "framework.h"

#ifdef DEBUG

void _base_comparable_array_debug();

void _base_comparable_array_debug()
{
   comparable_array<int32_t,int32_t> ia;
   int32_t i = 1;
   ia.find_first(i);
   ia.remove_first(i);
}

#endif