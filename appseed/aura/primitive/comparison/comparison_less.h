#pragma once


#include "aura/primitive/collection/collection_iterator.h"


template < class TYPE >
inline bool LessCompareElements(TYPE element1, TYPE element2)
{
   return element1 < element2;
}


namespace comparison
{

   
   class less
   {
   public:

      template < typename TYPE >
      static inline bool run(TYPE element1, TYPE element2)
      {
         return ::LessCompareElements < TYPE > (element1, element2);
      }


   };


} // namespace comparison

template <bool b> struct StaticAssertionFailed;
template <> struct StaticAssertionFailed <true> {};

#define STATIC_ASSERT(x) \
    {StaticAssertionFailed <x> ();}

namespace comparison
{


   template < >
   inline bool less::run(const string & element1,const string & element2)
   {
      return element1 < element2;
   }



} // namespace comparison






