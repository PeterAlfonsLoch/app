#include "framework.h"


namespace file_watcher
{

   listener_thread::listener_thread(::aura::application * papp) :
      ::object(papp),
      ::file_watcher::file_watcher(papp)
   {


   }


   listener_thread::~listener_thread()
   {

      for (auto & plistener : m_listenerptra)
      {

         if (plistener->m_pfilewatcherlistenerthread == plistener)
         {

            plistener->m_pfilewatcherlistenerthread = NULL;

         }

      }

   }


   file_watch_id listener_thread::add_file_watch(const char * directory, bool bRecursive)
   {
      
      return add_file_watch(directory, this, bRecursive);

   }


   file_watch_id listener_thread::add_file_watch(const char * directory, file_watch_listener * plistener, bool bRecursive, bool bOwn)
   {

#if defined(METROWIN) || defined(MACOS)

      return file_watcher::add_watch(directory, plistener, bRecursive, bOwn);

#else

      if(get_os_data() == NULL)
      {

         begin();

      }

      add * padd = new add;

      padd->m_str = directory;
      padd->m_plistener = plistener;
      padd->m_id = -1;
      padd->m_bOwn = bOwn;
      padd->m_bRecursive = bRecursive;

      file_watch_id id = padd->m_id;

      padd->m_event.ResetEvent();

      post_object(message_add_watch, 0, padd);

      padd->m_event.wait();

      if (id >= 0)
      {

         m_listenerptra.add_unique(plistener);

      }

      return id;

#endif

   }


} // namespace file_watcher




