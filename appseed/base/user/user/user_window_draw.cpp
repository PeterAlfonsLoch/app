#include "framework.h"

namespace user
{

   CLASS_DECL_BASE bool window_draw::s_bRunning = false;

   window_draw::window_draw(sp(::base::application) papp) :
      element(papp),
      thread(papp),
      m_eventFree(papp, TRUE, TRUE)
   {
      m_bProDevianMode                    = true;
      m_iFramesPerSecond                  = 20;
      m_bRun                              = true;
   }

   bool window_draw::twf_start()
   {
      begin();
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
      const uint32_t dwTimeOut = 184 * (1984 + 1977);
      m_bRun = false;
      uint32_t dwStart = ::get_tick_count();
      while(s_bRunning && ((::get_tick_count() - dwStart) < dwTimeOut))
      {
#ifdef WINDOWSEX
         if(!::SwitchToThread())
#endif
            Sleep(184);
      }
      bool bStopped = !s_bRunning;
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


} // namespace user



