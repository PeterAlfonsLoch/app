#include "StdAfx.h"

void calendar::_001OnDraw(CDC * pdc)
{
   pdc->SelectObject(&m_font);
   CTime timeNow = CTime::GetCurrentTime();
   int iMonth = m_time.GetMonth();
   int iYear = m_time.GetYear();
   CTime time(iYear, iMonth, 1, 0, 0, 0);
   CTimeSpan timespan(1, 0, 0, 0);
   COLORREF crBorder;
   rect rectDay;
   int iDay;
   for(int iDay = 1; iDay <= 33; iDay++)
   {
      if((timeNow.GetDay() == iDay &&
         timeNow.GetMonth() == m_time.GetMonth() &&
         timeNow.GetYear() == m_time.GetYear())
         ||
         (iDay == m_time.GetDay() &&
         iMonth == m_time.GetMonth() &&
         iYear == m_time.GetYear()))
      {
         continue;
      }
      GetRectDay(time, rectDay);
      crBorder = RGB(184, 184, 177);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(3, 3);
      string strDay;
      strDay.Format("%d", iDay);
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
      time += timespan;
      if(time.GetMonth() != m_time.GetMonth())
         break;
   }
   if(timeNow.GetMonth() == m_time.GetMonth() &&
      timeNow.GetYear() == m_time.GetYear())
   {
      crBorder = RGB(84, 84, 77);
      pdc->FillSolidRect(rectDay, RGB(220, 220, 210));
      GetRectDay(timeNow, rectDay);
      rectDay.InflateRect(2, 2);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(1, 1);
      string strDay;
      strDay.Format("%d", timeNow.GetDay());
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
   if(iMonth == m_time.GetMonth() &&
      iYear == m_time.GetYear( ))
   {
      crBorder = RGB(240, 184, 177);
      GetRectDay(m_time, rectDay);
      rectDay.InflateRect(2, 2);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(1, 1);
      string strDay;
      strDay.Format("%d", m_time.GetDay());
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
}

void calendar::GetRectDay(CTime & time, LPRECT lprect)
{
   int iWeekDay = time.GetDayOfWeek();
   int iWeek = (time.GetDay() + m_timeMonth.GetDayOfWeek() - 1) / 7;
   lprect->left = m_point.x + m_iColWidth * (iWeekDay - 1);
   lprect->right = lprect->left + m_iColWidth + 1;
   lprect->top = m_point.y + m_iLineHeight * iWeek;
   lprect->bottom = lprect->top + m_iLineHeight + 1;
}


void calendar::set_time(const CTime & time)
{
   m_time = time;
   m_timeMonth = CTime(time.GetYear(), time.GetMonth(), 1, 0, 0, 0);
}

void calendar::get_time(CTime & time)
{
   time = m_time;
}

void calendar::set_pos(point pt, size sz)
{
   m_point = pt;
   m_size = sz;
   m_iColWidth = m_size.cx / 7;
   m_iLineHeight = m_size.cy / 6;
}