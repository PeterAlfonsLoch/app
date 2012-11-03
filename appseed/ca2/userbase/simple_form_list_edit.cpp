#include "framework.h"


simple_form_list_edit::simple_form_list_edit(::ca::application * papp) :
    ca(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::userbase::edit_plain_text(papp)
{
}

simple_form_list_edit::~simple_form_list_edit()
{
}

bool simple_form_list_edit::OnEraseBkgnd(::ca::graphics * pgraphics) 
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;   
}

int simple_form_list_edit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   UNREFERENCED_PARAMETER(lpCreateStruct);
// trans   if (::user::interaction::OnCreate(lpCreateStruct) == -1)
      //return -1;


   ::user::interaction * pwndParent = ::user::interaction::get_parent();
   if(base < simple_form_list_view >::bases(pwndParent))
   {

      simple_form_list_view * pview = dynamic_cast < simple_form_list_view * > (pwndParent);
      m_plistinterface = pview;
   }
//   ::user::list * plist = GetBaseListInterface();

   
   return 0;
}

::user::list * simple_form_list_edit::GetBaseListInterface()
{
   return m_plistinterface;
}

void simple_form_list_edit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   UNREFERENCED_PARAMETER(nRepCnt);
   user::control_event key;

// trans   key.m_oswindow     = GetSafeoswindow_();
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

::user::interaction * simple_form_list_edit::GetNotifyWnd()
{
   ::user::interaction * pwnd = get_owner();
   if(pwnd != NULL)
      return pwnd;
   return ::user::interaction::get_parent();
}

void simple_form_list_edit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(nRepCnt);
   if(nChar == VK_RETURN)
   {
      return;
   }
// trans   ::user::interaction::OnChar(nChar, nRepCnt, nFlags);
}

int simple_form_list_edit::OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message) 
{
   UNREFERENCED_PARAMETER(pDesktopWnd);
   UNREFERENCED_PARAMETER(nHitTest);
   UNREFERENCED_PARAMETER(message);
   return MA_NOACTIVATE;   
   //return ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


