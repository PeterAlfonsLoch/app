#include "StdAfx.h"

SimpleFormListEdit::SimpleFormListEdit(::ca::application * papp) :
    ca(papp),
   data_container(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp),
   ::userbase::edit_plain_text(papp),
   ex1::tree(papp),
   ::ca::data_listener(papp)
{
}

SimpleFormListEdit::~SimpleFormListEdit()
{
}

BOOL SimpleFormListEdit::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;   
}

int SimpleFormListEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
// trans   if (::user::interaction::OnCreate(lpCreateStruct) == -1)
      //return -1;


   ::user::interaction * pwndParent = ::user::interaction::GetParent();
   if(base < simple_form_list_view >::bases(pwndParent))
   {

      simple_form_list_view * pview = dynamic_cast < simple_form_list_view * > (pwndParent);
      m_plistinterface = pview;
   }
//   ::user::list * plist = GetBaseListInterface();

   
   return 0;
}

::user::list * SimpleFormListEdit::GetBaseListInterface()
{
   return m_plistinterface;
}

void SimpleFormListEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   UNREFERENCED_PARAMETER(nRepCnt);
   user::control_event key;

// trans   key.m_hwnd     = GetSafeHwnd();
   key.m_eevent   = ::user::event_key_down;
   key.m_puie      = this;
   key.m_uiVKey   = nChar;
   key.m_uiFlags  = nFlags;

   // trans user::ENotifyRetMask eretmask = key.Send(GetNotifyWnd());

// trans   if(key.m_bDefault)
   {
// trans      ::user::interaction::OnKeyDown(nChar, nRepCnt, nFlags);
   }
}

::user::interaction * SimpleFormListEdit::GetNotifyWnd()
{
   ::user::interaction * pwnd = GetOwner();
   if(pwnd != NULL)
      return pwnd;
   return ::user::interaction::GetParent();
}

void SimpleFormListEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(nRepCnt);
   if(nChar == VK_RETURN)
   {
      return;
   }
// trans   ::user::interaction::OnChar(nChar, nRepCnt, nFlags);
}

int SimpleFormListEdit::OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message) 
{
   UNREFERENCED_PARAMETER(pDesktopWnd);
   UNREFERENCED_PARAMETER(nHitTest);
   UNREFERENCED_PARAMETER(message);
   return MA_NOACTIVATE;   
   //return ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
