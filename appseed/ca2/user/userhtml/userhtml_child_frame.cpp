#include "framework.h"


html_child_frame::html_child_frame(sp(::ca2::application) papp) :
   ca2(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
}


html_child_frame::~html_child_frame()
{
}

