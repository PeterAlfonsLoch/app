//#include "framework.h"


namespace file_watcher
{

   listener_thread::listener_thread(::aura::application * papp) :
      ::object(papp),
      ::file_watcher::file_watcher(papp)
   {


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
      post_object(WM_USER + 123, 0, pop);

      pop->m_event.wait();

      id id  = pop->m_id;

      delete pop;

      return id;

   }


} // namespace file_watcher




