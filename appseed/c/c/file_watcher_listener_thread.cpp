#include "framework.h"


namespace file_watcher
{


   id listener_thread::add_watch(const char * directory)
   {
      
      return thread::add_watch(directory, this);

   }

   id_array listener_thread::radd_watch(const char * directory)
   {
      
      return thread::radd_watch(directory, this);

   }


} // namespace file_watcher




