#include "framework.h"


html_child_frame::html_child_frame(sp(::axis::application) papp) :
   element(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
}


html_child_frame::~html_child_frame()
{
}

