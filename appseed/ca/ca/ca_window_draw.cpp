#include "framework.h"

namespace ca
{

   bool window_draw::s_bRunning = false;

   window_draw::window_draw(::ca::application * papp) :
      ca(papp),
      m_eventFree(papp, TRUE, TRUE)
   {
      m_bProDevianMode           = true;
      m_iFramesPerSecond         = 40;
      m_bRun                     = true;
   }

   bool window_draw::start()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::UpdateBuffer()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::ScreenOutput()
   {
      throw interface_only_exception(get_app());
   }

   bool window_draw::stop()
   {
      const DWORD dwTimeOut = 184 * (1984 + 1977);
      m_bRun = false;
      DWORD dwStart = ::GetTickCount();
      while(s_bRunning && ((::GetTickCount() - dwStart) < dwTimeOut))
      {
#ifdef WINDOWS
         if(!::SwitchToThread())
#endif
            Sleep(184);
      }
      bool bStopped = !s_bRunning;
      if(!bStopped)
      {
         TRACE("Failed to stop with the timeout %d milliseconds", dwTimeOut);
      }
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


} // namespace ca



