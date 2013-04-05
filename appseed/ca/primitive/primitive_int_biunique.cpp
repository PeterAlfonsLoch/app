#include "framework.h"


index_biunique::index_biunique(::ca::applicationsp papp) : 
   biunique < index >(papp) 
{ 
}

int_biunique::int_biunique(::ca::applicationsp papp) : 
   biunique < int32_t, int_to_int >(papp) 
{ 
}