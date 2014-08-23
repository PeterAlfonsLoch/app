#pragma once


namespace file_watcher
{


   class CLASS_DECL_AURA listener_thread :
      public thread,
      public file_watch_listener
   {
   public:

     

      struct op
      {

         string m_str;
         bool m_bRecursive;
         file_watch_listener * m_plistener;
         event m_event;
         id m_id;

         op() : m_event(get_thread_app(), false, true) {}

      };


      id add_file_watch(const char * directory, bool bRecursive);

         
   };


} // namespace file_watcher



