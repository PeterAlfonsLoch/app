#pragma once


class calendar
{
public:

   CFont    m_font;

   void GetRectDay(CTime & time, LPRECT lprect);


   void set_time(const CTime & time);
   void get_time(CTime & time);

   void _001OnDraw(CDC * pdc);

   void set_pos(point pt, size sz);


protected:
   CTime    m_time;
   CTime    m_timeMonth;
   point    m_point;
   size     m_size;
   int      m_iColWidth;
   int      m_iLineHeight;
};