#include "StdAfx.h"
#include "whiteboard.h"
#include "time.h"

namespace whiteboard
{

   time::time()
   {
      m_iYear = 1980;
      m_iMonth = 1;
      m_iDay = 1;
      m_iHour = 0;
      m_iMinute = 0;
      m_iSecond = 0;
   }

   time::~time()
   {

   }

   void time::ToString(string &str) const
   {
      str.Format(
         "%d-%d-%d-%d-%d-%d",
         m_iYear,
         m_iMonth,
         m_iDay,
         m_iHour,
         m_iMinute,
         m_iSecond);
   }

   void time::TimeToString(string &str) const
   {
      str.Format(
         "%02d:%02d:%02d",
         m_iHour,
         m_iMinute,
         m_iSecond);
   }
   void time::HourMinuteToString(string &str) const
   {
      str.Format(
         "%02d:%02d",
         m_iHour,
         m_iMinute);
   }

   bool time::FromString(const char * lpcsz)
   {
      if(sscanf(
            lpcsz,
            "%d-%d-%d-%d-%d-%d",
            &m_iYear,
            &m_iMonth,
            &m_iDay,
            &m_iHour,
            &m_iMinute, 
            &m_iSecond) == 6)
         return true;
      else
         return false;
   }


   bool time::operator >(const time & time) const
   {
      if(m_iYear > time.m_iYear)
         return true;
      else if(m_iYear == time.m_iYear)
      {
         if(m_iMonth > time.m_iMonth)
            return true;
         else if(m_iMonth == time.m_iMonth)
         {
            if(m_iDay > time.m_iDay)
               return true;
            else if(m_iDay == time.m_iDay)
            {
               if(m_iHour > time.m_iHour)
                  return true;
               else if(m_iHour == time.m_iHour)
               {
                  if(m_iMinute > time.m_iMinute)
                     return true;
                  else if(m_iMinute == time.m_iMinute)
                  {
                     if(m_iSecond > time.m_iSecond)
                        return true;
                     else if(m_iSecond == time.m_iSecond)
                     {
                        return false;
                     }
                     else
                        return false;
                  }
                  else
                     return false;
               }
               else
                  return false;
            }
            else
               return false;
         }
         else
            return false;
      }
      else
         return false;
   }

   bool time::operator <(const time & time) const
   {
      if(m_iYear < time.m_iYear)
         return true;
      else if(m_iYear == time.m_iYear)
      {
         if(m_iMonth < time.m_iMonth)
            return true;
         else if(m_iMonth == time.m_iMonth)
         {
            if(m_iDay < time.m_iDay)
               return true;
            else if(m_iDay == time.m_iDay)
            {
               if(m_iHour < time.m_iHour)
                  return true;
               else if(m_iHour == time.m_iHour)
               {
                  if(m_iMinute < time.m_iMinute)
                     return true;
                  else if(m_iMinute == time.m_iMinute)
                  {
                     if(m_iSecond < time.m_iSecond)
                        return true;
                     else if(m_iSecond == time.m_iSecond)
                     {
                        return false;
                     }
                     else
                        return false;
                  }
                  else
                     return false;
               }
               else
                  return false;
            }
            else
               return false;
         }
         else
            return false;
      }
      else
         return false;
   }

   void time::Min(const time & time1, const time & time2)
   {
      if(time1 > time2)
         *this = time2;
      else
         *this = time1;
   }

   void time::Max(const time & time1, const time & time2)
   {
      if(time1 > time2)
         *this = time1;
      else
         *this = time2;
   }


   void time::xml_export(xml::output_tree & xmlot)
   {
      xmlot.set_attr("year", m_iYear);
      xmlot.set_attr("month", m_iMonth);
      xmlot.set_attr("day", m_iDay);
      xmlot.set_attr("hour", m_iHour);
      xmlot.set_attr("minute", m_iMinute);
      xmlot.set_attr("second", m_iSecond);
   }
   void time::xml_import(xml::input_tree & xmlit)
   {
      xmlit.get_attr("year", m_iYear);
      xmlit.get_attr("month", m_iMonth);
      xmlit.get_attr("day", m_iDay);
      xmlit.get_attr("hour", m_iHour);
      xmlit.get_attr("minute", m_iMinute);
      xmlit.get_attr("second", m_iSecond);
   }


   void time::Now()
   {
      class ::time time = ::time::get_current_time();
      m_iYear     = time.GetYear();
      m_iMonth    = time.GetMonth();
      m_iDay      = time.GetDay();
      m_iHour     = time.GetHour();
      m_iMinute   = time.GetMinute();
      m_iSecond   = time.GetSecond();
   }

   void time::SetTime(__time64_t time64)
   {
      SYSTEMTIME stUTC;
      FileTimeToSystemTime(
         (const FILETIME*) &time64,
         &stUTC);

      SYSTEMTIME stLocal;
      SystemTimeToTzSpecificLocalTime(
         NULL, &stUTC, &stLocal);

      class ::time time(stLocal);
      SetTime(time);
   }

   void time::SetTime(class ::time & time)
   {
      m_iDay      = time.GetDay();
      m_iMonth    = time.GetMonth();
      m_iYear     = time.GetYear();
      m_iMinute   = time.GetMinute();
      m_iHour     = time.GetHour();
      m_iSecond   = time.GetSecond();
   }

} // namespace whiteboard
