#pragma once


template < class TYPE, class ARG_TYPE, class T >
class map_to_smart_pointer :
   virtual public map < TYPE, ARG_TYPE, smart_pointer < T >, const smart_pointer < T > & >
{
public:


   map_to_smart_pointer(sp(::axis::application) papp = NULL, ::count nBlockSize = 10) :
      element(papp),
      map < TYPE, ARG_TYPE, smart_pointer < T >, const smart_pointer < T > & > (papp, nBlockSize)
   {
   }



   virtual ~map_to_smart_pointer()
   {
   }


} ;

template < class T >
class string_to_smart_pointer :
   virtual public string_map < smart_pointer < T >, const smart_pointer < T > & >
{
public:


   string_to_smart_pointer(sp(::axis::application) papp = NULL, ::count nBlockSize = 10) :
      element(papp),
      string_map < smart_pointer < T >, const smart_pointer < T > & > (papp, nBlockSize)
   {

   }


   virtual ~string_to_smart_pointer()
   {
   }


} ;


#define mapsp(TYPE, ARG_TYPE, SPTYPE) map_to_smart_pointer < TYPE, ARG_TYPE, SPTYPE >
#define strsp(SPTYPE) string_to_smart_pointer < SPTYPE >






