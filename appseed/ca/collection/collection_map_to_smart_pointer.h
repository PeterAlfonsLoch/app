#pragma once


namespace collection
{


   template < class TYPE, class ARG_TYPE, class T >
   class map_to_smart_pointer :
      virtual public ::collection::map < TYPE, ARG_TYPE, ::ca::smart_pointer < T >, const ::ca::smart_pointer < T > & >
   {
   public:

      map_to_smart_pointer()
      {
      }

      map_to_smart_pointer(::ca::application * papp) :
         ca(papp),
         map_to_smart_pointer < TYPE, ARG_TYPE, ::ca::smart_pointer < T > >(papp)
      {
      }


      virtual ~map_to_smart_pointer()
      {
      }


   } ;


} // namespace collection


#define mapsp(TYPE, ARG_TYPE, SPTYPE) ::collection::map_to_smart_pointer < TYPE, ARG_TYPE, SPTYPE >






