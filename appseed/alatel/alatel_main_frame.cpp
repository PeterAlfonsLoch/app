#include "StdAfx.h"


namespace alatel
{


   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {

      m_dataid = "ca2.alatel.main_frame";

      WfiEnableFullScreen();

   }

   main_frame::~main_frame()
   {
   }


#ifdef _DEBUG
   void main_frame::assert_valid() const
   {
	   simple_frame_window::assert_valid();
   }

   void main_frame::dump(dump_context& dc) const
   {
	   simple_frame_window::dump(dc);
   }
#endif //_DEBUG


   
} // namespace alatel