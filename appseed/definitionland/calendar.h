#pragma once


class calendar
{
public:
   calendar();

   enum EElement
   {
      ElementNull,
      ElementPreviousYear,
      ElementPreviousMonth,
      ElementNextMonth,
      ElementNextYear,
      ElementMonthTitle,
      ElementYearTitle,
   };

   CFont    m_font;
   CFont    m_fontYear;
   CFont    m_fontMonth;
   CFont    m_fontSpin;

   void GetRectDay(CTime & time, LPRECT lprect);
   void GetRectDay(int iWeekDay, int iLine, LPRECT lprect);
   void GetRect(LPRECT lprect, enum EElement eelement);

   void set_month(int iYear, int iMonth);
   void set_time(const CTime & time);
   void get_time(CTime & time);

   void _001OnDraw(CDC * pdc);

   void set_pos(point pt, size sz);

   static void GetDateTime(string & strDateTime);

   static string GetTinyWeekDay(int iWeekDay); // 1 - domingo
   static string GetWeekDay(int iWeekDay); // 1 - domingo
   static string GetMonth(int iMonth); // 1 - janeiro

   void previous_month();
   void next_month();
   void next_year();
   void previous_year();

   EElement hit_test(point pt);
   bool hit_test(EElement eelement, point pt);
   bool time_hit_test(CTime & time, point pt);


protected:
   int      m_iMonth;
   int      m_iYear;
   CTime    m_time;
   point    m_point;
   size     m_size;
   int      m_iColWidth;
   int      m_iLineHeight;
};