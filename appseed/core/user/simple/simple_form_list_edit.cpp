#include "framework.h"


simple_form_list_edit::simple_form_list_edit(sp(::base::application) papp) :
    element(papp),
   ::user::interaction(papp),
   ::user::scroll_view(papp),
   ::data::data_listener(papp),
   ::colorertake5::base_editor(papp),
   ::user::edit_plain_text(papp)
{

}


simple_form_list_edit::~simple_form_list_edit()
{

}


bool simple_form_list_edit::OnEraseBkgnd(::draw2d::graphics * pgraphics)
{
   UNREFERENCED_PARAMETER(pgraphics);
   return TRUE;
}

void simple_form_list_edit::_001OnCreate(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);


   sp(::user::interaction) pwndParent = ::user::interaction::GetParent();
   if(base_class < simple_form_list_view >::bases(pwndParent))
   {

      simple_form_list_view * pview = dynamic_cast < simple_form_list_view * > (pwndParent.m_p);
      m_plistinterface = pview;
   }

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

sp(::user::interaction) simple_form_list_edit::GetNotifyWnd()
{
   sp(::user::interaction) pwnd = GetOwner();
   if(pwnd != NULL)
      return pwnd;
   return ::user::interaction::GetParent();
}

void simple_form_list_edit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   UNREFERENCED_PARAMETER(nFlags);
   UNREFERENCED_PARAMETER(nRepCnt);
//   if(nChar == VK_RETURN)
   {
      return;
   }
// trans   ::user::interaction::OnChar(nChar, nRepCnt, nFlags);
}

int32_t simple_form_list_edit::OnMouseActivate(sp(::user::interaction) pDesktopWnd, UINT nHitTest, UINT message)
{
   UNREFERENCED_PARAMETER(pDesktopWnd);
   UNREFERENCED_PARAMETER(nHitTest);
   UNREFERENCED_PARAMETER(message);
   return MA_NOACTIVATE;
   //return ::user::interaction::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


