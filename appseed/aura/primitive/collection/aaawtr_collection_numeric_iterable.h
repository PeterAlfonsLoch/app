#pragma once


#include "collection_iterable.h"

namespace numeric
{

   namespace iter
   {



   } // namespace iter


} // namespace numeric


template < typename ITERABLE >
class numeric_iterable :
   public iterable < ITERABLE >
{
public:

   typedef typename ITERABLE::iterator iterator;


};


