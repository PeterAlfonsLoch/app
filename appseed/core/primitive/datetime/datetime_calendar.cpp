#include "framework.h"

calendar::calendar(sp(::axis::application) papp) :
   element(papp),
   m_font(allocer()),
   m_fontYear(allocer()),
   m_fontMonth(allocer()),
   m_fontSpin(allocer()),
   calendar_interface(papp)
{
   ::datetime::time time = ::datetime::time::get_current_time();
   m_iYear = time.GetYear();
   m_iMonth = time.GetMonth();
}

void calendar::_001OnDraw(::draw2d::graphics * pdc)
{
   pdc->SelectObject(m_font);
   ::datetime::time timeNow = ::datetime::time::get_current_time();
   int32_t iMonth = m_iMonth;
   int32_t iYear = m_iYear;
   ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
   ::datetime::time_span timespan(1, 0, 0, 0);
   COLORREF crBorder;
   rect rectDay;
   int32_t iDay;
   for(iDay = 1; iDay <= 7; iDay++)
   {
      GetRectDay(iDay, 0, rectDay);
      //crBorder = RGB(184, 184, 177);
      //pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.deflate(m_iColWidth / 10, m_iLineHeight / 10);
      string strDay;
      strDay.Format("%s", GetTinyWeekDay(pdc->str_context(), iDay));
      pdc->draw_text(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
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
      rectDay.deflate(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", iDay);
      pdc->draw_text(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
      time += timespan;
      if(time.GetMonth() != iMonth)
         break;
   }
   if(timeNow.GetMonth() == iMonth
   && timeNow.GetYear() == iYear)
   {
      crBorder = RGB(84, 84, 77);
      GetRectDay(timeNow, rectDay);
      rectDay.inflate(m_iColWidth / 10, m_iColWidth / 10);
      pdc->FillSolidRect(rectDay, RGB(220, 220, 210));
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.deflate(1, 1);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.deflate(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", timeNow.GetDay());
      pdc->draw_text(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }
   ::datetime::time timeEmp = m_time;
   for(int32_t iDay = timeEmp.GetDay(); time.GetYear() == iYear
      && time.GetMonth() == iMonth &&
      (m_time.GetDay() == iDay || (
      m_bRange && time <= m_timeEnd)); time += timespan)
   {
      crBorder = RGB(240, 120, 52);
      GetRectDay(m_time, rectDay);
      rectDay.inflate(m_iColWidth / 10, m_iColWidth / 10);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.deflate(1, 1);
      pdc->Draw3dRect(rectDay, crBorder, crBorder);
      rectDay.deflate(m_iColWidth / 5, m_iLineHeight / 5);
      string strDay;
      strDay.Format("%d", timeEmp.GetDay());
      pdc->draw_text(strDay, rectDay, DT_BOTTOM | DT_RIGHT);
   }

   pdc->SelectObject(m_fontYear);
   class rect rect;
   GetRect(rect, ElementYearTitle);
   string strYear;
   strYear.Format("%d", iYear);
   pdc->draw_text(strYear, rect, DT_CENTER | DT_VCENTER);

   pdc->SelectObject(m_fontMonth);
   GetRect(rect, ElementMonthTitle);
   string strMonth;
   strMonth = GetMonth(pdc->str_context(), iMonth);
   pdc->draw_text(strMonth, rect, DT_CENTER | DT_VCENTER);

   pdc->SelectObject(m_fontSpin);
   GetRect(rect, ElementPreviousYear);
   pdc->draw_text("<<", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementNextYear);
   pdc->draw_text(">>", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementPreviousMonth);
   pdc->draw_text("<", rect, DT_CENTER | DT_VCENTER);
   GetRect(rect, ElementNextMonth);
   pdc->draw_text(">", rect, DT_CENTER | DT_VCENTER);
}

void calendar::_001GetHtml(sp(::html::file) pfile)
{


   try
   {

      // pszSchema can be ignored if the object has only one implemented schema
      ::datetime::time timeNow = ::datetime::time::get_current_time();
      int32_t iMonth = m_iMonth;
      int32_t iYear = m_iYear;
   
      if (iYear > (timeNow.GetYear() + 100))
         return;

      int32_t iWeekDay;

      ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
      ::datetime::time_span timespan(1, 0, 0, 0);
      ::datetime::time timeLastDayOfMonth((iMonth == 12) ? (iYear + 1) : iYear, (iMonth == 12) ? 1 : (iMonth + 1), 1, 0, 0, 0);
      timeLastDayOfMonth -= ::datetime::time_span(1, 0, 0, 0);
      int32_t iFirstDayOfWeek = time.GetDayOfWeek();

      if(pfile->m_strOptions.find("<monday-first>")>=0 && iFirstDayOfWeek == 1)
      {
         iFirstDayOfWeek = 8;
      }

//      int32_t iFirstWeek;
      int32_t iLastDayOfWeek = timeLastDayOfMonth.GetDayOfWeek();
      int32_t iLastDayPreviousMonth = (time - ::datetime::time_span(1, 0, 0, 0)).GetDay();
      rect rectDay;
      int32_t iDay;
      pfile->raw_print("<table cellpadding=\"0\" cellspacing=\"0\">");
      if(pfile->m_strOptions.find("<no-week-bar-title>") < 0)
      {
         pfile->raw_print("<tr>");
         if(pfile->m_strOptions.find("<left-week-of-the-year>") >= 0)
         {
            pfile->raw_print("<td>");
            pfile->raw_print("V");
            pfile->raw_print("</td>");
         }
         for(iWeekDay = 1; iWeekDay <= 7; iWeekDay++)
         {
            int32_t iDayOfWeek = iWeekDay;
            if(pfile->m_strOptions.find("<monday-first>")>=0)
            {
               iDayOfWeek++;
               if(iDayOfWeek > 7)
                  iDayOfWeek = 1;
            }
            pfile->raw_print("<td>");
            pfile->printf("%s", GetTinyWeekDay(pfile->str_context(), iDayOfWeek));
            pfile->raw_print("</td>");
         }
         pfile->raw_print("</tr>");
      }


      int32_t iDayCount = timeLastDayOfMonth.GetDay();
      int32_t iLineCount = (iDayCount + iFirstDayOfWeek - 1) / 7;
      if(((iDayCount + iFirstDayOfWeek - 1) % 7) > 0)
         iLineCount++;

      iDay = 1;
      for(int32_t iWeek = 1; iWeek <= iLineCount; iWeek++)
      {
         pfile->raw_print("<tr>");
         if(pfile->m_strOptions.find("<left-week-of-the-year>") >= 0)
         {
            time_t w ;       if(pfile->m_strOptions.find("<monday-first>")>=0)
      {
         w = atoi(System.datetime().strftime("%V", (time_t)::datetime::time(iYear, iMonth, iDay, 0, 0, 0).get_time()));
      }
      else
      {
         w = atoi( ::datetime::time(iYear, iMonth, iDay, 0, 0, 0).Format("%U"));
      }

            pfile->raw_print("<td>");
            pfile->raw_print(::str::from((int64_t) w));
            pfile->raw_print("</td>");
         }
         for(int32_t iWeekDay = 1; iWeekDay <=7; iWeekDay++)
         {
            int32_t iDayOfWeek = iWeekDay;
            if(pfile->m_strOptions.find("<monday-first>")>=0)
            {
               iDayOfWeek++;
            }

            pfile->raw_print("<td>");

            if((!m_bRange &&
               iMonth == m_time.GetMonth()
               && iYear == m_time.GetYear( )
               && iDay == m_time.GetDay()) ||
               (m_bRange &&
               ::datetime::time(iYear, iMonth, iDay, 23, 59, 59) >= m_time
               && ::datetime::time(iYear, iMonth, iDay, 0, 0, 0) <= m_timeEnd))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-sel\">");
            }
            else if((iWeek == 1 && iDayOfWeek < iFirstDayOfWeek) ||
               (iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-out-of-month-day\">");
            }
            else if((timeNow.GetDay() == iDay &&
               timeNow.GetMonth() == iMonth &&
               timeNow.GetYear() == iYear)
               ||
               (iDay == m_time.GetDay() &&
               iMonth == m_time.GetMonth() &&
               iYear == m_time.GetYear()))
            {
               pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-today\">");
            }
            else
            {
               if(iDayOfWeek == 1 || iDayOfWeek == 8)
               {
                  pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-sunday\">");
               }
               else
               {
                  pfile->raw_print("<div class=\""+ pfile->m_strStyle + "calendar-day\">");
               }
            }
            if(iWeek == 1 && iDayOfWeek < iFirstDayOfWeek)
            {
               pfile->printf("%d", iLastDayPreviousMonth + iDayOfWeek - iFirstDayOfWeek + 1);
               iDay = 1;
            }
            else if(iWeek == iLineCount && iDayOfWeek > iLastDayOfWeek)
            {
               pfile->printf("%d", iDayOfWeek - iLastDayOfWeek);
            }
            else
            {
               pfile->printf("%d", iDay);
               iDay++;
            }
            pfile->raw_print("</div></td>");
         }
         pfile->raw_print("</tr>");
      }
      pfile->raw_print("</table>");
   }
   catch(...)
   {
      //-----\/----- implement diagnostic print for html file;
      pfile->dprint("error calendar::_001GetHtml");
      // worst case: mal-formed calendar display
   }

}


void calendar::GetRectDay(::datetime::time & time, LPRECT lprect)
{
   int32_t iWeekDay = time.GetDayOfWeek();
   ::datetime::time timeMonth(m_iYear, m_iMonth, 1, 0, 0, 0);
   int32_t iWeek = get_week_of_month(time);
   GetRectDay(iWeekDay, iWeek + 1, lprect);
}

void calendar::GetRectDay(int32_t iWeekDay, int32_t iLine, LPRECT lprect)
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
         default:
            throw not_supported_exception(get_app());
      }
   }
}



void calendar::set_pos(point pt, size sz)
{
   m_point = pt;
   m_size = sz;
   m_iColWidth = m_size.cx / 7;
   m_iLineHeight = m_size.cy / 8;
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

bool calendar::time_hit_test(::datetime::time & timeRet, point pt)
{
   int32_t iMonth = m_iMonth;
   int32_t iYear = m_iYear;
   ::datetime::time time(iYear, iMonth, 1, 0, 0, 0);
   ::datetime::time_span timespan(1, 0, 0, 0);
   rect rectDay;
   int32_t iDay;
   for(iDay = 1; iDay <= 33; iDay++)
   {
      GetRectDay(time, rectDay);
      if(rectDay.contains(pt))
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
   return rect.contains(pt) != FALSE;

}


