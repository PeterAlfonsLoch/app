#include "framework.h"


index_biunique::index_biunique(::ca::application * papp) : 
   biunique < index >(papp) 
{ 
}

int_biunique::int_biunique(::ca::application * papp) : 
   biunique < int, ::collection::int_to_int >(papp) 
{ 
}