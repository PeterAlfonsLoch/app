#include "StdAfx.h"


namespace alatel
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {

      m_dataid = "ca2.alatel.frame";

      WfiEnableFullScreen();

      m_etranslucency = TranslucencyPresent;

   }

   frame::~frame()
   {
   }


   void frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &::alatel::frame::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_TIMER, pinterface, this, &::alatel::frame::_001OnTimer);
   }

#ifdef _DEBUG
   void frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context& dc) const
   {
	   simple_frame_window::dump(dc);
   }
#endif //_DEBUG


   void frame::_001OnTimer(gen::signal_object * pobj) 
   {
      SCAST_PTR(user::win::message::timer, ptimer, pobj)
      if(ptimer->m_nIDEvent == 4033)
      {
         if(IsWindowVisible())
         {
            WfiFullScreen(true, false);
            SetWindowPos(ZORDER_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
            ModifyStyleEx(0, WS_EX_TRANSPARENT, SWP_SHOWWINDOW);
         }
      }
   }

   void frame::alatel_fullscreen(bool bAlatel)
   {
      if(bAlatel)
      {
         m_etranslucency = TranslucencyPresent;
         SetTimer(4033, 984, 0);
      }
      else
      {
         m_etranslucency = TranslucencyNone;
         KillTimer(4033);
      }
   }

} // namespace alatel