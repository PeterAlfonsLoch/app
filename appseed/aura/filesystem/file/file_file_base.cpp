//#include "framework.h"


namespace file
{


   file_base::file_base()
   {
   }



   file_base::~file_base()
   {
   }

   
   void * file_base::get_internal_data()
   {

      return NULL;

   }


   const void * file_base::get_internal_data() const
   {

      return ((file_base *) this)->get_internal_data();

   }

   memory_size_t file_base::get_internal_data_size() const
   {

      return 0;

   }


   bool file_base::set_internal_data_size(memory_size_t c)
   {

      return false;
      
   }

   bool file_base::increase_internal_data_size(memory_size_t c)
   {

      return set_internal_data_size(c + get_internal_data_size());
      
   }


} // namespace file



