#pragma once


#include "aura/filestream.h"
#include "collection.h"



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
::file::ostream & operator << (::file::ostream & os, const map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & a)
{
   ::file::map::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
::file::istream & operator >> (::file::istream & is, map < KEY, ARG_KEY, VALUE, ARG_VALUE, PAIR > & a)
{
   ::file::map::read(is, a);
   return is;
}



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
::file::ostream & operator << (::file::ostream & os, const ::property_map & a)
{
   ::file::map::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
::file::istream & operator >> (::file::istream & is, property_map & a)
{
   ::file::map::read(is, a);
   return is;
}




