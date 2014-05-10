#include "framework.h"


index_biunique::index_biunique(sp(::base::application) papp) : 
   biunique < index >(papp) 
{ 
}

int_biunique::int_biunique(sp(::base::application) papp) : 
   biunique < int32_t, int_to_int >(papp) 
{ 
}