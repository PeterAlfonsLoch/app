#pragma once

class CLASS_DECL_ca calendar_interface :
   virtual public ::radix::object
{
public:

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


   int      m_iMonth;
   int      m_iYear;
   bool     m_bRange;
   ::datetime::time    m_time;
   ::datetime::time    m_timeEnd;


   calendar_interface(::ca::application * papp);


   virtual void GetRectDay(::datetime::time & time, LPRECT lprect);
   virtual void GetRectDay(int iWeekDay, int iLine, LPRECT lprect);
   virtual void GetRect(LPRECT lprect, enum EElement eelement);

   virtual void set_month(int iYear, int iMonth);
   virtual void set_time(const ::datetime::time & time);
   virtual void set_time_range(const ::datetime::time & time, const ::datetime::time & timeEnd);
   virtual void set_time_end(const ::datetime::time & timeEnd);
   virtual void get_time(::datetime::time & time);
   virtual int get_month();
   virtual int get_year();

   virtual int get_week_of_month(::datetime::time & time);

   virtual void _001OnDraw(::ca::graphics * pdc);

   void set_pos(point pt, size sz);

   virtual void GetDateTime(::user::str_context * pcontext, string & strDateTime);

   virtual string GetTinyWeekDay(::user::str_context * pcontext, int iWeekDay); // 1 - domingo
   virtual string GetWeekDay(::user::str_context * pcontext, int iWeekDay); // 1 - domingo
   virtual string GetMonth(::user::str_context * pcontext, int iMonth); // 1 - janeiro

   virtual void previous_month();
   virtual void next_month();
   virtual void next_year();
   virtual void previous_year();

   virtual EElement hit_test(point pt);
   virtual bool hit_test(EElement eelement, point pt);
   virtual bool time_hit_test(::datetime::time & time, point pt);


};