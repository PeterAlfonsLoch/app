#include "framework.h"


simple_child_frame::simple_child_frame(sp(::axis::application) papp) :
   element(papp),
   simple_frame_window(papp)
{

   m_bWindowFrame       = false;

}

simple_child_frame::~simple_child_frame()
{
}


bool simple_child_frame::pre_create_window(::user::create_struct& cs) 
{
   
   cs.style |= WS_CHILD;
   cs.style |= WS_CLIPCHILDREN;
   cs.style &= ~WS_BORDER;
   cs.style &= ~WS_THICKFRAME;

   if(!simple_frame_window::pre_create_window(cs))
      return FALSE;

#ifdef WINDOWSEX

   if(cs.hwndParent == NULL)
   {
      if(System.m_pwndMain != NULL)
      {
         cs.hwndParent = System.m_pwndMain->get_handle();
      }
   }

#endif

   cs.style &= ~WS_OVERLAPPEDWINDOW;

   return TRUE;

}

bool simple_child_frame::_001OnCmdMsg(::base::cmd_msg * pcmdmsg)  
{

   if(simple_frame_window::_001OnCmdMsg(pcmdmsg))
      return TRUE;

   return FALSE;

}



bool simple_child_frame::get_translucency(::user::ETranslucency & etranslucency)
{

   etranslucency = ::user::TranslucencyTotal;

   return true;

}