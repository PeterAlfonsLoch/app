#include "StdAfx.h"

namespace gen
{


   object::object(void)
   {
   }

   object::object(const object & objectSrc) :
      ptri(objectSrc)
   {
   }

   object::~object(void)
   {
   }

   object & object::operator = (const object & objectSrc)
   {
      if(this != &objectSrc)
      {
         ptri::operator =(objectSrc);
      }
      return *this;
   }

} // namespace gen