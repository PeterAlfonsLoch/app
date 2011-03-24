#include "StdAfx.h"

menu_frame::menu_frame(::ca::application * papp) :
   ca(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_frame_window(papp),
   form_frame(papp)
{
   m_bLayered        = true;
   m_bCustomFrame    = false;
}
