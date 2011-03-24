#include "StdAfx.h"

namespace ca2
{


   datetime::datetime(::ca::application * papp) :
      ca(papp),
      m_international(papp),
      m_str(papp)
   {
      m_str.m_pdatetime = this;
   }

   class datetime::international & datetime::international()
   {
      return m_international;
   }

   class datetime::str & datetime::str()
   {
      return m_str;
   }

   int datetime::get_month_day_count(int year, int month)
   {
      switch(month)
      {
      case 1:
         return 31;
      case 2:
         if((year % 4)== 0)
            return 29;
         else
            return 28;
      case 3:
         return 31;
      case 4:
         return 30;
      case 5:
         return 31;
      case 6:
         return 30;
      case 7:
         return 31;
      case 8:
         return 31;
      case 9:
         return 30;
      case 10:
         return 31;
      case 11:
         return 30;
      case 12:
         return 31;
      }
      return -1;   
   }

// 0 is Sunday
   int datetime::get_weekday(int year, int month, int day)
   {
      class time time(year, month, day, 0, 0, 0);
      return atoi(time.Format("%w"));
   }

   int64_t datetime::get_timestamp(int year, int month, int day)
   {
      string strInternationalDate;
      strInternationalDate.Format("%d-%02d-%02d", year, month, day);
      int i;
      return strtotime(NULL, strInternationalDate, 0, i);
   }

   int64_t datetime::strtotime(::user::str_context * pcontext, const char * psz, int iPath, int & iPathCount)
   {
      class time time;
      ::datetime::value val =::datetime::strtotime(get_app(), pcontext, psz, iPath, iPathCount);
      if(val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   int64_t datetime::strtotime(::user::str_context * pcontext, const char * psz, time_t timeParam, int iPath, int & iPathCount)
   {
      UNREFERENCED_PARAMETER(iPath);
      class time time(timeParam);
      iPathCount = 1;
      ::datetime::value val = ::datetime::value(time) +
         ::datetime::span_strtotime(get_app(), pcontext, psz);
      return val.get_time().get_time();
   }

   datetime::international::international(::ca::application * papp) :
      ca(papp)
   {
   }

   void datetime::international::parse_str(const char * psz, gen::property_set & set)
   {
        string src(psz);
      src.trim();
      string str;
      if(src.get_length() >= 4)
      {
         str = src.Mid(0, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"]    = 0;
      }
      if(src.get_length() >= 7)
      {
         str = src.Mid(5, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if(src.get_length() >= 10)
      {
         str = src.Mid(8, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if(src.get_length() >= 13)
      {
         str = src.Mid(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if(src.get_length() >= 16)
      {
         str = src.Mid(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if(src.get_length() >= 19)
      {
         str = src.Mid(17, 2);
         str.trim_left('0');
         set["second"]  = str;
      }
      else
      {
         set["second"]   = 0;
      }
   }


   string datetime::international::get_gmt_date_time(const class time & time)
   {
      string str;
      time.FormatGmt(str, "%Y-%m-%d %H:%M:%S");
      return str;
   }

   string datetime::international::get_gmt_date_time()
   {
      class time time;
      time = time.get_current_time();
      return get_gmt_date_time(time);
   }

   string datetime::international::get_local_date_time(const class time & time)
   {
      string str;
      time.Format(str, "%Y-%m-%d %H:%M:%S");
      return str;
   }

   string datetime::international::get_local_date_time()
   {
      class time time;
      time = time.get_current_time();
      return get_local_date_time(time);
   }

   datetime::str::str(::ca::application * papp)
   {
      UNREFERENCED_PARAMETER(papp);
      m_pdatetime = NULL;
   }

   string datetime::str::get_gmt_date_time()
   {
      return m_pdatetime->international().get_gmt_date_time(time::get_current_time());
   }

   time_t datetime::mktime(int iHour, int iMinute, int iSecond, int iMonth, int iDay, int iYear)
   {
      struct tm tm;
      memset(&tm, 0, sizeof(tm));
      tm.tm_hour  = iHour;
      tm.tm_min   = iMinute;
      tm.tm_sec   = iSecond;
      tm.tm_mon   = iMonth;
      tm.tm_mday  = iDay;
      tm.tm_year  = iYear;
      return _mktime64(&tm);
   }

   string datetime::get_week_day_str(user::str_context * pcontext, int iWeekDay) // 1 - domingo
   {
      return System.str().get(
         pcontext, 
         "datetimestr_weekday_long[" + gen::str::itoa(iWeekDay - 1) + "]",
         NULL,
         NULL);
   }

   string datetime::get_tiny_week_day_str(user::str_context * pcontext, int iWeekDay) // 1 - domingo
   {
      return System.str().get(
         pcontext, 
         "datetimestr_weekday_tiny[" + gen::str::itoa(iWeekDay - 1) + "]",
         NULL,
         NULL);
   }

   string datetime::get_month_str(user::str_context * pcontext, int iMonth)
   {
      return System.str().get(
         pcontext, 
         "datetimestr_month[" + gen::str::itoa(iMonth - 1) + "]",
         NULL,
         NULL);
   }

   class time datetime::from_gmt_date_time(int iYear, int iMonth, int iDay, int iHour, int iMinute, int iSecond)
   {
      class time timeLocalNow = time::get_current_time();
      tm tm;
      timeLocalNow.GetGmtTm(&tm);
      class time timeUTCNow = class time(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
      return class time(iYear, iMonth, iDay, iHour, iMinute, iSecond) + (timeUTCNow - timeLocalNow);
   }

} // namespace ca2