//#include "framework.h"


namespace file_watcher
{

   bool listener_thread::file_watcher_initialize_listener_thread(::aura::application * papp)
   {

      if(!file_watcher_initialize_thread(papp))
         return false;

      return true;

   }


   id listener_thread::add_file_watch(const char * directory, bool bRecursive)
   {

      if(get_os_data() == NULL)
      {

         begin();

      }

      op * pop = new op;

      pop->m_str = directory;
      pop->m_bRecursive = bRecursive;
      pop->m_plistener = this;

//      uint32_t uiId = m_nId;

      while(!m_bUpdating)
      {
         Sleep(100);
      }

      post_thread_message(WM_USER + 123, 0, (lparam) pop);

      pop->m_event.wait();
      
      id id  = pop->m_id;

      delete pop;

      return id;

   }


} // namespace file_watcher




