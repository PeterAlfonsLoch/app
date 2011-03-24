#include "StdAfx.h"

namespace backup
{

   frame::frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      production::frame(papp)
   {
      m_iFrameData = 10;

      m_dataid = "ca2::backup::frame";
      
   }

   frame::~frame()
   {
   }

} // namespace backup