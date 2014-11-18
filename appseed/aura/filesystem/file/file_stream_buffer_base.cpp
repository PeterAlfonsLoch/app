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


   const void * stream_buffer_base::get_internal_data() const
   {

      return ((stream_buffer_base *) this)->get_internal_data();

   }

   ::primitive::memory_size stream_buffer_base::get_internal_data_size() const
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



