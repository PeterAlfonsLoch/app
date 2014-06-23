#include "framework.h"


namespace user
{


   window_draw::window_draw(sp(::base::application) papp) :
      element(papp),
      thread(papp),
      m_eventFree(papp, TRUE, TRUE)
   {
      m_bProDevianMode                    = true;
      m_iFramesPerSecond                  = 20;
      m_bRunning                          = false;
      m_bRun                              = true;
   }


   bool window_draw::twf_start()
   {

      int iReturnCode;

      if(begin_synch(&iReturnCode))
         return false;

      return true;

   }


   bool window_draw::UpdateBuffer()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::ScreenOutput()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::twf_stop()
   {
      const uint32_t dwTimeOut = 184 * (5000);
      m_bRun = false;
      uint32_t dwStart = ::get_tick_count();
      while(m_bRunning && ((::get_tick_count() - dwStart) < dwTimeOut))
      {
#ifdef WINDOWSEX
         if(!::SwitchToThread())
#endif
            Sleep(184);
      }
      bool bStopped = !m_bRunning;
      if(!bStopped)
      {
         TRACE("Failed to stop with the timeout %d milliseconds", dwTimeOut);
      }
      Sleep(584);
      return bStopped;
   }

   void window_draw::asynch_redraw()
   {
      throw interface_only_exception(get_app());
   }

   void window_draw::synch_redraw()
   {
      throw interface_only_exception(get_app());
   }


   ::user::interaction_ptr_array window_draw::get_wnda()
   {

      return System.frames();

   }


} // namespace user



