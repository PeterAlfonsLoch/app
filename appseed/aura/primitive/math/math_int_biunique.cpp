#include "framework.h"


index_biunique::index_biunique(::aura::application * papp) : 
   biunique < index >(papp) 
{ 
}

int_biunique::int_biunique(::aura::application * papp) : 
   biunique < int32_t, int_to_int >(papp) 
{ 
}