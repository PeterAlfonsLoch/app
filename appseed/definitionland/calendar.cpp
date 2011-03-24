#include "StdAfx.h"

calendar::calendar()
{
   CTime time = CTime::GetCurrentTime();
   m_iYear = time.GetYear();
   m_iMonth = time.GetMonth();
}

void calendar::_001OnDraw(CDC * pdc)
{
   pdc->SelectObject(&m_font);
   CTime timeNow = CTime::GetCurrentTime();
   int iMonth = m_iMonth;
   int iYear = m_iYear;
   CTime time(iYear, iMonth, 1, 0, 0, 0);
   CTimeSpan timespan(1, 0, 0, 0);
   COLORREF crBorder;
   rect rectDay;
   int iDay;
   for(iDay = 1; iDay <= 7; iDay++)
   {
      GetRectDay(iDay, 0, rectDay);
      //crBorder = RGB(184, 184, 177);
      //pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(m_iColWidth / 10, m_iLineHeight / 10);
      string strDay;
      strDay.Format("%s", GetTinyWeekDay(iDay));
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
   for(iDay = 1; iDay <= 33; iDay++)
   {
      if((timeNow.GetDay() == iDay &&
         timeNow.GetMonth() == iMonth &&
         timeNow.GetYear() == iYear)
         ||
         (iDay == m_time.GetDay() &&
         iMonth == m_time.GetMonth() &&
         iYear == m_time.GetYear()))
      {
         time += timespan;
         if(time.GetMonth() != iMonth)
            break;
         continue;
      }
      GetRectDay(time, rectDay);
      crBorder = RGB(184, 184, 177);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", iDay);
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
      time += timespan;
      if(time.GetMonth() != iMonth)
         break;
   }
   if(timeNow.GetMonth() == iMonth
   && timeNow.GetYear() == iYear)
   {
      crBorder = RGB(84, 84, 77);
      GetRectDay(timeNow, rectDay);
      rectDay.InflateRect(m_iColWidth / 10, m_iColWidth / 10);
      pdc->FillSolidRect(rectDay, RGB(220, 220, 210));
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(1, 1);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", timeNow.GetDay());
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
   if(iMonth == m_time.GetMonth()
   && iYear == m_time.GetYear( ))
   {
      crBorder = RGB(240, 120, 52);
      GetRectDay(m_time, rectDay);
      rectDay.InflateRect(m_iColWidth / 10, m_iColWidth / 10);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(1, 1);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.DeflateRect(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", m_time.GetDay());
      pdc->DrawText(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
   
   pdc->SelectObject(&m_fontYear);
   class rect rect;
   GetRect(rect, ElementYearTitle);
   string strYear;
   strYear.Format("%d", iYear);
   pdc->DrawText(strYear, rect, DT_CENTER | DT_VCENTER);

   pdc->SelectObject(&m_fontMonth);
   GetRect(rect, ElementMonthTitle);
   string strMonth;
   strMonth = GetMonth(iMonth);
   pdc->DrawText(strMonth, rect, DT_CENTER | DT_VCENTER);

   pdc->SelectObject(&m_fontSpin);
   GetRect(rect, ElementPreviousYear);
   pdc->DrawText("<<", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementNextYear);
   pdc->DrawText(">>", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementPreviousMonth);
   pdc->DrawText("<", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementNextMonth);
   pdc->DrawText(">", rect, DT_CENTER | DT_VCENTER);
}


void calendar::GetRectDay(CTime & time, LPRECT lprect)
{
   int iWeekDay = time.GetDayOfWeek();
   CTime timeMonth(m_iYear, m_iMonth, 1, 0, 0, 0);
  int iWeek = (time.GetDay() + timeMonth.GetDayOfWeek() - 2) / 7;
   GetRectDay(iWeekDay, iWeek + 1, lprect);
}

void calendar::GetRectDay(int iWeekDay, int iLine, LPRECT lprect)
{
   lprect->left = m_point.x + m_iColWidth * (iWeekDay - 1);
   lprect->right = lprect->left + m_iColWidth + 1;
   lprect->top = m_point.y + m_iLineHeight * iLine;
   lprect->bottom = lprect->top + m_iLineHeight + 1;
}

void calendar::GetRect(LPRECT lprect, enum EElement eelement)
{
   if(eelement == ElementMonthTitle)
   {
      lprect->left = m_point.x + m_iColWidth * 1;
      lprect->right = lprect->left + m_iColWidth * 2 + 1;
      lprect->top = m_point.y + m_iLineHeight * 7;
      lprect->bottom = lprect->top + m_iLineHeight + 1;
   }
   else
   {
      switch(eelement)
      {
      case ElementPreviousYear:
         GetRectDay(5, 7, lprect);
         return;
      case ElementPreviousMonth:
         GetRectDay(1, 7, lprect);
         return;
      case ElementNextMonth:
         GetRectDay(4, 7, lprect);
         return;
      case ElementNextYear:
         GetRectDay(7, 7, lprect);
         return;
      case ElementYearTitle:
         GetRectDay(6, 7, lprect);
         return;
      }
   }
}


void calendar::set_time(const CTime & time)
{
   m_time = time;
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
   m_iLineHeight = m_size.cy / 8;
}


void calendar::GetDateTime(string & strDateTime)
{
   CTime time = CTime::GetCurrentTime();
   string strDate;
   string strWeekDay;
   string strTime;
   strDate.Format(
      "%d de %s de %d",
      time.GetDay(),
      GetMonth(time.GetMonth()),
      time.GetYear());
   strWeekDay = GetWeekDay(time.GetDayOfWeek());
   strTime.Format("%02d:%02d:%02d",
      time.GetHour(),
      time.GetMinute(),
      time.GetSecond());
   strDateTime.Format("%s %s, %s", strTime,  strWeekDay, strDate);
}


string calendar::GetWeekDay(int iWeekDay) // 1 - domingo
{
   string strWeekDay;
   switch(iWeekDay)
   {
   case 1:
      strWeekDay = "domingo";
      break;
   case 2:
      strWeekDay = "segunda-feira";
      break;
   case 3:
      strWeekDay = unitext("terça-feira");
      break;
   case 4:
      strWeekDay = "quarta-feira";
      break;
   case 5:
      strWeekDay = "quinta-feira";
      break;
   case 6:
      strWeekDay = "sexta-feira";
      break;
   case 7:
      strWeekDay = unitext("sábado");
      break;
   }
   return strWeekDay;
}


string calendar::GetTinyWeekDay(int iWeekDay) // 1 - domingo
{
   string strWeekDay;
   switch(iWeekDay)
   {
   case 1:
      strWeekDay = "D";
      break;
   case 2:
      strWeekDay = "S";
      break;
   case 3:
      strWeekDay = "T";
      break;
   case 4:
      strWeekDay = "Q";
      break;
   case 5:
      strWeekDay = "Q";
      break;
   case 6:
      strWeekDay = "S";
      break;
   case 7:
      strWeekDay = "S";
      break;
   }
   return strWeekDay;
}

string calendar::GetMonth(int iMonth)
{
   string strMonth;
   switch(iMonth)
   {
   case 1:
      strMonth = "janeiro";
      break;
   case 2:
      strMonth = "fevereiro";
      break;
   case 3:
      strMonth = unitext("março");
      break;
   case 4:
      strMonth = "abril";
      break;
   case 5:
      strMonth = "maio";
      break;
   case 6:
      strMonth = "junho";
      break;
   case 7:
      strMonth = unitext("julho");
      break;
   case 8:
      strMonth = "agosto";
      break;
   case 9:
      strMonth = "setembro";
      break;
   case 10:
      strMonth = unitext("outubro");
      break;
   case 11:
      strMonth = "novembro";
      break;
   case 12:
      strMonth = "dezembro";
      break;
   }
   return strMonth;
}


void calendar::set_month(int iYear, int iMonth)
{
   m_iYear = iYear;
   m_iMonth = iMonth;
}


void calendar::previous_month()
{
   if(m_iMonth <= 1)
   {
      m_iMonth = 12;
      m_iYear--;
   }
   else
   {
      m_iMonth--;
   }
}
void calendar::next_month()
{
   if(m_iMonth >= 12)
   {
      m_iMonth = 1;
      m_iYear++;
   }
   else
   {
      m_iMonth++;
   }
}
void calendar::next_year()
{
   m_iYear++;
}
void calendar::previous_year()
{
   m_iYear--;
}


calendar::EElement calendar::hit_test(point pt)
{
   if(hit_test(ElementNextMonth, pt))
      return ElementNextMonth;
   if(hit_test(ElementNextYear, pt))
      return ElementNextYear;
   if(hit_test(ElementPreviousMonth, pt))
      return ElementPreviousMonth;
   if(hit_test(ElementPreviousYear, pt))
      return ElementPreviousYear;
   return ElementNull;
}

bool calendar::time_hit_test(CTime & timeRet, point pt)
{
   int iMonth = m_iMonth;
   int iYear = m_iYear;
   CTime time(iYear, iMonth, 1, 0, 0, 0);
   CTimeSpan timespan(1, 0, 0, 0);
   COLORREF crBorder;
   rect rectDay;
   int iDay;
   for(iDay = 1; iDay <= 33; iDay++)
   {
      GetRectDay(time, rectDay);
      if(rectDay.PtInRect(pt))
      {
         timeRet = time;
         return true;
      }
      time += timespan;
      if(time.GetMonth() != iMonth)
         break;
   }
   return false;
}

bool calendar::hit_test(EElement eelement, point pt)
{
   class rect rect;
   GetRect(rect, eelement);
   return rect.PtInRect(pt);
}