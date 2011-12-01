#include "StdAfx.h"

namespace user
{

   check_box::check_box(::ca::application * papp) :
      ca(papp),
      ::user::interaction(papp)
   {
      m_echeck = check::unchecked;
   }

   check_box::~check_box()
   {
   }


   check::e_check check_box::_001GetCheck()
   {
      return m_echeck;
   }

   void check_box::_001SetCheck(check::e_check echeck, bool bUser)
   {
      if(echeck != check::unchecked 
      && echeck != check::checked
      && echeck != check::tristate)
      {
         // default value when setting a value that does not match the ones above
         echeck = check::checked;
      }
      m_echeck = echeck;
      ::user::control_event ev;
      ev.m_puie = this;
      ev.m_eevent = ::user::event_set_check;
      ev.m_bUser = bUser;
      if(get_form() != NULL)
      {
         get_form()->SendMessage(
            ::user::message_event, 0, (LPARAM) &ev);
      }
      else
      {
         GetParent()->SendMessage(
            ::user::message_event, 0, (LPARAM) &ev);
      }
   }


   void check_box::_001OnDraw(::ca::graphics * pdc)
   {
      rect rectClient;
      GetClientRect(rectClient);
      pdc->OffsetViewportOrg(rectClient.left, rectClient.top);

      // if no image
      {
         rect rectCheckBox;
         rectCheckBox.left = 0;
         rectCheckBox.top = 0;
         rectCheckBox.right = 15;
         rectCheckBox.bottom = 15;
         if(m_echeck == check::tristate)
         {
            pdc->FillSolidRect(rectCheckBox, RGB(220, 220, 220));
         }
         pdc->Draw3dRect(rectCheckBox, RGB(128, 128, 128), RGB(128, 128, 128));
         if(m_echeck == check::tristate 
         || m_echeck == check::checked)
         {
            ::ca::pen_sp pen(get_app());
            pen->construct(PS_SOLID, 1, m_echeck == check::checked ? RGB(0, 0, 0) : RGB(96, 96, 96));
            pdc->SelectObject(pen);
            pdc->MoveTo(2, 8);
            pdc->LineTo(6, 12);
            pdc->LineTo(13, 5);
            pdc->MoveTo(2, 9);
            pdc->LineTo(6, 13);
            pdc->LineTo(13, 6);
         }
      }
      pdc->OffsetViewportOrg(-rectClient.left, -rectClient.top);
      
   }


   void check_box::_001OnTimer(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::gen::message::timer, ptimer, pobj)
   }

   void check_box::_001OnKeyDown(gen::signal_object * pobj) 
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::key, pkey, pobj)
   }

   void check_box::_001OnKeyUp(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::key, pkey, pobj)
      if(pkey->m_nChar == VK_SPACE)
      {
         _001ToggleCheck(true);
      }
   }


   void check_box::_001OnLButtonDown(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      m_bMouseDown = true;
      
   }
   void check_box::_001OnLButtonUp(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      if(m_bMouseDown)
      {
         _001ToggleCheck(true);
         pobj->m_bRet = true;
         pmouse->set_lresult(1);
      }
      m_bMouseDown = false;
      //System.simple_message_box(m_strText);
   }


   void check_box::_001OnMouseMove(gen::signal_object * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::gen::message::mouse, pmouse, pobj)
      ::SetCursor(::LoadCursor(NULL, IDC_IBEAM));
   }

   void check_box::install_message_handling(::gen::message::dispatch * pinterface)
   {
      ::user::interaction::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &check_box::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &check_box::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &check_box::_001OnMouseMove);
   }

} // namespace user