#include "framework.h"


namespace multithreading
{


   CLASS_DECL_AXIS comparable_array < HTHREAD > * s_phaThread = NULL;
   CLASS_DECL_AXIS comparable_array < thread * > * s_pthreadptra = NULL;
   CLASS_DECL_AXIS mutex * s_pmutex = NULL;


   CLASS_DECL_AXIS void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_phaThread = new comparable_array < HTHREAD >;
      s_pthreadptra = new comparable_array < thread * >;

      __node_init_multithreading();

   }


   CLASS_DECL_AXIS void term_multithreading()
   {

      __node_term_multithreading();

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_phaThread;
      s_phaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }

   CLASS_DECL_AXIS void __node_on_init_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      ::set_thread(pthread);

      __init_thread();

      s_phaThread->add((HTHREAD) pthread->m_pthreadimpl->get_os_data());

      s_pthreadptra->add(pthread);

   }


   CLASS_DECL_AXIS void __node_on_term_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      s_phaThread->remove((HTHREAD)pthread->m_pthreadimpl->get_os_data());

      s_pthreadptra->remove(pthread);

      __term_thread();

   }


   CLASS_DECL_AXIS uint32_t __on_thread_finally(thread * pthread)
   {

      __node_term_thread(pthread);

      ::multithreading::__node_on_term_thread(pthread);

      sp(::base::application) papp = pthread->get_app();

      int nExitCode = pthread->m_iReturnCode;

      pthread->m_pthreadimpl->thread_term();

      __end_thread(papp);

      return nExitCode;

   }


} // namespace multithreading




thread_pointer < ::thread > t_pthread;




::thread * get_thread()
{

   return t_pthread;

}



void set_thread(::thread* pthread)
{

   t_pthread = pthread;

}






thread* __begin_thread(sp(::base::application) papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority,UINT nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs)
{

   ASSERT(pfnThreadProc != NULL);

   thread* pThread = new thread(papp,pfnThreadProc,pParam);
   ASSERT_VALID(pThread);

   if(!pThread->create_thread(epriority,nStackSize, dwCreateFlags,lpSecurityAttrs))
   {
      pThread->Delete();
      return NULL;
   }

   return pThread;

}







mutex & user_mutex()
{

   static mutex * s_pmutexUser = new mutex();

   return *s_pmutexUser;
   //return *((mutex *)NULL);

}

mutex & message_dispatch_mutex()
{

   static mutex * s_pmutexMessageDispatch = new mutex();

   return *s_pmutexMessageDispatch;

}



::base::application * get_thread_app()
{

   thread * pthread = get_thread();

   if(pthread == NULL)
      return NULL;

   return pthread->get_app();

}




void do_events()
{

   ::thread * pthread = ::get_thread();

   if(pthread == NULL)
      return;

   pthread->do_events();

}


void do_events(const duration & duration)
{

   ::thread * pthread = ::get_thread();

   if(pthread == NULL)
      return;

   pthread->do_events(duration);

}


