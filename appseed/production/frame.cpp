#include "StdAfx.h"
#include "window_frame/FrameSchemaHardCoded002.h"
#include "window_frame/FrameSchemaHardCoded005.h"

namespace production
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
      m_dataid = "ca2::production::frame";
   }

   frame::~frame()
   {
   }


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
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &frame::_001OnCreate);
   }

   void frame::_001OnCreate(gen::signal_object * pobj)
   {
      pobj->previous();
//      application * papp = dynamic_cast < application * > (get_app());

      window_frame::FrameSchemaHardCoded005 * pschema = dynamic_cast < window_frame::FrameSchemaHardCoded005 * > (m_workset.m_pframeschema);
      if(pschema != NULL)
      {
         pschema->SetStyle(window_frame::FrameSchemaHardCoded005::StyleBlueRedPurple);
      }
   }

} // namespace production