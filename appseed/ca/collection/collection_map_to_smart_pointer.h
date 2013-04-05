#pragma once


template < class TYPE, class ARG_TYPE, class T >
class map_to_smart_pointer :
   virtual public map < TYPE, ARG_TYPE, ::ca::smart_pointer < T >, const ::ca::smart_pointer < T > & >
{
public:


   map_to_smart_pointer()
   {
   }

   map_to_smart_pointer(::ca::applicationsp papp) :
      ::ca::ca(papp),
      map < TYPE, ARG_TYPE, ::ca::smart_pointer < T >, const ::ca::smart_pointer < T > & >(papp)
   {
   }


   virtual ~map_to_smart_pointer()
   {
   }


} ;

template < class T >
class string_to_smart_pointer :
   virtual public string_map < ::ca::smart_pointer < T >, const ::ca::smart_pointer < T > & >
{
public:


   string_to_smart_pointer()
   {
   }

   string_to_smart_pointer(::ca::applicationsp papp) :
      ::ca::ca(papp),
      string_map < ::ca::smart_pointer < T >, const ::ca::smart_pointer < T > & >(papp)
   {
   }


   virtual ~string_to_smart_pointer()
   {
   }


} ;


#define mapsp(TYPE, ARG_TYPE, SPTYPE) map_to_smart_pointer < TYPE, ARG_TYPE, SPTYPE >
#define strsp(SPTYPE) string_to_smart_pointer < SPTYPE >






