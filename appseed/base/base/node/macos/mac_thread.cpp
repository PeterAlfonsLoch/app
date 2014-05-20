#include "framework.h"
#include <fcntl.h>






namespace mac
{
   

   
   
   thread::thread(::base::application * papp) :
   element(papp),
   message_queue(papp),//,
   ::thread(NULL),
   thread_impl(papp),
   m_evFinish(papp, FALSE, TRUE)
   {
      m_evFinish.SetEvent();
      m_pThreadParams = NULL;
      m_pfnThreadProc = NULL;
      
      
      CommonConstruct();
      
      
   }
   
   
   
   
   void thread::construct(__THREADPROC pfnThreadProc, LPVOID pParam)
   {
      m_evFinish.SetEvent();
      m_pfnThreadProc = pfnThreadProc;
      m_pThreadParams = pParam;
      
      CommonConstruct();
   }
   
   
   void thread::CommonConstruct()
   {
      m_ptimera      = NULL;
      m_puiptra      = NULL;
      m_puiMain      = NULL;
      m_puiActive    = NULL;
      
      //      m_peventReady  = NULL;
      
      //      m_pmapHDC      = NULL;
      //    m_pmapHGDIOBJ  = NULL;
      
      m_nDisablePumpCount  = 0;
      
      m_bAutoDelete = TRUE;
      m_bRun = false;
      
      //      m_pmapHDC = new hdc_map;
      //    m_pmapHGDIOBJ = new hgdiobj_map;
      //      m_frameList.Construct(offsetof(frame_window, m_pNextFrameWnd));
      m_ptimera = canew(::user::interaction::timer_array(get_app()));
      m_puiptra = canew(::user::interaction_ptr_array(get_app()));
      
      m_hthread = NULL;
      
   }
   
   
   thread::~thread()
   {

     
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
      
      try
      {
         if(MAC_THREAD(pui->m_pthread.m_p) == this)
         {
            pui->m_pthread = NULL;
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pui->m_pimpl != NULL && pui->m_pimpl != pui)
         {
            if(MAC_THREAD(pui->m_pimpl->m_pthread.m_p) == this)
            {
               pui->m_pimpl->m_pthread = NULL;
            }
         }
      }
      catch(...)
      {
      }
      try
      {
         if(pui->m_pui != NULL && pui->m_pui != pui)
         {
            if(MAC_THREAD(pui->m_pui->m_pthread.m_p) == this)
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
      if(m_spuiMessage.is_null())
      {
         return;
      }
      m_ptimera->set(pui, nIDEvent, nEllapse);
      single_lock sl(&m_ptimera->m_mutex, TRUE);
      int32_t iMin = 100;
      for(int32_t i = 0; i < m_ptimera->m_timera.get_count(); i++)
      {
         if(m_ptimera->m_timera.element_at(i)->m_uiElapse < natural(iMin))
         {
            iMin = m_ptimera->m_timera.element_at(i)->m_uiElapse;
         }
      }
      sl.unlock();
      if(m_spuiMessage->IsWindow())
      {
         m_spuiMessage->SetTimer((uint_ptr)-2, iMin, NULL);
      }
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
      return m_bRun;
   }
   
   sp(::user::interaction) thread::get_active_ui()
   {
      return m_puiActive;
   }
   
   sp(::user::interaction) thread::set_active_ui(sp(::user::interaction) pui)
   {
      ::user::interaction * puiPrevious = m_puiActive;
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
   
      step_timer();
     
      
      ::base::application * pappThis1 = dynamic_cast < ::base::application * > (this);

      ::base::application * pappThis2 = dynamic_cast < ::base::application * > (m_pimpl.m_p);
      
      m_pimpl->m_dwAlive = m_dwAlive = ::get_tick_count();
      
      if(pappThis1 != NULL)
      {

         pappThis1->m_dwAlive = m_dwAlive;
         
      }
      
      if(pappThis2 != NULL)
      {
      
         pappThis2->m_dwAlive = m_dwAlive;
         
      }
       
       return true;
      
   }
   
   
   
   void thread::Delete()
   {
      
      // delete thread if it is auto-deleting
      if(m_bAutoDelete)
      {
         
         if(m_pappDelete != NULL)
            m_pappDelete.release();
         
         m_evFinish.SetEvent();
         
         m_pimpl.release();
         
      }
      else
      {
         m_hthread = 0;
         
         m_evFinish.SetEvent();
         
      }
      
   }
   
#ifdef DEBUG
   void thread::assert_valid() const
   {
      command_target::assert_valid();
   }
   void thread::dump(dump_context & dumpcontext) const
   {
      command_target::dump(dumpcontext);
   }
#endif
   
   
   bool thread::set_thread_priority(int32_t epriority)
   {

      return ::SetThreadPriority(m_hthread, ::get_scheduling_priority_normal()) != FALSE;
      
   }
   
   
   int32_t thread::get_thread_priority()
   {
      ::GetThreadPriority(m_hthread);
      return ::get_scheduling_priority_normal();
      
   }
   
   
   DWORD thread::ResumeThread()
   {
      //throw not_implemented(get_app());
      ASSERT(m_hthread != NULL);
      return ::ResumeThread(m_hthread);
   }
   DWORD thread::SuspendThread()
   {
      throw not_implemented(get_app());
      //   ASSERT(m_hThread != NULL);
      // return ::SuspendThread(m_hThread);
      
   }
      
   
	unsigned long MillisecondCounter ()
	{
		timeval tv;
		gettimeofday(&tv, 0);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}

   
} // namespace mac




WINBOOL CLASS_DECL_mac AfxInternalPumpMessage();
LRESULT CLASS_DECL_mac AfxInternalProcessWndProcException(::exception::base*, const MESSAGE* pMsg);
void AfxInternalPreTranslateMessage(signal_details * pobj);

void CLASS_DECL_mac __init_thread()
{
   
   
}











void __end_thread(base::application*, unsigned int, bool)

{
   
}


void __term_thread(base::application*, HINSTANCE__*)
{
}

