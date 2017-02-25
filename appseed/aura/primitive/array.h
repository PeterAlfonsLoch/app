#pragma once


#include "aura/primitive/collection/collection_common.h"
#include "aura/primitive/collection/collection_decl.h"
#include "aura/primitive/collection/collection_array_decl.h"
#include "aura/primitive/collection/collection_raw_array_decl.h"
#include "aura/primitive/collection/collection_lemon_array_decl.h"
#include "aura/primitive/collection/collection_smart_pointer_array.h"
#include "aura/primitive/collection/collection_comparable_eq_array.h"
#include "aura/primitive/collection/collection_comparable_array.h"
#include "aura/primitive/collection/collection_comparable_raw_array.h"


#include "aura/primitive/collection/collection_sort_array.h"


#include "aura/primitive/collection/collection_ptr_array.h"




template < class Type, class RawType >
inline ::file::ostream & operator << (::file::ostream & ostream, const string_array < Type, RawType > & a)
{
   ostream.write_arbitrary(a->get_count());
   for (int32_t i = 0; i < a->get_size(); i++)
   {
      ostream << a->element_at(i);
   }
   return ostream;
}


template < class Type, class RawType >
inline ::file::istream &  operator >>(::file::istream & istream, string_array < Type, RawType > & a)
{

   if (istream.fail())
   {

      return;

   }

   ::count iSize;

   istream.read_arbitrary(iSize);

   if (istream.fail())
   {

      return;

   }

   this->remove_all();

   this->set_size(iSize);

   for (int32_t i = 0; i < iSize; i++)
   {

      istream >> this->element_at(i);

      if (istream.fail())
      {

         return;

      }

   }

   if (this->get_size() != iSize)
   {

      istream.setstate(::file::failbit);

   }

   return istream;

}
