#include "framework.h"
#include <fcntl.h>





namespace linux
{


   thread::thread(sp(::base::application) papp) :
      element(papp),
      message_queue(papp),
      ::thread(NULL),
      ::thread_impl(papp)
   {

      m_evFinish.SetEvent();

      m_pThreadParams = NULL;
      m_pfnThreadProc = NULL;

      CommonConstruct();

   }

   void thread::CommonConstruct()
   {
      m_ptimera      = NULL;
      m_puiptra      = NULL;


      m_nDisablePumpCount  = 0;

      m_bAutoDelete = TRUE;
      m_bRun = false;

      m_ptimera = new ::user::interaction::timer_array(get_app());
      m_puiptra = new user::interaction_ptr_array(get_app());

      m_hthread = NULL;

   }


   void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {

      m_evFinish.SetEvent();

      m_pfnThreadProc = pfnThreadProc;
      m_pThreadParams = pParam;

      CommonConstruct();
   }


   thread::~thread()
   {


      if(m_puiptra != NULL)
      {
         single_lock sl(&m_mutexUiPtra, TRUE);
         ::user::interaction_ptr_array * puiptra = m_puiptra;
         m_puiptra = NULL;
         for(int32_t i = 0; i < puiptra->get_size(); i++)
         {
            sp(::user::interaction) pui = puiptra->element_at(i);
            if(pui->m_pthread != NULL)
            {
#ifndef DEBUG
               try
               {
#endif
                  if(LNX_THREAD(pui->m_pthread.m_p) == this || pui->m_pthread->m_pimpl.m_p == this)
                  {
                     pui->m_pthread = NULL;
                  }
#ifndef DEBUG
               }
               catch(...)
               {
               }
#endif
            }
         }
         sl.unlock();
      }

   }

   int thread::get_x_window_count() const
   {

         if(m_puiptra == NULL)
            return 0;

            return m_puiptra->get_count();
   }

   void thread::add(sp(::user::interaction) pui)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      m_puiptra->add(pui);
   }

   void thread::remove(::user::interaction * pui)
   {
      if(pui == NULL)
         return;
      single_lock sl(&m_mutexUiPtra, TRUE);
      if(m_puiptra != NULL)
      {
         m_puiptra->remove(pui);
         m_puiptra->remove(pui->m_pui);
         m_puiptra->remove(pui->m_pimpl);
      }
      sl.unlock();
      if(m_ptimera != NULL)
      {
         m_ptimera->unset(pui);
         m_ptimera->unset(pui->m_pui);
         m_ptimera->unset(pui->m_pimpl);
      }

#ifndef DEBUG
      try
      {
#endif
         if(LNX_THREAD(pui->m_pthread.m_p) == this)
         {
            pui->m_pthread = NULL;
         }
#ifndef DEBUG
      }
      catch(...)
      {
      }
#endif

#ifndef DEBUG
      try
      {
#endif
         if(pui->m_pimpl != NULL && pui->m_pimpl != pui)
         {
            if(LNX_THREAD(pui->m_pimpl->m_pthread.m_p) == this)
            {
               pui->m_pimpl->m_pthread = NULL;
            }
         }
#ifndef DEBUG
      }
      catch(...)
      {
      }
#endif
      try
      {
         if(pui->m_pui != NULL && pui->m_pui != pui)
         {
            if(LNX_THREAD(pui->m_pui->m_pthread.m_p) == this)
            {
               pui->m_pui->m_pthread = NULL;
            }
         }
      }
      catch(...)
      {
      }
   }

   ::count thread::get_ui_count()
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      return m_puiptra->get_count();
   }

   sp(::user::interaction) thread::get_ui(int32_t iIndex)
   {
      single_lock sl(&m_mutexUiPtra, TRUE);
      return m_puiptra->element_at(iIndex);
   }

   void thread::set_timer(sp(::user::interaction) pui, uint_ptr nIDEvent, UINT nEllapse)
   {
      m_ptimera->set(pui, nIDEvent, nEllapse);
   }

   void thread::unset_timer(sp(::user::interaction) pui, uint_ptr nIDEvent)
   {
      m_ptimera->unset(pui, nIDEvent);
   }

   void thread::set_auto_delete(bool bAutoDelete)
   {
      m_bAutoDelete = bAutoDelete;
   }

   void thread::set_run(bool bRun)
   {
      m_bRun = bRun;
   }

   event & thread::get_finish_event()
   {
      return m_evFinish;
   }

   bool thread::get_run()
   {
      return m_bRun && ::os_thread::get_run();
   }

   sp(::user::interaction) thread::get_active_ui()
   {
      return m_puiActive;
   }

   sp(::user::interaction) thread::set_active_ui(sp(::user::interaction) pui)
   {
      sp(::user::interaction) puiPrevious = m_puiActive;
      m_puiActive = pui;
      return puiPrevious;
   }

   void thread::step_timer()
   {
      if(m_ptimera == NULL)
         return;
      m_ptimera->check();
   }


   bool thread::on_run_step()
   {
      sp(::base::application) pappThis1 =  (this);
      sp(::base::application) pappThis2 =  (m_puser.m_p);


            m_puser->m_dwAlive = m_dwAlive = ::get_tick_count();
            if(pappThis1 != NULL)
            {
               pappThis1->m_dwAlive = m_dwAlive;
            }
            if(pappThis2 != NULL)
            {
               pappThis2->m_dwAlive = m_dwAlive;
            }
      step_timer();


   }




void thread::Delete()
{

   // delete thread if it is auto-deleting
   if(m_bAutoDelete)
   {
      if(m_pappDelete != NULL)
         m_pappDelete.release();
      m_evFinish.SetEvent();
//      ::thread * pthread = dynamic_cast < ::thread * > (m_p.m_p);
//      if(pthread->m_peventReady != NULL)
  //    {
    //     ::SetEvent((HANDLE) pthread->m_peventReady);
     // }
//      if(m_peventReady != NULL)
  //    {
    //     ::SetEvent((HANDLE) m_peventReady);
      //}
      //pthread->::ca2::smart_pointer < ::thread >::m_p = NULL;
//      m_p.release();
//      delete_this();
        ::root::release();

   }
   else
   {
      m_hthread = 0;
      m_evFinish.SetEvent();
   }
}




   void thread::defer_process_windows_messages()
   {

      XEvent e;

      bool b;

      Window root;
      Window child;
      int root_x;
      int root_y;
      int win_x;
      int win_y;
      unsigned int mask;


      bool bContinue;


   }


} // namespace linux







void __node_init_app_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

}






