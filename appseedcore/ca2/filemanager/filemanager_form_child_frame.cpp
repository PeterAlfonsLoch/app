#include "StdAfx.h"

file_manager_form_child_frame::file_manager_form_child_frame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_child_frame(papp),
   form_child_frame(papp)
{
}