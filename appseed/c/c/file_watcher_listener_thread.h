#pragma once


namespace file_watcher
{


   class CLASS_DECL_c listener_thread :
      public thread,
      public file_watch_listener
   {
   public:

      
      id add_watch(const char * directory);
      id_array radd_watch(const char * directory);

         
   };


} // namespace file_watcher



