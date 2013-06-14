#pragma once


namespace file_watcher
{


   class CLASS_DECL_c listener_thread :
      public thread,
      public file_watch_listener
   {
   public:

     

      struct op
      {

         vsstring m_str;
         bool m_bRecursive;
         file_watch_listener * m_plistener;
         simple_event m_event;
         id m_id;

         op() : m_event(false, true) {}

      };


      id add_file_watch(const char * directory, bool bRecursive);

         
   };


} // namespace file_watcher



