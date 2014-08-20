#include "framework.h"


simple_main_frame::simple_main_frame(sp(::axis::application) papp) :
   element(papp),
   simple_frame_window(papp)
{

   m_bAutoWindowFrame   = false;
   m_bWindowFrame       = true;

}

simple_main_frame::~simple_main_frame()
{
}

