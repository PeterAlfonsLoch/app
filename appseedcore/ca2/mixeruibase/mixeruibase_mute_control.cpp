#include "StdAfx.h"
#include "mute_control.h"

namespace mixeruserbase
{

   mute_control::mute_control(::ca::application * papp) :
      ca(papp),
      ::user::button(papp),
      simple_button(papp)
   {
      m_bTransparent = true;
   }

   mute_control::~mute_control()
   {
   }

   check::e_check mute_control::_001GetCheck()
   {
      return simple_button::_001GetCheck();
   }

   void mute_control::_001SetCheck(check::e_check echeck)
   {
      simple_button::_001SetCheck(echeck, true);
   }

   void mute_control::set_label(const char * lpcsz)
   {
      SetWindowText(lpcsz);
   }

   ::user::interaction * mute_control::GetWnd()
   {
      return this;
   }

   bool mute_control::Initialize(::user::interaction * pwndParent, UINT uiId)
   {
      rect rect(0, 0, 0, 0);
      return simple_button::create(
         NULL,
           "",
           BS_AUTOCHECKBOX |
           WS_CHILD |
           WS_VISIBLE,
           rect,
           pwndParent,
           uiId) != FALSE;
   }

   int mute_control::_GetDlgCtrlID()
   {
      return ::user::interaction::GetDlgCtrlId();
   }

} // namespace mixeruserbase