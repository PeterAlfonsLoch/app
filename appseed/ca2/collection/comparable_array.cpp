#include "StdAfx.h"

#ifdef _DEBUG

void _base_comparable_array_debug()
{
   comparable_array<int,int> ia;
   int i = 1;
   ia.find_first(i);
   ia.remove_first(i);
}
#endif