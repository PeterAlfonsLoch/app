#include "framework.h"

#ifdef DEBUG

void _debug_arrayPtrAlloc();

void _debug_arrayPtrAlloc()
{
   array_ptr_alloc < int, int > ia;
   
   ia.add(1);

   int * pa = ia.ptr_at(0);
   UNREFERENCED_PARAMETER(pa);

   ia.set_at_grow(20, 32);

}

#endif // DEBUG