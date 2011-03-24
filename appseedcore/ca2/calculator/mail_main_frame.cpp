#include "StdAfx.h"

namespace mail
{

   main_frame::main_frame(::ca::application * papp) :
      ::ca::ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
      m_dataid = "MusicalPlayerscreencaptureFrame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
   }

   main_frame::~main_frame()
   {
   }


   /////////////////////////////////////////////////////////////////////////////
   // main_frame diagnostics

   #ifdef _DEBUG
   void main_frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //_DEBUG

} //namespace mail