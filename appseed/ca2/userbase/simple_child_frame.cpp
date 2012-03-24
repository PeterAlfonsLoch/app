#include "StdAfx.h"


simple_child_frame::simple_child_frame(::ca::application * papp) :
   ca(papp),
   simple_frame_window(papp)
{
   m_etranslucency = TranslucencyTotal;
   m_bCustomFrame = false;
}

simple_child_frame::~simple_child_frame()
{
}


BOOL simple_child_frame::PreCreateWindow(CREATESTRUCT& cs) 
{
   cs.style |= WS_CHILD;
   cs.style |= WS_CLIPCHILDREN;
   cs.style &= ~WS_BORDER;
   cs.style &= ~WS_THICKFRAME;

   if(!simple_frame_window::PreCreateWindow(cs))
      return FALSE;

   if(cs.hwndParent == NULL)
   {
      if(System.m_pwndMain != NULL)
      {
         cs.hwndParent = System.m_pwndMain->_get_handle();
      }
   }

   cs.style &= ~WS_OVERLAPPEDWINDOW;
   return TRUE;
}

bool simple_child_frame::_001OnCmdMsg(BaseCmdMsg * pcmdmsg)  
{

   if(simple_frame_window::_001OnCmdMsg(pcmdmsg))
      return TRUE;

   return FALSE;

}



