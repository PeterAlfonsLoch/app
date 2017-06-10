#include "framework.h"


namespace multithreading
{


   CLASS_DECL_AURA comparable_eq_array<IDTHREAD> * s_piaThread = NULL;
   CLASS_DECL_AURA ref_array < thread > * s_pthreadptra = NULL;
   CLASS_DECL_AURA mutex * s_pmutex = NULL;


   CLASS_DECL_AURA void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_piaThread = new comparable_eq_array<IDTHREAD>;
      s_pthreadptra = new ref_array < thread >;

      __node_init_multithreading();

   }


   CLASS_DECL_AURA void term_multithreading()
   {

      __node_term_multithreading();

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_piaThread;
      s_piaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }

   CLASS_DECL_AURA void __node_on_init_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      ::set_thread(pthread);

      processor_cache_oriented_set_thread_memory_pool(0); // set default processor cache oriented thread memory pool index to 0 ("zero") (The First One)

      __init_thread();

      s_piaThread->add(pthread->get_os_int());

      s_pthreadptra->add(pthread);

   }


   CLASS_DECL_AURA void __node_on_term_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      s_piaThread->remove(pthread->get_os_int());

      s_pthreadptra->remove(pthread);

      __term_thread();

   }


   CLASS_DECL_AURA uint32_t __on_thread_finally(thread * pthread)
   {

      //try
      //{

      //   single_lock sl(&pthread->m_mutexUiPtra, TRUE);

      //   if (pthread->m_spuiptra.is_set())
      //   {

      //      while (pthread->m_spuiptra->has_elements())
      //      {

      //         pthread->remove(pthread->m_spuiptra->element_at(0));

      //      }

      //      pthread->m_spuiptra.release();

      //   }

      //}
      //catch (...)
      //{

      //}

      int nExitCode = -1;

      try
      {

         try
         {

            pthread->unregister_from_required_threads();

         }
         catch(...)
         {


         }


         __node_term_thread(pthread);

         ::multithreading::__node_on_term_thread(pthread);

         ::aura::application * papp = pthread->get_app();

         nExitCode = pthread->m_iReturnCode;

         try
         {

            pthread->m_signala.remove_all();

         }
         catch(...)
         {

         }

         try
         {

            pthread->m_signala.remove_all();

         }
         catch(...)
         {

         }

         try
         {

            pthread->thread_term();

         }
         catch(...)
         {

         }


         __end_thread(papp);

         try
         {

//            if(pthread->m_bAutoDelete)
  //          {

      //         ::aura::del(pthread);
                  

    //        }

            ::release(pthread);

         }
         catch(...)
         {

         }

      }
      catch(...)
      {

      }

      set_thread_off(::GetCurrentThreadId());

      return nExitCode;

   }


} // namespace multithreading




thread_pointer < ::thread > t_pthread;




::thread * get_thread()
{

   return t_pthread;

}

bool get_thread_run()
{
   
   if(t_pthread == NULL) // system threads don't have generally associated ca2 thread object
   {
      // and have short life, so it is safe to keep it running
      return true;
      
   }
   
   try
   {

      return t_pthread->get_run_thread();

   }
   catch (...)
   {

   }

   return false;

}

namespace multithreading
{

   CLASS_DECL_AURA bool post_quit()
   {

      return post_quit(t_pthread);

   }


   CLASS_DECL_AURA bool post_quit_and_wait(const duration & duration)
   {

      return post_quit_and_wait(t_pthread, duration);

   }


   CLASS_DECL_AURA bool post_quit(::thread * pthread)
   {

      return post_quit<::thread>(pthread);

   }


   CLASS_DECL_AURA bool post_quit_and_wait(::thread * pthread, const duration & duration)
   {

      return post_quit_and_wait<::thread>(pthread, duration);

   }


} // namespace multithreading



void set_thread(::thread* pthread)
{

   t_pthread = pthread;

}





thread* __begin_thread(::aura::application * papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority,UINT nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs, IDTHREAD * puiId)
{

   ASSERT(pfnThreadProc != NULL);

   thread* pThread = canew(thread(papp,pfnThreadProc,pParam));

   ASSERT_VALID(pThread);

   if(!pThread->create_thread(epriority,nStackSize, dwCreateFlags,lpSecurityAttrs, puiId))
   {

      pThread->Delete();

      return NULL;

   }

   return pThread;

}







//mutex & user_mutex()
//{
//
//   //static mutex * s_pmutexUser = new mutex();
//
//   //return *s_pmutexUser;
//   return *((mutex *)NULL);
//
//}

mutex * s_pmutexMessageDispatch = NULL;

mutex & message_dispatch_mutex()
{


   return *s_pmutexMessageDispatch;

}



::aura::application * get_thread_app()
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


