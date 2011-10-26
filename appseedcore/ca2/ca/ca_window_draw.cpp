#include "StdAfx.h"

namespace ca
{

   bool window_draw::s_bRunning = false;

   window_draw::window_draw() :
      m_eventFree(TRUE, TRUE)
   {
      m_bProDevianMode           = true;
      m_iFramesPerSecond         = 40;
      m_bRun                     = true;
   }

   bool window_draw::start()
   {
      throw interface_only_exception();
   }

   bool window_draw::UpdateBuffer()
   {
      throw interface_only_exception();
   }

   bool window_draw::ScreenOutput()
   {
      throw interface_only_exception();
   }

   bool window_draw::stop()
   {
      const DWORD dwTimeOut = 184 * (1984 + 1977);
      m_bRun = false;
      DWORD dwStart = ::GetTickCount();
      while(s_bRunning && ((::GetTickCount() - dwStart) < dwTimeOut))
      {
         if(!::SwitchToThread())
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
      throw interface_only_exception();
   }

   void window_draw::synch_redraw()
   {
      throw interface_only_exception();
   }


} // namespace ca



