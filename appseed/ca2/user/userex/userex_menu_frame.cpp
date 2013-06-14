#include "framework.h"


menu_frame::menu_frame(sp(::ca2::application) papp) :
   ca2(papp),
   simple_frame_window(papp),
   form_frame(papp)
{
   m_bLayered        = true;
   m_bWindowFrame    = false;
}
