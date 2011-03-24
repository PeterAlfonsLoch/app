#include "StdAfx.h"

namespace gen
{

   ptri::ptri(void)
   {
   }

   ptri::ptri(const ptri & ptriSrc) :
      ::ca::object(ptriSrc)
   {
   }

   ptri::~ptri(void)
   {
   }

   ptri & ptri::operator = (const ptri & ptriSrc)
   {
      if(this != &ptriSrc)
      {
         ::ca::object::operator =(ptriSrc);
      }
      return *this;
   }

}