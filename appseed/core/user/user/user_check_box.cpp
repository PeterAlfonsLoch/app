#include "framework.h"

namespace user
{

   check_box::check_box(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp)
   {
      m_echeck = check::unchecked;
      m_estyle = style_normal;
   }

   check_box::~check_box()
   {
   }


   check::e_check check_box::_001GetCheck()
   {
      return m_echeck;
   }

   void check_box::_001SetCheck(check::e_check echeck, ::action::context actioncontext)
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
      ev.m_actioncontext = actioncontext;
      if(get_form() != NULL)
      {
         get_form()->send_message(
            ::message::message_event, 0, (LPARAM) &ev);
      }
      else
      {
         GetParent()->send_message(
            ::message::message_event, 0, (LPARAM) &ev);
      }
   }

   void check_box::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_estyle == style_red_green_circle)
      {

         _001OnDrawRedGreenCircle(pgraphics);

      }
      else
      {

         _001OnDrawNormal(pgraphics);

      }

   }


   void check_box::_001OnDrawNormal(::draw2d::graphics * pgraphics)
   {

      if (m_puserschemaSchema != NULL)
      {

         rect rectClient;

         GetClientRect(rectClient);

         m_puserschemaSchema->_001DrawCheckBox(pgraphics, rectClient, _001GetCheck());

      }


   }


   void check_box::_001OnDrawRedGreenCircle(::draw2d::graphics * pgraphics)
   {



      rect rectClient;
      GetClientRect(rectClient);

      int iMin = MAX(MIN(rectClient.size().cx, rectClient.size().cy) -1, 1);

      rect rectCheckBox;
      rectCheckBox.left = 1;
      rectCheckBox.top = 1;
      rectCheckBox.right = iMin + 1;
      rectCheckBox.bottom = iMin + 1;

      COLORREF crPen = ARGB(255, 0, 0, 0);
      COLORREF crBrush;

      if (m_echeck == check::checked)
      {
         
         crBrush = ARGB(255, 100, 220, 120);

      }
      else if (m_echeck == check::unchecked)
      {

         crBrush = ARGB(255, 220, 220, 100);

      }
      else
      {

         crBrush = ARGB(255, 128, 128, 128);

      }

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0, crPen);

      pgraphics->SelectObject(pen);

      ::draw2d::brush_sp brush(allocer());

      brush->create_solid(crBrush);

      pgraphics->SelectObject(brush);

      pgraphics->Ellipse(rectCheckBox);
      //   pgraphics->Draw3dRect(rectCheckBox, ARGB(255, 128, 128, 128), ARGB(255, 128, 128, 128));
      //   if (m_echeck == check::tristate
      //      || m_echeck == check::checked)
      //   {
      //      ::draw2d::pen_sp pen(allocer());
      //      pen->create_solid(1, m_echeck == check::checked ? ARGB(255, 0, 0, 0) : ARGB(255, 96, 96, 96));
      //      pgraphics->SelectObject(pen);
      //      pgraphics->MoveTo(2, 8);
      //      pgraphics->LineTo(6, 12);
      //      pgraphics->LineTo(13, 5);
      //      pgraphics->MoveTo(2, 9);
      //      pgraphics->LineTo(6, 13);
      //      pgraphics->LineTo(13, 6);
      //   }
      //}
      //pgraphics->OffsetViewportOrg(-rectClient.left, -rectClient.top);

   }


   void check_box::_001OnTimer(::timer * ptimer)
   {
      
      ::user::control::_001OnTimer(ptimer);

   }

   void check_box::_001OnKeyDown(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::key, pkey, pobj);
   }

   void check_box::_001OnKeyUp(signal_details * pobj)
   {
      SCAST_PTR(::message::key, pkey, pobj);
      if(pkey->m_ekey == ::user::key_space)
      {
         _001ToggleCheck(::action::source_user);
      }
   }


   void check_box::_001OnLButtonDown(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
//      SCAST_PTR(::message::mouse, pmouse, pobj);
      m_bMouseDown = true;
      pobj->m_bRet = true;

   }
   void check_box::_001OnLButtonUp(signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      SCAST_PTR(::message::mouse, pmouse, pobj);
      if(m_bMouseDown)
      {
         _001ToggleCheck(::action::source_user);
         pobj->m_bRet = true;
         pmouse->set_lresult(1);
      }
      m_bMouseDown = false;
      //System.simple_message_box(m_strText);
   }


   void check_box::_001OnMouseMove(signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_text_select;


   }



   void check_box::install_message_handling(::message::dispatch * pinterface)
   {
      
      ::user::interaction::install_message_handling(pinterface);
      
      IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &check_box::_001OnLButtonDown);
      IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &check_box::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &check_box::_001OnMouseMove);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &check_box::_001OnCreate);

   }

   void check_box::_001OnCreate(signal_details * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      m_puserschemaSchema = Application.userschema();

   }


} // namespace user
