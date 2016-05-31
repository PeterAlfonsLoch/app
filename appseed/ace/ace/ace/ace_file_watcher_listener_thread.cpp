//#include "framework.h"


namespace file_watcher
{

   bool listener_thread::file_watcher_initialize_listener_thread(::ace::application * papp)
   {

      if(!file_watcher_initialize_thread(papp))
         return false;

      return true;

   }

   id listener_thread::add_file_watch(const char * directory, bool bRecursive)
   {
      
      return add_file_watch(directory, this, bRecursive);

   }

   id listener_thread::add_file_watch(const char * directory, file_watch_listener * plistener, bool bRecursive, bool bOwn)
   {

      if(get_os_data() == NULL)
      {

         begin();

      }

      op * pop = new op;

      pop->m_str = directory;
      pop->m_bRecursive = bRecursive;
      pop->m_plistener = plistener;
      pop->m_bOwn = bOwn;

//      uint32_t uiId = m_nId;

      //while(m_bUpdating)
    //  {
  //       Sleep(100);
//      }
      LPARAM lparam = (LPARAM)(int_ptr)(void *)(listener_thread::op *)pop;
      post_thread_message(WM_USER + 123, 0, lparam);

      pop->m_event.wait();

      id id  = pop->m_id;

      delete pop;

      return id;

   }


} // namespace file_watcher




