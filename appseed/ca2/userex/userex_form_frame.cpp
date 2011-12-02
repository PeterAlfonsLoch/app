#include "StdAfx.h"


form_frame::form_frame(::ax::application * papp) :
   ax(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp)
{
}