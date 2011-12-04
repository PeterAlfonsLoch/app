#include "StdAfx.h"
#include <math.h>

clock::clock(::ca::application * papp) :
   ca(papp),
   clock_interface(papp)
{
   class time time = time::get_current_time();
}

void clock::_001OnDraw(::ca::graphics * pdc)
{
   class time timeNow = time::get_current_time() + m_timespan;

   rect rect;
   GetRect(&rect, ElementClock);
   ::ca::pen_sp pen(get_app(), PS_SOLID, 1, RGB(0, 0, 0));
   pdc->SelectObject(pen);
   pdc->DrawEllipse(&rect);

   point ptCenter(rect.center());

   ::ca::pen_sp penHour(get_app(), PS_SOLID, 5, RGB(0, 0, 0));
   ::ca::pen_sp penMinute(get_app(), PS_SOLID, 1, RGB(0, 0, 0));
 
   double dRIntH = rect.width() * 57  / 128;
   double dRIntM = rect.width() * 59  / 128;
   double dRExt = rect.width() * 60  / 128;
 
   for(int i = 0; i < 60; i++)
   {
      double angle = System.math().GetPi() / 2.0 - i * System.math().GetPi() * 2.0 / (60.0);
      point ptInt;
      point ptExt((__int64) (cos(angle) * dRExt), (__int64)(-sin(angle) * dRExt));
      ptExt.Offset(ptCenter);
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
      ptInt.Offset(ptCenter);
      pdc->MoveTo(ptInt);
      pdc->LineTo(ptExt);
   }

   double dRHour = rect.width() * 11  / 32;
   double dRMinute = rect.width() * 15  / 32;
   double dRSecond = rect.width() * 16 / 32;

   ::ca::pen_sp penHM(get_app(), PS_SOLID, 2, RGB(0, 0, 0));
   pdc->SelectObject(penHM);

   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetHour() * System.math().GetPi() * 2.0 / (12.0);
      point ptHour((__int64)(cos(angle) * dRHour), (__int64)(-sin(angle) * dRHour));
      ptHour.Offset(ptCenter);
      pdc->LineTo(ptHour);
   }
   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetMinute() * System.math().GetPi() * 2.0 / (60.0);
      point ptMinute((__int64)(cos(angle) * dRMinute), (__int64)(-sin(angle) * dRMinute));
      ptMinute.Offset(ptCenter);
      pdc->LineTo(ptMinute);
   }
   ::ca::pen_sp penRed(get_app(), PS_SOLID, 1, RGB(200, 0, 0));
   pdc->SelectObject(penRed);
   pdc->MoveTo(ptCenter);
   {
      double angle = System.math().GetPi() / 2.0 - timeNow.GetSecond() * System.math().GetPi() * 2.0 / (60.0);
      point ptSecond((__int64)(cos(angle) * dRSecond), (__int64)(-sin(angle) * dRSecond));
      ptSecond.Offset(ptCenter);
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
