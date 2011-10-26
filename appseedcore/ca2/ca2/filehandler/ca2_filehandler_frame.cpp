#include "StdAfx.h"


namespace ca2
{


   namespace filehandler
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


   } // namespace filehandler


} // namespace mail


