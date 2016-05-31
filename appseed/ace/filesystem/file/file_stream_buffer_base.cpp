//#include "framework.h"


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

   memory_size_t stream_buffer_base::get_internal_data_size() const
   {

      return 0;

   }


   bool stream_buffer_base::set_internal_data_size(memory_size_t c)
   {

      return false;
      
   }

   bool stream_buffer_base::increase_internal_data_size(memory_size_t c)
   {

      return set_internal_data_size(c + get_internal_data_size());
      
   }


} // namespace file



