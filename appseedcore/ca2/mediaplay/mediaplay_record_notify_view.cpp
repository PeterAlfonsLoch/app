#include "StdAfx.h"


namespace mediaplay
{

   record_notify_view::record_notify_view(::ca::application * papp) :
      ca(papp),
      virtual_user_interface(papp), 
      ::user::interaction(papp)
   {
      m_dwOnTime = 800;
      m_dwOffTime = 200;
   }

   record_notify_view::~record_notify_view()
   {
   }

   bool record_notify_view::create(::user::interaction * pinterface, id id)
   {
      pinterface->SetTimer((UINT_PTR) this, min(m_dwOnTime, m_dwOffTime) / 2, NULL);
      return virtual_user_interface::create(pinterface, id);
   }

   void record_notify_view::_001OnTimer(gen::signal_object * pobj)
   {
      SCAST_PTR(::user::win::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == ((UINT_PTR) this))
      {
         _001RedrawWindow();
         ptimer->m_bRet = true;
         return;
      }
      ptimer->m_bRet = false;
   }

   void record_notify_view::_001OnDraw(::ca::graphics *pdc)
   {
      if((GetTickCount() % (m_dwOnTime + m_dwOffTime)) > m_dwOnTime)
      {
         return;
      }
      pdc->SetBkMode(TRANSPARENT);
      pdc->SetTextColor(RGB(0, 0, 0));
   //   pdc->SelectObject(m_font);
      rect rect;
      GetClientRect(rect);
      class imaging & imaging = System.imaging();
      imaging.color_blend(
         pdc,
         rect,
         RGB(255, 0, 0),
         127);

      pdc->DrawText(
         "Recording",
         rect,
         DT_LEFT
         | DT_BOTTOM);
      virtual_user_interface::_001OnDraw(pdc);
   }

   void record_notify_view::_001InstallMessageHandling(::user::win::message::dispatch * pinterface)
   {
      ::user::win::message::connect(WM_TIMER, pinterface, this, &record_notify_view::_001OnTimer);
   }

   void record_notify_view::GetParentClientRect(LPRECT lprect)
   {
      m_pparent->GetClientRect(lprect);
   }

} // namespace mediaplay