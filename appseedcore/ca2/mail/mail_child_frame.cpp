#include "StdAfx.h"

namespace mail
{

   child_frame::child_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_child_frame(papp)
   {
      m_dataid = "MusicalPlayerscreencaptureFrame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
   }

   child_frame::~child_frame()
   {
   }


   /////////////////////////////////////////////////////////////////////////////
   // child_frame diagnostics

   #ifdef _DEBUG
   void child_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void child_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG

} // namespace mail