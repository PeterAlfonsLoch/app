#pragma once


#include "user/user_window_util.h"


#define ca2m_PRODEVIAN_SYNCH (WM_APP + 1985)

namespace user
{
   class buffer;
   class window_interface;
}

namespace ca2
{

   class CLASS_DECL_ca2 window_draw :
      virtual public ::ca2::thread
   {
   public:


      bool                 m_bProDevianMode;
      ::user::buffer *     m_pbuffer;
      uint32_t             m_iFramesPerSecond;
      event                m_eventFree;


      window_draw(sp(::application) papp);

      virtual bool UpdateBuffer();
      virtual bool ScreenOutput();

      // legacy name TWF ressurected here - TWF - Transparent Window Interface - The veriwell Musical Player lite translucent windows
      virtual bool twf_start();
      virtual bool twf_stop();

      virtual void asynch_redraw();
      virtual void synch_redraw();

      static bool s_bRunning;
   };



   typedef smart_pointer < window_draw > window_draw_sp;

} // namespace ca2
