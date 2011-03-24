#include "StdAfx.h"

#ifdef WIN32
#include <windows.h>
#endif

namespace ca
{

   object::object()
   {
   }

   object::~object()
   {
   }

   object::object(const object & o)
   {
      operator = (o);
   }

   object & object::operator =(const object & o)
   {
      if(this != &o)
      {
         ::ca::ca::operator = (o);
      }
      return *this;
   }

   void object::delete_this()
   {
      if(m_ulFlags & flag_discard_to_factory)
      {
         System.factory().discard(this);
      }
      else if(m_ulFlags & flag_heap_alloc)
      {
         delete this;
      }
   }

} // namespace ca
