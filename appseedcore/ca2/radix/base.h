#pragma once

#include "gen/gen_holder.h"

/////////////////////////////////////////////////////////////////////////////
// class ::radix::object is the root of all compliant objects
template < class T >
class base 
{
public:


   template < class T2 >
   inline static bool bases(T2 * p) 
   {
      return dynamic_cast < T * > (p) != NULL; 
   }


   template < class T2 >
   inline static bool bases(const ::gen::holder < T2 > & holder) 
   { 
      return dynamic_cast < T * > ((T2 *) holder) != NULL; 
   }

};
