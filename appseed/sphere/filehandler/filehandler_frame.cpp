#include "framework.h"


namespace filehandler
{


   frame::frame(sp(::base::application) papp) :
      element(papp),
      simple_frame_window(papp)
   {
      m_iFrameData = 10;
      m_dataid = "MusicalPlayerscreencaptureFrame";

      WfiEnableFullScreen();

      m_dataidWindow = "WindowData";
        

      select_layered_frame();


   }

   frame::~frame()
   {
   }

   /////////////////////////////////////////////////////////////////////////////
   // frame diagnostics

   #ifdef DEBUG
   void frame::assert_valid() const
   {
      simple_frame_window::assert_valid();
   }

   void frame::dump(dump_context & dumpcontext) const
   {
      simple_frame_window::dump(dumpcontext);
   }


   #endif //DEBUG


} // namespace filehandler




