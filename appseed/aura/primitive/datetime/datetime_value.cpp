#include "framework.h"

#if defined(ANDROID) || defined(SOLARIS)

time_t
my_timegm(struct tm *tm)
{
   time_t ret;
   char *tz;

   tz = getenv("TZ");
   setenv("TZ", "", 1);
   tzset();
   ret = mktime(tm);
   if (tz)
      setenv("TZ", tz, 1);
   else
      unsetenv("TZ");
   tzset();
   return ret;
}


#endif

namespace datetime
{




   value::value(const ::datetime::time & time)
   {
      operator =(time);
   }

   value::value()
   {
      m_iYear     = 0;
      m_iMonth    = 0;

      m_iDay      = 0;
      m_iHour     = 0;
      m_iMinute   = 0;
      m_iSecond   = 0;

      m_bSpan     = false;

   }

   value::~value()
   {
   }

   double value::get_years() const
   {
      return m_iYear + m_iMonth / 12.0 +  (m_iDay + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0)) / 365.2425;
   }

   double value::get_months() const
   {
      return m_iYear / 12.0 + m_iMonth +  12.0 * (m_iDay + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0)) / 365.2425;
   }

   double value::get_days() const
   {
      return (m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) + (m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0) / 24.0);
   }

   double value::get_hours() const
   {
      return (m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24.0 + m_iHour +  (m_iMinute + (m_iSecond / 60.0) / 60.0);
   }

   double value::get_minutes() const
   {
      return (((m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24  + m_iHour) * 60.0) + m_iMinute + (m_iSecond / 60.0);
   }

   double value::get_seconds() const
   {
      return (((m_iYear * 365.2425 + m_iMonth * 365.2425 / 12.0 + m_iDay) * 24.0  + m_iHour) * 60.0 + m_iMinute) * 60.0 + m_iSecond;
   }

   ::datetime::time value::get_time() const
   {
      ASSERT(!m_bSpan);
      try
      {
         return ::datetime::time(m_iYear, m_iMonth, m_iDay, m_iHour, m_iMinute, m_iSecond);
      }
      catch(...)
      {
         return -1;
      }
   }

   ::datetime::time_span value::GetSpan() const
   {
      ASSERT(m_bSpan);
      return ::datetime::time_span((LONG) (m_iDay + m_iMonth * (365.0 * 4.0 + 1.0) /(12.0 *4.0) + m_iYear *(365.0 * 4.0 + 1.0) /(4.0)), m_iHour, m_iMinute, m_iSecond);
   }

   value & value::operator = (const ::datetime::time & time)
   {
      m_bSpan     = false;
      m_iYear     = time.GetYear();
      m_iMonth    = time.GetMonth();
      m_iDay      = time.GetDay();
      m_iHour     = time.GetHour();
      m_iMinute   = time.GetMinute();
      m_iSecond   = time.GetSecond();
      return *this;
   }

   string value::to_string(sp(::aura::application) pbaseapp, ::user::str_context * pcontext)
   {
      string str;
      if(m_bSpan)
      {
         stringa stra;
         string strItem;
         if(m_iYear != 0)
         {
            if(abs(m_iYear) == 1)
            {
               strItem.Format("%d year", m_iYear);
            }
            else
            {
               strItem.Format("%d years", m_iYear);
            }
            stra.add(strItem);
         }
         if(m_iMonth != 0)
         {
            if(abs(m_iMonth) == 1)
            {
               strItem.Format("%d month", m_iMonth);
            }
            else
            {
               strItem.Format("%d months", m_iMonth);
            }
            stra.add(strItem);
         }
         if(m_iDay != 0)
         {
            if(abs(m_iDay) == 1)
            {
               strItem.Format("%d day", m_iDay);
            }
            else
            {
               strItem.Format("%d days", m_iDay);
            }
            stra.add(strItem);
         }
         if(m_iHour != 0)
         {
            if(abs(m_iHour) == 1)
            {
               strItem.Format("%d hour", m_iHour);
            }
            else
            {
               strItem.Format("%d hours", m_iHour);
            }
            stra.add(strItem);
         }
         if(m_iMinute != 0)
         {
            if(abs(m_iMinute) == 1)
            {
               strItem.Format("%d minute", m_iMinute);
            }
            else
            {
               strItem.Format("%d minutes", m_iMinute);
            }
            stra.add(strItem);
         }
         if(m_iSecond != 0)
         {
            if(abs(m_iSecond) == 1)
            {
               strItem.Format("%d second", m_iSecond);
            }
            else
            {
               strItem.Format("%d seconds", m_iSecond);
            }
            stra.add(strItem);
         }
         if(stra.get_count() >= 2)
         {
            str = stra.implode(", ", 0, stra.get_count() - 1) + " and " + stra.last_element();
         }
         else if(stra.get_count() == 1)
         {
            str = stra[0];
         }
      }
      else
      {
         ::datetime::time time = get_time();
         if(time.GetSecond() == 0)
         {
            if(time.GetHour() == 0 && time.GetMinute() == 0)
            {
               str = time.Format("%Y-");
               Sys(pbaseapp->m_paurasystem).datetime().get_month_str(pcontext, time.GetMonth());
               str += time.Format("-%d");
            }
            else
            {
               str = time.Format("%Y-");
               str += Sys(pbaseapp->m_paurasystem).datetime().get_month_str(pcontext, time.GetMonth());
               str += time.Format("-%d %H:%M");
            }
         }
         else
         {
            str = time.Format("%Y-");
            str += Sys(pbaseapp->m_paurasystem).datetime().get_month_str(pcontext, time.GetMonth());
            str += time.Format("-%d %H:%M:%S");
         }
      }
      return str;
   }

} // namespace datetime


datetime::value operator + (const datetime::value & val1, const datetime::value & val2)
{
   datetime::value val;
   if(val1.m_bSpan && val2.m_bSpan)
   {
      val.m_bSpan = true;
      int32_t iTotalSecond = val1.m_iSecond + val2.m_iSecond;
      int32_t iTotalMinute = iTotalSecond / 60 + val1.m_iMinute + val2.m_iMinute;
      int32_t iTotalHour = iTotalMinute / 60 + val1.m_iHour + val2.m_iHour;
      int32_t iTotalDay = iTotalHour / 24 + val1.m_iDay + val2.m_iDay;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay;
      val.m_iMonth  = val1.m_iMonth + val2.m_iMonth;
      val.m_iYear   = val1.m_iYear + val2.m_iYear;
   }
   else if((val1.m_bSpan && !val2.m_bSpan) || (val2.m_bSpan && !val1.m_bSpan))
   {
      const datetime::value * pdate = NULL;
      const datetime::value * pspan = NULL;
      if(val1.m_bSpan)
      {
         pdate = &val2;
         pspan = &val1;
      }
      else
      {
         pdate = &val1;
         pspan = &val2;
      }
      val = ::datetime::time(pdate->get_time() + pspan->GetSpan());
   }
   else
   {
      throw "cannot add two dates";
   }
   return val;
}

datetime::value operator - (const datetime::value & val1, const datetime::value & val2)
{
   datetime::value val;
   if(val1.m_bSpan && val2.m_bSpan)
   {
      val.m_bSpan = true;
      int32_t iTotalSecond = val1.m_iSecond - val2.m_iSecond;
      int32_t iTotalMinute = iTotalSecond / 60 + val1.m_iMinute - val2.m_iMinute;
      int32_t iTotalHour = iTotalMinute / 60 + val1.m_iHour - val2.m_iHour;
      int32_t iTotalDay = iTotalHour / 24 + val1.m_iDay - val2.m_iDay;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay;
   }
   else if(val1.m_bSpan && !val2.m_bSpan)
   {
      throw "cannot subtract a date from a span";
   }
   else if(val2.m_bSpan && !val1.m_bSpan)
   {
      const datetime::value * pdate = &val1;
      const datetime::value * pspan = &val2;
      val = ::datetime::time(pdate->get_time() - pspan->GetSpan());
   }
   else
   {
      val.m_bSpan = true;
      int32_t iTotalSecond = val1.m_iSecond - val2.m_iSecond;
      int32_t iTotalMinute = iTotalSecond / 60 + val1.m_iMinute - val2.m_iMinute;
      int32_t iTotalHour = iTotalMinute / 60 + val1.m_iHour - val2.m_iHour;
      int32_t iTotalDay = iTotalHour / 24 + val1.m_iDay - val2.m_iDay;
      int32_t iTotalMonth = iTotalDay / 31 + val1.m_iMonth - val2.m_iMonth;
      int32_t iTotalYear = iTotalMonth / 12 + val1.m_iYear - val2.m_iYear;
      val.m_iSecond = iTotalSecond % 60;
      val.m_iMinute = iTotalMinute % 60;
      val.m_iHour   = iTotalHour % 24;
      val.m_iDay    = iTotalDay % 31;
      val.m_iMonth  = iTotalMonth % 12;
      val.m_iYear   = iTotalYear;
   }
   return val;
}

datetime::value operator * (const datetime::value & val1, double d)
{
   datetime::value val;
   if(val1.m_bSpan)
   {
      val.m_bSpan = true;
      double dTotalSecond
         = (val1.m_iSecond + (val1.m_iMinute + (val1.m_iHour + (val1.m_iDay * 24.0)) * 60.0) * 60.0) * d;
      double dTotalMinute = dTotalSecond / 60.0;
      double dTotalHour = dTotalMinute / 60.0;
      double dTotalDay = dTotalHour / 24.0;
      val.m_iSecond = (int32_t) fmod(dTotalSecond, 60.0);
      val.m_iMinute = (int32_t) fmod(dTotalMinute, 60.0);
      val.m_iHour   = (int32_t) fmod(dTotalHour, 24.0);
      val.m_iDay    = (int32_t) dTotalDay;
   }
   else
   {
      throw "cannot multiply a date";
   }
   return val;
}

datetime::value operator / (const datetime::value & val1, double d)
{
   datetime::value val;
   if(val1.m_bSpan)
   {
      val.m_bSpan = true;
      double dTotalSecond
         = (val1.m_iSecond
         + (val1.m_iMinute
         + (val1.m_iHour
         + (val1.m_iDay * 24.0)) * 60.0) * 60.0) / d;
      double dTotalMinute = dTotalSecond / 60.0;
      double dTotalHour = dTotalMinute / 60.0;
      double dTotalDay = dTotalHour / 24.0;
      val.m_iSecond = (int32_t) fmod(dTotalSecond, 60.0);
      val.m_iMinute = (int32_t) fmod(dTotalMinute, 60.0);
      val.m_iHour   = (int32_t) fmod(dTotalHour, 24.0);
      val.m_iDay    = (int32_t) dTotalDay;
   }
   else
   {
      throw "cannot multiply a date";
   }
   return val;
}


