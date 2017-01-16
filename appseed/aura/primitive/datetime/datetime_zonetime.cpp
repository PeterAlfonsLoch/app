#include "framework.h"


namespace datetime
{


   ::datetime::zonetime WINAPI zonetime::get_current_time(int iZoneOffset) throw()
   {

      zonetime t;

#ifdef WINDOWS

      t.m_time = ::_time64(NULL);

#else

      t.m_time = ::time(NULL);

#endif

      t.m_iZoneOffset = iZoneOffset;

      return t;

   }

   zonetime::zonetime() throw() :
      time(0),
      m_iZoneOffset(0)
   {

   }

   
   zonetime::zonetime(const zonetime & zonetime) throw() :
      time(zonetime.m_time),
      m_iZoneOffset(zonetime.m_iZoneOffset)
   {


   }


   zonetime::zonetime(__time64_t zonetime, int iZoneOffset) throw() :
      time(zonetime),
      m_iZoneOffset(iZoneOffset)
   {
   }

   zonetime::zonetime(int32_t nYear, int32_t nMonth, int32_t nDay, int32_t nHour, int32_t nMin, int32_t nSec, int32_t iZoneOffset)
   {
#pragma warning (push)
#pragma warning (disable: 4127)  // conditional expression constant


#pragma warning (pop)

      struct tm atm;

      atm.tm_sec = nSec;
      atm.tm_min = nMin;
      atm.tm_hour = nHour;
      atm.tm_mday = nDay;
      atm.tm_mon = nMonth - 1;        // tm_mon is 0 based
      atm.tm_year = nYear - 1900;     // tm_year is 1900 based
      atm.tm_isdst = 0;

#ifdef WINDOWS

      m_time = _mkgmtime64(&atm);

#else

      m_time = mkgmtime(&atm);

#endif

      /*
      Remember that:
      ENSURE( nYear >= 1900 );
      ENSURE( nMonth >= 1 && nMonth <= 12 );
      ENSURE( nDay >= 1 && nDay <= 31 );
      ENSURE( nHour >= 0 && nHour <= 23 );
      ENSURE( nMin >= 0 && nMin <= 59 );
      ENSURE( nSec >= 0 && nSec <= 59 );
      ASSUME(m_time != -1);   */    // indicates an illegal input zonetime
      if (m_time == -1)
      {
         throw invalid_argument_exception(get_thread_app());
      }
   }





   struct tm* zonetime::GetZoneTm(struct tm* ptm) const
   {

      if (ptm != NULL)
      {


#ifdef WINDOWS

         struct tm tmTemp;

         __time64_t t = m_time;

         t += m_iZoneOffset;

         errno_t err = _gmtime64_s(&tmTemp, &t);

         if (err != 0)
         {
            return NULL;    // indicates that m_time was not initialized!
         }

         *ptm = tmTemp;

         return ptm;

#else

         struct tm * ptmTemp;


         time_t t = m_time;

         t += m_iZoneOffset;

         ptmTemp = gmtime(&y);

         // gmtime can return NULL
         if (ptmTemp == NULL)
            return NULL;

         // but don't throw exception or generate error...
         // (reason for commenting out below, fat to be removed...)
         //         if(errno != 0)
         //          return NULL;

         *ptm = *ptmTemp;

         return ptm;

#endif

      }
      else
      {

         return NULL;

      }


   }


   int32_t zonetime::GetZoneYear() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? (ptm->tm_year) + 1900 : 0;
   }

   int32_t zonetime::GetZoneMonth() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_mon + 1 : 0;
   }

   int32_t zonetime::GetZoneDay() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_mday : 0;
   }

   int32_t zonetime::GetZoneHour() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_hour : -1;
   }

   int32_t zonetime::GetZoneMinute() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_min : -1;
   }

   int32_t zonetime::GetZoneSecond() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_sec : -1;
   }

   int32_t zonetime::GetZoneDayOfWeek() const NOTHROW
   {
      struct tm ttm;
      struct tm * ptm;

      ptm = GetZoneTm(&ttm);
      return ptm ? ptm->tm_wday + 1 : 0;
   }


   string zonetime::FormatZone(string & str, const string & strFormat) const
   {

      str = strFormat;

      str.replace("%Y", ::str::from(GetZoneYear()));
      str.replace("%m", ::str::zero_pad(::str::from(GetZoneMonth()), 2));
      str.replace("%d", ::str::zero_pad(::str::from(GetZoneDay()), 2));
      str.replace("%H", ::str::zero_pad(::str::from(GetZoneHour()), 2));
      str.replace("%M", ::str::zero_pad(::str::from(GetZoneMinute()), 2));
      str.replace("%S", ::str::zero_pad(::str::from(GetZoneSecond()), 2));

      return str;

   }


   __time64_t zonetime::GetZoneTimeOfDay() const NOTHROW
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ((ptm->tm_hour * 3600) + (ptm->tm_min * 60) + ptm->tm_sec) : 0;

   }


   int64_t zonetime::GetZoneDaySig() const NOTHROW
   {

      struct tm ttm;

      struct tm * ptm;

      ptm = GetZoneTm(&ttm);

      return ptm ? ((ptm->tm_year * 500) + (ptm->tm_mon * 40) + ptm->tm_mday) : 0;

   }

} // namespace datetime



dump_context & operator <<(dump_context & dumpcontext, ::datetime::zonetime zonetime)
{
   char psz[32];
   psz[0] = '\0';

   //   __time64_t tmp = zonetime.get_time();
   //   errno_t err = _ctime64_s(psz, sizeof(psz), &tmp);

   errno_t err = 0;

   if ((err != 0) || (psz[0] == '\0') || (zonetime.get_time() == 0))
   {
      return dumpcontext << "::datetime::zonetime(invalid #" << (int_ptr)zonetime.get_time() << ")";
   }

   // format it
   return dumpcontext << "::datetime::zonetime(\"" << psz << "\")";
}


::file::ostream & operator <<(::file::ostream & os, ::datetime::zonetime zonetime)
{

   os.write_arbitrary((int64_t)zonetime.m_time);
   os.write_arbitrary((int32_t)zonetime.m_iZoneOffset);

   return os;

}

::file::istream & operator >> (::file::istream & is, ::datetime::zonetime& rtime)
{

   is.read_arbitrary((int64_t &)rtime.m_time);
   is.read_arbitrary((int32_t &)rtime.m_iZoneOffset);

   return is;

}






