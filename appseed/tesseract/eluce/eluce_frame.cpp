#include "StdAfx.h"

namespace eluce 
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
      m_iFrameData = 10;
      m_dataid = "MusicalPlayerscreencaptureFrame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";

      m_bblur_Background = true;
      m_bLayered = true;
      m_etranslucency = TranslucencyPresent;

   }

   frame::~frame()
   {
   }

   /////////////////////////////////////////////////////////////////////////////
   // frame diagnostics

   #ifdef _DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG


   void frame::install_message_handling(::user::win::message::dispatch * pinterface)
   {
      simple_frame_window::install_message_handling(pinterface);
      USER_MESSAGE_LINK(message_create, pinterface, this, &frame::_001OnCreate);
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {

      pobj->previous();
      if(pobj->m_bRet)
         return;

      LoadToolBar(0, "eluce/frame/toolbar.xml", TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

      LoadToolBar(1, "eluce/frame/center_toolbar.xml", TBSTYLE_ALIGN_CENTER, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_BOTTOM);

      
   }


} // namespace eluce 