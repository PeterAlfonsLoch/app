#include "framework.h"

namespace datetime
{




   departament::departament(sp(base_application) papp) :
      element(papp),
      base_departament(papp),
      m_international(papp),
      m_str(papp)
   {
      m_str.m_pdatetime = this;
   }

   class departament::international & departament::international()
   {
      return m_international;
   }

   class departament::str & departament::str()
   {
      return m_str;
   }

   int32_t departament::get_month_day_count(int32_t year, int32_t month)
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
   int32_t departament::get_weekday(int32_t year, int32_t month, int32_t day)
   {
      ::datetime::time time(year, month, day, 0, 0, 0);
      return atoi(time.Format("%w"));
   }

   int64_t departament::get_timestamp(int32_t year, int32_t month, int32_t day)
   {
      string strInternationalDate;
      strInternationalDate.Format("%d-%02d-%02d", year, month, day);
      int32_t i;
      return strtotime(NULL, strInternationalDate, 0, i);
   }

   int64_t departament::strtotime(::user::str_context * pcontext, const char * psz, int32_t iPath, int32_t & iPathCount)
   {
      ::datetime::time time;
      ::datetime::value val =::datetime::strtotime(get_app(), pcontext, psz, iPath, iPathCount, false);
      if(val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   int64_t departament::strtotime(::user::str_context * pcontext, const char * psz, time_t timeParam, int32_t iPath, int32_t & iPathCount)
   {
      UNREFERENCED_PARAMETER(iPath);
      ::datetime::time time(timeParam);
      iPathCount = 1;
      ::datetime::value val = ::datetime::value(time) +
         ::datetime::span_strtotime(get_app(), pcontext, psz);
      return val.get_time().get_time();
   }

   int64_t departament::gmt_strtotime(::user::str_context * pcontext, const char * psz, int32_t iPath, int32_t & iPathCount)
   {
      ::datetime::time time;
      ::datetime::value val = ::datetime::strtotime(get_app(), pcontext, psz, iPath, iPathCount, true);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   departament::international::international(sp(base_application) papp) :
      element(papp)
   {
   }

   void departament::international::parse_str(const char * psz, property_set & set)
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


   string departament::international::get_gmt_date_time(const ::datetime::time & time)
   {
      string str;
      time.FormatGmt(str, "%Y-%m-%d %H:%M:%S");
      return str;
   }

   string departament::international::get_gmt_date_time()
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_gmt_date_time(time);
   }

   string departament::international::get_local_date_time(const ::datetime::time & time)
   {
      string str;
      time.Format(str, "%Y-%m-%d %H:%M:%S");
      return str;
   }

   string departament::international::get_local_date_time()
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_local_date_time(time);
   }

   departament::str::str(sp(base_application) papp)
   {
      UNREFERENCED_PARAMETER(papp);
      m_pdatetime = NULL;
   }

   string departament::str::get_gmt_date_time()
   {
      return m_pdatetime->international().get_gmt_date_time(::datetime::time::get_current_time());
   }

   time_t departament::mktime(int32_t iHour, int32_t iMinute, int32_t iSecond, int32_t iMonth, int32_t iDay, int32_t iYear)
   {
      struct tm tm;
      ZERO(tm);
      tm.tm_hour  = iHour;
      tm.tm_min   = iMinute;
      tm.tm_sec   = iSecond;
      tm.tm_mon   = iMonth - 1;
      tm.tm_mday  = iDay;
      tm.tm_year  = iYear - 1900;
      #ifdef WINDOWS
      return _mktime64(&tm);
      #else
      return ::mktime(&tm);
      #endif
   }

   string departament::get_week_day_str(user::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_long[" + ::str::from(iWeekDay - 1) + "]");
   }

   string departament::get_tiny_week_day_str(user::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_tiny[" + ::str::from(iWeekDay - 1) + "]");
   }

   string departament::get_month_str(user::str_context * pcontext, int32_t iMonth)
   {
      return System.str().get(pcontext, "datetimestr_month[" + ::str::from(iMonth - 1) + "]");
   }

   ::datetime::time departament::from_gmt_date_time(int32_t iYear, int32_t iMonth, int32_t iDay, int32_t iHour, int32_t iMinute, int32_t iSecond)
   {
      ::datetime::time timeLocalNow = ::datetime::time::get_current_time();
      struct tm tmLocalNow;
      timeLocalNow.GetGmtTm(&tmLocalNow);
      ::datetime::time timeUTCNow(tmLocalNow.tm_year + 1900, tmLocalNow.tm_mon + 1, tmLocalNow.tm_mday, tmLocalNow.tm_hour, tmLocalNow.tm_min, tmLocalNow.tm_sec);
      ::datetime::time timeUTC(tmLocalNow.tm_year + 1900, tmLocalNow.tm_mon + 1, tmLocalNow.tm_mday, tmLocalNow.tm_hour, tmLocalNow.tm_min, tmLocalNow.tm_sec);
      return timeUTC + (timeUTCNow - timeLocalNow);
   }


   /*
   and ML ("Month Length") is defined as:

       ML( y, 1 ) = 31
       ML( y, 2 ) = 28 + LEAP( y )
       ML( y, 3 ) = 31
       ML( y, 4 ) = 30
       ML( y, 5 ) = 31
       ML( y, 6 ) = 30
       ML( y, 7 ) = 31
       ML( y, 8 ) = 31
       ML( y, 9 ) = 30
       ML( y, 10 ) = 31
       ML( y, 11 ) = 30
       ML( y, 12 ) = 31

   and LEAP( y ) is defined as:

       LEAP( y ) = ( y % 4 == 0 ) && ( ( y % 100 != 0 ) || ( y % 400 == 0 ) ) */

   // simple week number
   //The simple week number we define such that
   //    week 1 starts on January 1st of a given year,
   //    week n+1 starts 7 days after week n
   int32_t departament::SWN(int32_t y, int32_t m, int32_t d )
   {
      return 1 + (DP( y, m ) + d-1 ) / 7;
   }

   //where DP ("Days Passed") is given by:
   //   DP( y, 1 ) = 0
   //  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
   int32_t departament::DP(int32_t y, int32_t m)
   {
      if(m == 1)
         return 0;
      else
         return DP(y, m - 1) + ML(y, m - 1);
   }

   int32_t departament::ML(int32_t y, int32_t m)
   {
      switch(m)
      {
      case 1:
         return 31;
      case 2:
         return 28 + LEAP(y);
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
         return 30;
      }
      throw invalid_argument_exception(get_app());
   }

   int32_t departament::LEAP(int32_t y )
   {
      if((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)))
         return 1;
      else
         return 0;
   }


   // Use this elegant code by Tomohiko Sakamoto:

   int32_t departament::dayofweek(int32_t y, int32_t m, int32_t d)	/* 0 = Sunday */
   {
	   static int32_t t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	   y -= m < 3;
	   return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
   }

   int32_t departament::SDOW(int32_t y,int32_t m, int32_t d ) // ( 0 = Monday, ..., 6 = Sunday )
   {
      return (DP( y, m ) + d-1 ) % 7;
   }


   int32_t departament::DOW(int32_t y, int32_t m, int32_t d)
   {
      //return SDOW(y, m, d);
      return getDayOfWeek(m, d, y, 0);
   }


int32_t departament::getDayOfWeek(int32_t month, int32_t day, int32_t year, int32_t CalendarSystem)
{
     // CalendarSystem = 1 for Gregorian Calendar
     if (month < 3)
     {
           month = month + 12;
           year = year - 1;
     }
     return (
             day
             + (2 * month)
             + int32_t(6 * (month + 1) / 10)
             + year
             + int32_t(year / 4)
             - int32_t(year / 100)
             + int32_t(year / 400)
             + CalendarSystem
            ) % 7;
}

   /*In [ISO8601], the week number is defined by:

       weeks start on a monday
       week 1 of a given year is the one that includes the first Thursday of that year. (or, equivalently, week 1 is the week that includes 4 January.)

   This means that the days before week 1 in a given year are attributed to the last week of the previous year. Also the days that come after the last week of a given year are attributed to the first week of the next year.

   If we adapt approximation SWN5 for the simple week number to reflect the differences between the definitions of both week numbers, we arrive at the final solution, adopted for the week number wristapp:
   */
   /*int32_t ISO_WN(int32_t  y, int32_t m, int32_t d, int32_t dow, int32_t dow0101 )
   {
       dow     = DOW( y, m, d );
       dow0101 = DOW( y, 1, 1 );

       if      ( m == 1  &&  3 < dow0101 < 7 - (d-1) )
       {
           // days before week 1 of the current year have the same week number as
           // the last day of the last week of the previous year

           dow     = dow0101 - 1;
           dow0101 = DOW( y-1, 1, 1 );
           m       = 12;
           d       = 31;
       }
       else if ( m == 12  &&  30 - (d-1) < DOW( y+1, 1, 1 ) < 4 )
       {
           // days after the last week of the current year have the same week number as
           // the first day of the next year, (i.e. 1)

           return 1;
       }

       return  ( DOW( y, 1, 1 ) < 4 ) + 4 * (m-1) + ( 2 * (m-1) + (d-1) + dow0101 - dow + 6 ) * 36 / 256;

   }*/


int32_t departament::ISO_WN(int32_t  y, int32_t m, int32_t d )
{
    int32_t dow     = DOW( y, m, d );
    int32_t dow0101 = DOW( y, 1, 1 );

    if      ( m == 1  &&  3 < dow0101 && dow0101 < (7 - (d-1)) )
    {
        // days before week 1 of the current year have the same week number as
        // the last day of the last week of the previous year

        dow     = dow0101 - 1;
        dow0101 = DOW( y-1, 1, 1 );
        m       = 12;
        d       = 31;
    }
    else if ( m == 12  &&  (30 - (d-1)) < DOW( y+1, 1, 1 ) &&  DOW( y+1, 1, 1 ) < 4 )
    {
        // days after the last week of the current year have the same week number as
        // the first day of the next year, (i.e. 1)

        return 1;
    }

    return ( dow0101 < 4 ) + 4 * (m-1) + ( 2 * (m-1) + (d-1) + dow0101 - dow + 6 ) * 36 / 256;

}


   string departament::strftime(const char * psz, time_t timeParam)
   {
      string strFormat(psz);
      string str;
      ::datetime::time time(timeParam);
      index iFind = strFormat.find("%V");
      if(iFind >= 0)
      {
         string strV;
         strV.Format("%02d", ISO_WN(time.GetYear(), time.GetMonth(), time.GetDay()));
         strFormat.replace("%V", strV);
      }
      time.FormatGmt(str, strFormat);
      return str;
   }

   string departament::strftime(const char * psz)
   {
      string str;
      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      time.FormatGmt(str, psz);
      return str;
   }

   string departament::friend_time(user::str_context * pcontext, ::datetime::time timeNow, ::datetime::time time)
   {
      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      __int64 iSecDiff = (timeNow - time).GetTotalSeconds();
      __int64 iMinDiff = (timeNow - time).GetTotalMinutes();
      __int64 iHouDiff = (timeNow - time).GetTotalHours();
      if (iSecDiff <= 59)
      {
         bSolved = true;
         strTime.Format("about %d seconds ago", (timeNow - time).GetTotalSeconds());
      }
      else if (iMinDiff <= 59)
      {
         bSolved = true;
         if (iMinDiff <= 1)
         {
            strTime = pcontext->get("about 1 minute and %SECONDS% seconds ago");
            strTime.replace("%SECONDS%", ::str::from((timeNow - time).GetSeconds()));
         }
         else if (iMinDiff <= 2)
         {
            strTime = pcontext->get("about 2 minutes and %SECONDS% seconds ago");
            strTime.replace("%SECONDS%", ::str::from((timeNow - time).GetSeconds()));
         }
         else
         {
            strTime = pcontext->get("about %MINUTES% minutes ago");
            strTime.replace("%MINUTES%", ::str::from(iMinDiff));
         }
      }
      else if (iHouDiff <= 24)
      {
         bSolved = true;
         if (iHouDiff <= 1)
         {
            strTime.Format("about 1 hour and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else if (iHouDiff <= 2)
         {
            strTime.Format("about 2 hours and %d minutes ago", (timeNow - time).GetMinutes());
         }
         else
         {
            strTime = pcontext->get("about %HOURS% hours ago");
            strTime.replace("%HOURS%", ::str::from(iHouDiff));
         }
      }
      else
      {
         if (!bSolved && timeNow.GetGmtYear() != time.GetGmtYear())
         {
            bDiff = true;
            str.Format("%04d", time.GetGmtYear());
            strTime = str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMonth() != time.GetGmtMonth()))
         {
            str = get_month_str(pcontext, time.GetGmtMonth());
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtDay() != time.GetGmtDay()))
         {
            str.Format("%02d", time.GetGmtDay());
            if (bDiff)
            {
               strTime += "-";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtHour() != time.GetGmtHour()))
         {
            str.Format("%02d", time.GetGmtHour());
            if (bDiff)
            {
               strTime += " ";
            }
            else
            {
               bDiff = true;
            }
            strTime += str;
         }
         if (!bSolved && (bDiff || timeNow.GetGmtMinute() != time.GetGmtMinute()))
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtMinute());
               strTime += ":";
               strTime += str;
            }
            else
            {
               bSolved = true;
               bDiff = true;
            }
         }
         if (!bDiff || !bSolved)
         {
            if (bDiff)
            {
               str.Format("%02d", time.GetGmtSecond());
               strTime += ":" + str;
            }
            else
            {
            }
         }
      }
      return strTime;
   }

} // namespace datetime
