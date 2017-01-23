
#include "framework.h" // from "base/aura/aura.h"
#include <time.h>
//#ifdef ANDROID
//#include <sys/time.h>
//#endif



namespace datetime
{

   ::datetime::time department::from(const string & str)
   {
      int iPathCount;
      return ::datetime::time(strtotime(Session.str_context(), str, 0, iPathCount));
   }


   department::department(::aura::application * papp) :
      object(papp),
      ::aura::department(papp),
      m_international(papp),
      m_str(papp)
   {

      m_pmutex = new mutex(papp);
      
      m_str.m_pdatetime = this;

      m_bInitialLocalityTimeZoneInit = false;

      //m_bInitialCountryTimeZoneInit = false;

   }


   class department::international & department::international()
   {

      return m_international;

   }


   class department::str & department::str()
   {
      return m_str;
   }

   int32_t department::get_month_day_count(int32_t year, int32_t month)
   {
      switch (month)
      {
      case 1:
         return 31;
      case 2:
         if ((year % 4) == 0)
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
   int32_t department::get_weekday(int32_t year, int32_t month, int32_t day)
   {
      ::datetime::time time(year, month, day, 0, 0, 0);
      return atoi(time.Format("%w"));
   }

   int64_t department::get_timestamp(int32_t year, int32_t month, int32_t day)
   {
      string strInternationalDate;
      strInternationalDate.Format("%d-%02d-%02d", year, month, day);
      int32_t i;
      return strtotime(NULL, strInternationalDate, 0, i);
   }

   int64_t department::strtotime(::aura::str_context * pcontext, const char * psz, int32_t iPath, int32_t & iPathCount)
   {
      ::datetime::time time;
      ::datetime::value val = ::datetime::strtotime(get_app(), pcontext, psz, iPath, iPathCount, false);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   int64_t department::strtotime(::aura::str_context * pcontext, const char * psz, time_t timeParam, int32_t iPath, int32_t & iPathCount)
   {
      UNREFERENCED_PARAMETER(iPath);
      ::datetime::time time(timeParam);
      iPathCount = 1;
      ::datetime::value val = ::datetime::value(time) +
         ::datetime::span_strtotime(get_app(), pcontext, psz);
      return val.get_time().get_time();
   }

   int64_t department::gmt_strtotime(::aura::str_context * pcontext, const char * psz, int32_t iPath, int32_t & iPathCount)
   {
      ::datetime::time time;
      ::datetime::value val = ::datetime::strtotime(get_app(), pcontext, psz, iPath, iPathCount, true);
      if (val.m_bSpan)
         time = time.get_current_time() + val.GetSpan();
      else
         time = val.get_time();
      return time.get_time();
   }

   department::international::international(::aura::application * papp) :
      object(papp)
   {
   }

   void department::international::parse_str(const char * psz, property_set & set)
   {
      string src(psz);
      src.trim();
      string str;
      if (src.get_length() >= 4)
      {
         str = src.Mid(0, 4);
         str.trim_left('0');
         set["year"] = str;
      }
      else
      {
         set["year"] = 0;
      }
      if (src.get_length() >= 7)
      {
         str = src.Mid(5, 2);
         str.trim_left('0');
         set["month"] = str;
      }
      else
      {
         set["month"] = 0;
      }
      if (src.get_length() >= 10)
      {
         str = src.Mid(8, 2);
         str.trim_left('0');
         set["day"] = str;
      }
      else
      {
         set["day"] = 0;
      }
      if (src.get_length() >= 13)
      {
         str = src.Mid(11, 2);
         str.trim_left('0');
         set["hour"] = str;
      }
      else
      {
         set["hour"] = 0;
      }
      if (src.get_length() >= 16)
      {
         str = src.Mid(14, 2);
         str.trim_left('0');
         set["minute"] = str;
      }
      else
      {
         set["minute"] = 0;
      }
      if (src.get_length() >= 19)
      {
         str = src.Mid(17, 2);
         str.trim_left('0');
         set["second"] = str;
      }
      else
      {
         set["second"] = 0;
      }
   }


   string department::international::get_gmt_date_time(const ::datetime::time & time, string strFormat)
   {
      string str;
      time.FormatGmt(str, strFormat);
      return str;
   }

   string department::international::get_gmt_date_time(string strFormat)
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_gmt_date_time(time);
   }

   string department::international::get_local_date_time(const ::datetime::time & time, string strFormat)
   {
      string str;
      time.Format(str, strFormat);
      return str;
   }

   string department::international::get_local_date_time(string strFormat)
   {
      ::datetime::time time;
      time = time.get_current_time();
      return get_local_date_time(time);
   }

   department::str::str(::aura::application * papp)
   {
      UNREFERENCED_PARAMETER(papp);
      m_pdatetime = NULL;
   }

   string department::str::get_gmt_date_time()
   {
      return m_pdatetime->international().get_gmt_date_time(::datetime::time::get_current_time());
   }

   time_t department::mktime(int32_t iHour, int32_t iMinute, int32_t iSecond, int32_t iMonth, int32_t iDay, int32_t iYear)
   {
      struct ::tm tm;
      ZERO(tm);
      tm.tm_hour = iHour;
      tm.tm_min = iMinute;
      tm.tm_sec = iSecond;
      tm.tm_mon = iMonth - 1;
      tm.tm_mday = iDay;
      tm.tm_year = iYear - 1900;
#ifdef WINDOWS
      return _mktime64(&tm);
#else
      return ::mktime(&tm);
#endif
   }

   string department::get_week_day_str(aura::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_long[" + ::str::from(iWeekDay - 1) + "]");
   }

   string department::get_tiny_week_day_str(aura::str_context * pcontext, int32_t iWeekDay) // 1 - domingo
   {
      return System.str().get(pcontext, "datetimestr_weekday_tiny[" + ::str::from(iWeekDay - 1) + "]");
   }

   string department::get_month_str(aura::str_context * pcontext, int32_t iMonth)
   {
      return System.str().get(pcontext, "datetimestr_month[" + ::str::from(iMonth - 1) + "]");
   }

   string department::get_short_month_str(aura::str_context * pcontext, int32_t iMonth)
   {
      return System.str().get(pcontext, "datetimestr_month_short[" + ::str::from(iMonth - 1) + "]");
   }

   ::datetime::time department::from_gmt_date_time(int32_t iYear, int32_t iMonth, int32_t iDay, int32_t iHour, int32_t iMinute, int32_t iSecond)
   {
      ::datetime::time timeLocalNow = ::datetime::time::get_current_time();
      struct ::tm tmLocalNow;
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
   int32_t department::SWN(int32_t y, int32_t m, int32_t d)
   {
      return 1 + (DP(y, m) + d - 1) / 7;
   }

   //where DP ("Days Passed") is given by:
   //   DP( y, 1 ) = 0
   //  DP( y, m+1 ) = DP( y, m ) + ML( y, m )
   int32_t department::DP(int32_t y, int32_t m)
   {
      if (m == 1)
         return 0;
      else
         return DP(y, m - 1) + ML(y, m - 1);
   }

   int32_t department::ML(int32_t y, int32_t m)
   {
      switch (m)
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

   int32_t department::LEAP(int32_t y)
   {
      if ((y % 4 == 0) && ((y % 100 != 0) || (y % 400 == 0)))
         return 1;
      else
         return 0;
   }


   // Use this elegant code by Tomohiko Sakamoto:

   int32_t department::dayofweek(int32_t y, int32_t m, int32_t d)	/* 0 = Sunday */
   {
      static int32_t t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };
      y -= m < 3;
      return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
   }

   int32_t department::SDOW(int32_t y, int32_t m, int32_t d) // ( 0 = Monday, ..., 6 = Sunday )
   {
      return (DP(y, m) + d - 1) % 7;
   }


   int32_t department::DOW(int32_t y, int32_t m, int32_t d)
   {
      //return SDOW(y, m, d);
      return getDayOfWeek(m, d, y, 0);
   }


   int32_t department::getDayOfWeek(int32_t month, int32_t day, int32_t year, int32_t CalendarSystem)
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


   int32_t department::ISO_WN(int32_t  y, int32_t m, int32_t d)
   {
      int32_t dow = DOW(y, m, d);
      int32_t dow0101 = DOW(y, 1, 1);

      if (m == 1 && 3 < dow0101 && dow0101 < (7 - (d - 1)))
      {
         // days before week 1 of the current year have the same week number as
         // the last day of the last week of the previous year

         dow = dow0101 - 1;
         dow0101 = DOW(y - 1, 1, 1);
         m = 12;
         d = 31;
      }
      else if (m == 12 && (30 - (d - 1)) < DOW(y + 1, 1, 1) && DOW(y + 1, 1, 1) < 4)
      {
         // days after the last week of the current year have the same week number as
         // the first day of the next year, (i.e. 1)

         return 1;
      }

      return (dow0101 < 4) + 4 * (m - 1) + (2 * (m - 1) + (d - 1) + dow0101 - dow + 6) * 36 / 256;

   }


   string department::strftime(const char * psz, time_t timeParam)
   {
      string strFormat(psz);
      string str;
      ::datetime::time time(timeParam);
      index iFind = strFormat.find("%V");
      if (iFind >= 0)
      {
         string strV;
         strV.Format("%02d", ISO_WN(time.GetYear(), time.GetMonth(), time.GetDay()));
         strFormat.replace("%V", strV);
      }
      time.FormatGmt(str, strFormat);
      return str;
   }

   string department::strftime(const char * psz)
   {
      string str;
      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      time.FormatGmt(str, psz);
      return str;
   }

   string department::friend_time(aura::str_context * pcontext, ::datetime::time timeNow, ::datetime::time time)
   {
      bool bDiff = false;
      bool bSolved = false;
      string strTime;
      string str;
      int64_t iSecDiff = (timeNow - time).GetTotalSeconds();
      int64_t iMinDiff = (timeNow - time).GetTotalMinutes();
      int64_t iHouDiff = (timeNow - time).GetTotalHours();
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

   
   bool department::locality_sunset(openweather_city * pcity, int & iRise, int & iSet)
   {

      if (pcity == NULL)
      {

         return false;

      }

#include "sensitive/openweather.txt"

      double dZone = 0.0;

      System.datetime().initial_locality_time_zone(pcity, dZone);

      int iTimeZone = (int)(dZone * 3600.0);

      property_set set;

      string strUrl = "http://api.openweathermap.org/data/2.5/weather?id=" + ::str::from(pcity->m_iId) + "&APPID=" + string(pszId);

      string strGetUrl = "https://api.ca2.cc/account/openweather?sessid=" + Session.fontopus_get_user_sessid("api.ca2.cc")
         + "&request=" + System.url_encode(strUrl);

      string str = Application.http_get(strGetUrl, set);

      synch_lock sl(m_pmutex);

      const char * pszJson = str;

      var v;

      v.parse_json(pszJson);

      ::datetime::zonetime timeSunrise(v["sys"]["sunrise"].int64(), iTimeZone);

      ::datetime::zonetime timeSunset(v["sys"]["sunset"].int64(), iTimeZone);

      iRise = timeSunrise.GetZoneTimeOfDay();

      iSet = timeSunset.GetZoneTimeOfDay();

      string strSunrise(timeSunrise.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      string strSunset(timeSunset.FormatZone(INTERNATIONAL_DATE_TIME_FORMAT));

      output_debug_string("sunrise:" + strSunrise + "\n");

      output_debug_string("sunset:" + strSunset + "\n");

      return true;

   }


   bool  department::locality_sunset(string strCountry, string strLocality, int & iRise, int & iSet)
   {

      auto pcity = System.openweather_find_city(strLocality + ", " + strCountry);

      if (pcity == NULL)
      {

         return false;

      }

      return locality_sunset(pcity, iRise, iSet);


   }


   string department::initial_locality_time_zone(openweather_city * pcity, double & dZone)
   {

      if (pcity == NULL)
      {

         dZone = 0.0;

         return "utc";

      }

      class time_zone timezone;

      ::datetime::time_span spanTimeout(1, 0, 0, 0);

      ::datetime::time now = ::datetime::time::get_current_time();

      mutex m(get_app(), false, "Global\\ca2_datetime_departament");

      {

         synch_lock sl(&m);

         if (!m_bInitialLocalityTimeZoneInit)
         {

            m_bInitialLocalityTimeZoneInit = true;

            {

               ::file::path path = ::dir::public_system() / "datetime_departament_cityTimeZone.bin";

               auto & file = Application.file().friendly_get_file(path, ::file::type_binary | ::file::mode_read);

               if (file.is_set())
               {

                  ::file::byte_istream is(file);

                  is >> m_cityTimeZone;

               }

            }

         }

         if (m_cityTimeZone.Lookup(pcity->m_iId, timezone) && (now - timezone.m_time) < spanTimeout)
         {

            dZone = timezone.m_dZone;

            return timezone.m_strZone;

         }

      }


      property_set set;

      string strLat = ::str::from(pcity->m_dLat);

      string strLng = ::str::from(pcity->m_dLon);

      string strKey;

#ifdef WINDOWS

      strKey = file_as_string_dup("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");

#else

      strKey = file_as_string_dup("/sensitive/sensitive/seed/timezonedb.txt");

#endif

      string str = Application.http_get("http://api.timezonedb.com/?key=" + strKey + "&format=json&lat=" + strLat + "&lng=" + strLng, set);

      if (str.has_char())
      {

         const char * pszJson = str;

         var v;

         try
         {

            v.parse_json(pszJson);

            str = v["abbreviation"].get_string().lowered();

            dZone = v["gmtoffset"].get_double() / 3600.0;

         }
         catch (...)
         {

            str = "utc";

            dZone = 0.0;

         }

      }
      else
      {

         str = "utc";

         dZone = 0.0;

      }

      timezone.m_strZone = str;

      timezone.m_dZone = dZone;

      timezone.m_time = now;

      {

         synch_lock sl(&m);

         m_cityTimeZone[pcity->m_iId] = timezone;

         ::file::path path = ::dir::public_system() / "datetime_departament_cityTimeZone.bin";

         auto & file = Application.file().friendly_get_file(path, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::defer_create_directory);

         ::file::byte_ostream os(file);

         os << m_cityTimeZone;

      }

      return str;

   }


   string  department::initial_locality_time_zone(string strCountry, string strLocality, double & dZone)
   {

      string str;

      if (strLocality.is_empty())
      {

         str = initial_country_time_zone(strCountry);

         dZone = time_zone(str, strCountry);

         return str;

      }

      string strQ;

      strQ = strLocality;

      if (strCountry.has_char())
      {

         strQ += ", ";

         strQ += strCountry;

      }


      int64_t iId;

      double dLat;

      double dLon;

      auto pcity = System.openweather_find_city(strQ);

      return initial_locality_time_zone(pcity, dZone);

//      if (pcity != NULL)
//      {
//
//
//
//         property_set set;
//
//         string strLat = ::str::from(pcity->m_dLat);
//
//         string strLng = ::str::from(pcity->m_dLon);
//
//         string strKey;
//
//#ifdef WINDOWS
//
//         strKey = file_as_string_dup("C:\\sensitive\\sensitive\\seed\\timezonedb.txt");
//
//#else
//
//         strKey = file_as_string_dup("/sensitive/sensitive/seed/timezonedb.txt");
//
//#endif
//
//         str = Application.http_get("http://api.timezonedb.com/?key=" + strKey + "&format=json&lat=" + strLat + "&lng=" + strLng, set);
//
//         if (str.has_char())
//         {
//
//            const char * pszJson = str;
//
//            var v;
//
//            try
//            {
//
//               v.parse_json(pszJson);
//
//               str = v["abbreviation"].get_string().lowered();
//
//               dZone = v["gmtoffset"].get_double() / 3600.0;
//
//            }
//            catch (...)
//            {
//
//               str = "utc";
//
//               dZone = 0.0;
//
//            }
//
//         }
//         else
//         {
//
//            str = "utc";
//
//            dZone = 0.0;
//
//         }
//
//      }
//      else
//      {
//
//         str = "utc";
//
//         dZone = 0.0;
//
//      }
//
//
//      timezone.m_strZone = str;
//
//      timezone.m_dZone = dZone;
//
//      timezone.m_time = now;
//
//      {
//
//         synch_lock sl(&m);
//
//         m_countryLocalityTimeZone[strCountry][strLocality] = timezone;
//
//         ::file::path path = ::dir::public_system() / "datetime_departament_m_countryLocalityTimeZone.bin";
//
//         auto & file = Application.file().friendly_get_file(path, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::defer_create_directory);
//
//         ::file::byte_ostream os(file);
//
//         ::file::map::write(os, m_countryLocalityTimeZone);
//
//      }
//
//      return str;

   }

   // remark: initial does mean "official default" is certainly a rough guess
   string  department::initial_country_time_zone(string strCountry)
   {




      if (strCountry == "br")
      {

         return "brt";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "us")
      {

         return "pdt";

      }
      else if (strCountry == "jp")
      {

         return "jst";

      }
      else if (strCountry == "de")
      {

         return "cest";

      }
      else if (strCountry == "fr")
      {

         return "cest";

      }
      else if (strCountry == "pt")
      {

         return "west";

      }
      else if (strCountry == "es")
      {

         return "cest";

      }
      else if (strCountry == "it")
      {

         return "cest";

      }
      else if (strCountry == "ar")
      {

         return "art";

      }
      else if (strCountry == "cl")
      {

         return "clst";

      }
      else if (strCountry == "uk")
      {

         return "bst";

      }
      else if (strCountry == "nl")
      {

         return "cest";

      }
      else if (strCountry == "cn")
      {

         return "cst";

      }
      else if (strCountry == "tw")
      {

         return "cst";

      }
      else if (strCountry == "ru")
      {

         return "msk";

      }
      else if (strCountry == "pl")
      {

         return "cest";

      }
      else if (strCountry == "am")
      {

         return "amt";

      }
      else if (strCountry == "dk")
      {

         return "cest";

      }
      else if (strCountry == "se")
      {

         return "cest";

      }
      else if (strCountry == "fi")
      {

         return "eest";

      }
      else if (strCountry == "ua")
      {

         return "eest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "no")
      {

         return "cest";

      }
      else if (strCountry == "be")
      {

         return "cest";

      }
      else if (strCountry == "at")
      {

         return "cest";

      }
      else if (strCountry == "lu")
      {

         return "cest";

      }
      else if (strCountry == "li")
      {

         return "cest";

      }
      else if (strCountry == "ch")
      {

         return "cest";

      }
      else if (strCountry == "au")
      {

         return "aest";

      }
      else if (strCountry == "nz")
      {

         return "nzst";

      }
      else if (strCountry == "kr")
      {

         return "kst";

      }
      else if (strCountry == "ph")
      {

         return "pht";

      }
      else if (strCountry == "my")
      {

         return "myt";

      }
      else if (strCountry == "hk")
      {

         return "hkt";

      }
      else if (strCountry == "vn")
      {

         return "ict";

      }
      else if (strCountry == "in")
      {

         return "ist";

      }
      else if (strCountry == "ca")
      {

         return "adt";

      }
      else if (strCountry == "bg")
      {

         return "eet";

      }
      else
      {

         return "utc";

      }

   }



   bool utc_offset_invalid(double dUTCOffset);


   string department::utc_offset_string(double dUTCOffset)
   {

      if (dUTCOffset == 1000000.0)
      {

         return "";

      }
      else if (dUTCOffset == 0.0)
      {

         return "UTC";

      }
      else if (utc_offset_invalid(dUTCOffset))
      {

         return "(" + ::str::signed_double(dUTCOffset) + " : invalid UTC?)";

      }
      else
      {

         string strUTCOffset;

         strUTCOffset = "UTC " + ::str::signed_int(dUTCOffset);

         double dMod = fmod(fabs(dUTCOffset), 1.0);

         if (dMod > 0.0)
         {

            string strMinutes;

            strMinutes.Format("%02d", (int)(60.0 * dMod));

            strUTCOffset += ":" + strMinutes;

         }

         return strUTCOffset;

      }

   }


   double department::time_zone(string str, string strCountryCode)
   {
      str.make_lower();
      strCountryCode.make_lower();
      //Московское время (UTC+3)
      if (str == "msk")
      {

         return 3.0;

      }
      else if (str == "brt")
      {

         return -3.0;

      }
      else if (str == "cet")
      {

         return 1.0;

      }
      else if (str == "cest")
      {

         return 2.0;

      }
      else if (str == "eet")
      {

         return 2.0;

      }
      else if (str == "eest")
      {

         return 3.0;

      }
      else if (str == "pdt")
      {

         return -7.0;

      }
      else if (str == "est")
      {

         return -5.0;

      }
      else if (str == "edt")
      {

         return -4.0;

      }
      else if (str == "jst")
      {

         return 9.0;

      }
      else if (str == "west")
      {

         return 1.0;

      }
      else if (str == "art")
      {

         return -3.0;

      }
      else if (str == "clst")
      {

         return -3.0;

      }
      else if (str == "bst")
      {

         return 1.0;

      }
      else if (str == "cdt")
      {

         return -5.0;

      }
      else if (str == "cst")
      {

         if (strCountryCode == "cn")
         {
            return 8.0;
         }
         else
         {
            return -6.0;
         }

      }
      else if (str == "amt")
      {

         return 4.0;

      }
      else if (str == "aest")
      {

         return 10.0;

      }
      else if (str == "nzst")
      {

         return 12.0;

      }
      else if (str == "kst")
      {

         return 9.0;

      }
      else if (str == "pht")
      {

         return 8.0;

      }
      else if (str == "myt")
      {

         return 8.0;

      }
      else if (str == "hkt")
      {

         return 8.0;

      }
      else if (str == "ict")
      {

         return 7.0;

      }
      else if (str == "utc")
      {

         return 0.0;

      }
      else if (str == "alphatime")
      {

         return -2.0;

      }
      else if (str == "ist")
      {

         return 5.5;

      }
      else if (str == "adt")
      {

         return -3.0;

      }
      else if (str == "brst")
      {

         return -2.0;

      }
      else
      {

         TRACE("ERROR !! Missing timezone offset information for \"%s\" - \"%s\"", str, strCountryCode);

         return 0.0;

      }

   }


} // namespace datetime





CLASS_DECL_AURA file::istream &operator >> (file::istream & is, class ::datetime::department::time_zone & z)
{

   is >> z.m_strZone;
   is >> z.m_dZone;
   is >> z.m_time;

   return is;
}

CLASS_DECL_AURA file::ostream &operator << (file::ostream & os, const class ::datetime::department::time_zone & z)
{

   os << z.m_strZone;
   os << z.m_dZone;
   os << z.m_time;

   return os;
}

CLASS_DECL_AURA file::istream &operator >> (file::istream & is, string_map < class ::datetime::department::time_zone > & m)
{

   ::file::map::read(is, m);

   return is;

}

CLASS_DECL_AURA ::file::ostream &operator << (file::ostream & os, const string_map < class ::datetime::department::time_zone > & m)
{

   ::file::map::write(os, m);

   return os;

}

CLASS_DECL_AURA file::istream &operator >> (file::istream & is, int_ptr_map < class ::datetime::department::time_zone > & m)
{

   ::file::map::read(is, m);

   return is;

}

CLASS_DECL_AURA::file::ostream &operator << (file::ostream & os, const int_ptr_map < class ::datetime::department::time_zone > & m)
{

   ::file::map::write(os, m);

   return os;

}

