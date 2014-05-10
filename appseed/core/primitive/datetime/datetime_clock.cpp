#include "framework.h"


clock::clock(sp(::base::application) papp) :
   element(papp),
   clock_interface(papp)
{
//   ::datetime::time time = ::datetime::time::get_current_time();
}

void clock::_001OnDraw(::draw2d::graphics * pdc)
{
   ::datetime::time timeNow = ::datetime::time::get_current_time() + m_timespan;

   rect rect;
   GetRect(&rect, ElementClock);
   ::draw2d::pen_sp pen(pdc, 1, ARGB(255, 0, 0, 0));
   pdc->SelectObject(pen);
   pdc->DrawEllipse(&rect);

   point ptCenter(rect.center());

   ::draw2d::pen_sp penHour(pdc, 5, ARGB(255, 0, 0, 0));
   ::draw2d::pen_sp penMinute(pdc, 1, ARGB(255, 0, 0, 0));

   double dRIntH = rect.width() * 57  / 128;
   double dRIntM = rect.width() * 59  / 128;
   double dRExt = rect.width() * 60  / 128;

   for(int32_t i = 0; i < 60; i++)
   {
      double angle = System.math().GetPi() / 2.0 - i * System.math().GetPi() * 2.0 / (60.0);
      point ptInt;
      point ptExt((int64_t) (cos(angle) * dRExt), (int64_t)(-sin(angle) * dRExt));
      ptExt.offset(ptCenter);
      if(i % 5 == 0)
      {
         ptInt.x = (LONG) (cos(angle) * dRIntH);
         ptInt.y = (LONG) (-sin(angle) * dRIntH);
         pdc->SelectObject(penHour);
      }
      else
      {
         ptInt.x = (LONG) (cos(angle) * dRIntM);
         ptInt.y = (LONG) (-sin(angle) * dRIntM);
         pdc->SelectObject(penMinute);
      }
      ptInt.offset(ptCenter);
      pdc->MoveTo(ptInt);
      pdc->LineTo(ptExt);
   }

   double dRHour = rect.width() * 11  / 32;
   double dRMinute = rect.width() * 15  / 32;
   double dRSecond = rect.width() * 16 / 32;

   ::draw2d::pen_sp penHM(pdc, 2, ARGB(255, 0, 0, 0));
   pdc->SelectObject(penHM);

   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetHour() * System.math().GetPi() * 2.0 / (12.0);
      point ptHour((int64_t)(cos(angle) * dRHour), (int64_t)(-sin(angle) * dRHour));
      ptHour.offset(ptCenter);
      pdc->LineTo(ptHour);
   }
   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetMinute() * System.math().GetPi() * 2.0 / (60.0);
      point ptMinute((int64_t)(cos(angle) * dRMinute), (int64_t)(-sin(angle) * dRMinute));
      ptMinute.offset(ptCenter);
      pdc->LineTo(ptMinute);
   }
   ::draw2d::pen_sp penRed(pdc, 1, ARGB(255, 200, 0, 0));
   pdc->SelectObject(penRed);
   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetSecond() * System.math().GetPi() * 2.0 / (60.0);
      point ptSecond((int64_t)(cos(angle) * dRSecond), (int64_t)(-sin(angle) * dRSecond));
      ptSecond.offset(ptCenter);
      pdc->LineTo(ptSecond);
   }



}



void clock::GetRect(LPRECT lprect, enum EElement eelement)
{
   if(eelement == ElementClock)
   {
      lprect->left = m_point.x;
      lprect->right = lprect->left + m_size.cx;
      lprect->top = m_point.y;
      lprect->bottom = lprect->top + m_size.cy;
   }
}



void clock::set_pos(point pt, size sz)
{
   m_point = pt;
   m_size = sz;
}
