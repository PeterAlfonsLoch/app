#pragma once

#include "user/user_window_draw_client_tool.h"
#include "multithreading/multithreading.h"
#include "user/user_window_util.h"

#define ca2m_PRODEVIAN_SYNCH (WM_APP + 1985)

namespace user
{
   class buffer;
   class ::user::window_interface;
}

namespace ca
{

   class CLASS_DECL_ca window_draw : 
      virtual public ::radix::object
   {
   public:


      bool              m_bRun;
      bool              m_bDrawCursor;
      bool              m_bProDevianMode;
      ::user::buffer *  m_pbuffer;
      int               m_iFramesPerSecond;
      CEvent            m_eventFree;


      window_draw();

      virtual bool start();
      virtual bool UpdateBuffer();
      virtual bool ScreenOutput();
      virtual bool stop();

      virtual void asynch_redraw();
      virtual void synch_redraw();

      static bool s_bRunning;
   };

   

   typedef smart_pointer < window_draw > window_draw_sp;

} // namespace ca