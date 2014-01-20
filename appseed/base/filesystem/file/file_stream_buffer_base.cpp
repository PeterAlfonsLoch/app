#include "framework.h"


namespace file
{


   stream_buffer_base::stream_buffer_base()
   {
   }



   stream_buffer_base::~stream_buffer_base()
   {
   }

   
   void * stream_buffer_base::get_internal_data()
   {

      return NULL;

   }

   ::primitive::memory_size stream_buffer_base::get_internal_data_size()
   {

      return 0;

   }


   bool stream_buffer_base::set_internal_data_size(::primitive::memory_size c)
   {

      return false;
      
   }

   bool stream_buffer_base::increase_internal_data_size(::primitive::memory_size c)
   {

      return set_internal_data_size(c + get_internal_data_size());
      
   }


} // namespace file



