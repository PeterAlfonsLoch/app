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

      synch_lock sl(m_pmutex);

#ifndef METROWIN

      if(get_os_data() == NULL)
      {

         begin();

      }

#endif

      file_watch_id id = file_watcher::add_watch(directory, plistener, bRecursive, bOwn);

      m_listenerptra.add_unique(plistener);

      return id;

   }


} // namespace file_watcher




