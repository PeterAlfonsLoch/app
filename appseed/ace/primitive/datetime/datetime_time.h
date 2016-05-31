#pragma once


#ifdef ANDROID

struct tm;

#endif


namespace datetime
{



   class CLASS_DECL_AURA time
   {
   public:

#if defined(ANDROID) || defined(APPLEOS) || defined(SOLARIS)
      time_t         m_time;
#else
      __time64_t m_time;
#endif


      static time WINAPI get_current_time() NOTHROW;
      static bool WINAPI is_valid_FILETIME(const FILETIME& ft) NOTHROW;


      time() NOTHROW;
      time(__time64_t time) NOTHROW;
      time(int32_t nYear, int32_t nMonth, int32_t nDay, int32_t nHour, int32_t nMin, int32_t nSec, int32_t nDST = -1);
      time(WORD wDosDate, WORD wDosTime, int32_t nDST = -1);
      time(const SYSTEMTIME& st, int32_t nDST = -1);
      time(const FILETIME& ft, int32_t nDST = -1);


      time& operator=( __time64_t time ) NOTHROW;

      time& operator+=( date_span span );
      time& operator-=( date_span span );

      time& operator+=( time_span span ) NOTHROW;
      time& operator-=( time_span span ) NOTHROW;

      time& operator+=( const duration & span ) NOTHROW;
      time& operator-=( const duration & span ) NOTHROW;

      time_span operator-( time time ) const NOTHROW;
      time operator-( time_span span ) const NOTHROW;
      time operator+( time_span span ) const NOTHROW;

      time operator-( date_span span ) const;
      time operator+( date_span span ) const;

      time operator-(const duration & duration) const;
      time operator+(const duration & duration) const;

      bool operator==( time time ) const NOTHROW;
      bool operator!=( time time ) const NOTHROW;
      bool operator<( time time ) const NOTHROW;
      bool operator>( time time ) const NOTHROW;
      bool operator<=( time time ) const NOTHROW;
      bool operator>=( time time ) const NOTHROW;

      struct ::tm* GetGmtTm( struct ::tm* ptm ) const;
      struct ::tm* GetLocalTm( struct ::tm* ptm ) const;
      /*
      #if !_SECURE_TEMPLATE
      _INSECURE_DEPRECATE("Pass an output time structure to time::GetGmtTm")
      struct tm* GetGmtTm() const NOTHROW;
      _INSECURE_DEPRECATE("Pass an output time structure to time::GetLocalTm")
      struct tm* GetLocalTm() const NOTHROW;
      #endif
      */

      bool get_as_system_time( SYSTEMTIME& st ) const NOTHROW;

      __time64_t get_time() const NOTHROW;

      int32_t GetYear() const NOTHROW;
      int32_t GetMonth() const NOTHROW;
      int32_t GetDay() const NOTHROW;
      int32_t GetHour() const NOTHROW;
      int32_t GetMinute() const NOTHROW;
      int32_t GetSecond() const NOTHROW;
      int32_t GetDayOfWeek() const NOTHROW; // 1 = Sunday, 7 = Saturday

      int32_t GetGmtYear() const NOTHROW;
      int32_t GetGmtMonth() const NOTHROW;
      int32_t GetGmtDay() const NOTHROW;
      int32_t GetGmtHour() const NOTHROW;
      int32_t GetGmtMinute() const NOTHROW;
      int32_t GetGmtSecond() const NOTHROW;
      int32_t GetGmtDayOfWeek() const NOTHROW;

      string Format(string & str, const string & strFormat) const;
      string FormatGmt(string & str, const string & strFormat) const;
      string Format(const string & strFormat);
      string FormatGmt(const string & strFormat);

      time get_sunday() const;


      FILETIME to_file_time() const;
      SYSTEMTIME to_system_time() const;

   };





   enum _CTIMESPANFORMATSTEP
   {
      _CTFS_NONE   = 0,
      _CTFS_FORMAT = 1,
      _CTFS_NZ     = 2
   };
#define _CTIMESPANFORMATS 3



   inline string time::Format(const string & strFormat)
   {
      string str;
      Format(str, strFormat);
      return str;
   }
   inline string time::FormatGmt(const string & strFormat)
   {
      string str;
      FormatGmt(str, strFormat);
      return str;
   }




} // namespace datetime



CLASS_DECL_AURA dump_context & operator <<(dump_context & dumpcontext, ::datetime::time time);
CLASS_DECL_AURA dump_context & operator <<(dump_context & dumpcontext, ::datetime::time_span time);

CLASS_DECL_AURA ::file::ostream & operator <<(::file::ostream & os, ::datetime::time time);
CLASS_DECL_AURA ::file::istream & operator >>(::file::istream & is, ::datetime::time & time);


inline CLASS_DECL_AURA ::datetime::time_span operator - (const duration & duration, const ::datetime::time & time)
{

   return ::datetime::time_span(::datetime::time::get_current_time().m_time - duration.GetTimeSpan() - time.m_time);

}


inline CLASS_DECL_AURA ::datetime::time operator + (const duration & duration, const ::datetime::time & time)
{

   return ::datetime::time(duration.GetTimeSpan() + time.m_time);

}
