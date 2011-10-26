#include "StdAfx.h"

namespace veriview
{

   main_frame::main_frame(::ca::application * papp) :
      ca(papp),
      window_frame::WorkSetClientInterface(papp),
      userbase::frame_window_interface(papp),
      userbase::frame_window(papp),
      simple_frame_window(papp)
   {
   }

   main_frame::~main_frame()
   {
   }


} // namespace veriview
