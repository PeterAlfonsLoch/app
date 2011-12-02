#include "StdAfx.h"

html_child_frame::html_child_frame(::ax::application * papp) :
   ax(papp),
   window_frame::WorkSetClientInterface(papp),
   userbase::frame_window_interface(papp),
   userbase::frame_window(papp),
   simple_child_frame(papp), 
   m_toolbar(papp)
{
}

html_child_frame::~html_child_frame()
{
}

