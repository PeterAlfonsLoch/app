#include "framework.h"


menu_frame::menu_frame(::ca::application * papp) :
   ca(papp),
   simple_frame_window(papp),
   form_frame(papp)
{
   m_bLayered        = true;
   m_bWindowFrame    = false;
}
