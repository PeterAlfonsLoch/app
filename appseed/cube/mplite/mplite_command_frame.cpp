#include "StdAfx.h"

#include "window_frame/FrameSchemaHardCoded008.h"


namespace mplite
{


   command_frame::command_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
   }

   command_frame::~command_frame()
   {
   }

      
#ifdef _DEBUG
   void command_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void command_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }
#endif


   void command_frame::_001InstallMessageHandling(::user::win::message::dispatch * pdispatch)
   {
      simple_frame_window::_001InstallMessageHandling(pdispatch);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pdispatch, this, &command_frame::_001OnClose);
   }

   void command_frame::_001OnClose(gen::signal_object * pobj)
   {
      ShowWindow(SW_HIDE);
      pobj->m_bRet = true;
   }


   window_frame::FrameSchema * command_frame::create_frame_schema()
   {
      window_frame::FrameSchemaHardCoded008 * pschema = new window_frame::FrameSchemaHardCoded008(get_app());
      pschema->m_pruntimeclassControlBoxButton = typeid(MetaButton);
      return pschema;
   }





}