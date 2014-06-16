#include "framework.h"


namespace multithreading
{


   CLASS_DECL_BASE comparable_array < HTHREAD > * s_phaThread = NULL;
   CLASS_DECL_BASE comparable_array < thread * > * s_pthreadptra = NULL;
   CLASS_DECL_BASE mutex * s_pmutex = NULL;


   CLASS_DECL_BASE void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_phaThread = new comparable_array < HTHREAD >;
      s_pthreadptra = new comparable_array < thread * >;
      
      __node_init_multithreading();
      
   }


   CLASS_DECL_BASE void term_multithreading()
   {
      
      __node_term_multithreading();

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_phaThread;
      s_phaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }

   CLASS_DECL_BASE void __node_on_init_thread(HTHREAD hthread,thread * pthread)
   {

      synch_lock sl(s_pmutex);

      ::set_thread(pthread);

      __init_thread();
      
      s_phaThread->add(hthread);

      s_pthreadptra->add(pthread);

      __inc_threading_count();
      
   }


   CLASS_DECL_BASE void __node_on_term_thread(HTHREAD hthread,thread * pthread,int nExitCode,bool bDelete)
   {

      synch_lock sl(s_pmutex);

      __dec_threading_count();
      
      s_phaThread->remove(hthread);

      s_pthreadptra->remove(pthread);

      __term_thread();

      if(pthread != NULL)
      {

         __end_thread(pthread->m_pbaseapp,(UINT)nExitCode,bDelete);

      }


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

}




::base::application * get_thread_app()
{

   thread * pthread = get_thread();

   if(pthread == NULL)
      return NULL;

   return pthread->get_app();

}

