#include "framework.h"

#ifdef DEBUG


void _debug_arrayPtrAlloc();

void _debug_arrayPtrAlloc()
{
   array_ptr_alloc < int32_t, int32_t > ia;
   
   ia.add(1);

   int32_t * pa = ia.ptr_at(0);
   UNREFERENCED_PARAMETER(pa);

   ia.set_at_grow(20, 32);

}

#endif // DEBUG