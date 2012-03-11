#pragma once


namespace ca2
{


   class html_file;


} // namespace html


class CLASS_DECL_ca calendar :
   public calendar_interface
{
protected:


   point    m_point;
   size     m_size;
   int      m_iColWidth;
   int      m_iLineHeight;


public:

   
   ::ca::font_sp    m_font;
   ::ca::font_sp    m_fontYear;
   ::ca::font_sp    m_fontMonth;
   ::ca::font_sp    m_fontSpin;


   calendar(::ca::application * papp);


   virtual void GetRectDay(class time & time, LPRECT lprect);
   virtual void GetRectDay(int iWeekDay, int iLine, LPRECT lprect);
   virtual void GetRect(LPRECT lprect, enum EElement eelement);

   void _001OnDraw(::ca::graphics * pdc);
   void _001GetHtml(::ca2::html_file * pfile);

   void set_pos(point pt, size sz);

   virtual EElement hit_test(point pt);
   virtual bool hit_test(EElement eelement, point pt);
   virtual bool time_hit_test(class time & time, point pt);





};



