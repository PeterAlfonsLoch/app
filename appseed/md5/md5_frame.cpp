#include "StdAfx.h"


namespace md5
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {

      m_dataid = "ca2.md5.frame";


      WfiEnableFullScreen();


   }

   frame::~frame()
   {
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


} // namespace md5