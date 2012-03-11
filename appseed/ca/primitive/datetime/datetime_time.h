#pragma once

#include "ca/template/template_definition.h"
#include "ca/primitive/primitive_string.h"

class CLASS_DECL_ca date_span
{
public:
   date_span();
   int m_iMonth;
   int m_iYear;
   bool m_bConstraintMonth;
};

class CLASS_DECL_ca time_span
{
public:
   time_span() NOTHROW;
   time_span( __time64_t time ) NOTHROW;
   time_span( LONG lDays, int nHours, int nMins, int nSecs ) NOTHROW;

   LONGLONG GetDays() const NOTHROW;
   LONGLONG GetTotalHours() const NOTHROW;
   LONG GetHours() const NOTHROW;
   LONGLONG GetTotalMinutes() const NOTHROW;
   LONG GetMinutes() const NOTHROW;
   LONGLONG GetTotalSeconds() const NOTHROW;
   LONG GetSeconds() const NOTHROW;

   __time64_t GetTimeSpan() const NOTHROW;

   time_span operator+( time_span span ) const NOTHROW;
   time_span operator-( time_span span ) const NOTHROW;
   time_span& operator+=( time_span span ) NOTHROW;
   time_span& operator-=( time_span span ) NOTHROW;
   bool operator==( time_span span ) const NOTHROW;
   bool operator!=( time_span span ) const NOTHROW;
   bool operator<( time_span span ) const NOTHROW;
   bool operator>( time_span span ) const NOTHROW;
   bool operator<=( time_span span ) const NOTHROW;
   bool operator>=( time_span span ) const NOTHROW;

public:
   string Format( const char * pszFormat ) const;
   //string Format( UINT nID ) const;
#if defined(_AFX) && defined(_UNICODE)
   // for compatibility with ca2 API 3.x
   string Format(const char * pFormat) const;
#endif

#ifdef _AFX
//   CArchive& Serialize64(CArchive& ar);
#endif

private:
   __time64_t m_timeSpan;
};

class CLASS_DECL_ca time
{
private:

   __time64_t m_time;

public:
   static time WINAPI get_current_time() NOTHROW;
   static BOOL WINAPI is_valid_FILETIME(const FILETIME& ft) NOTHROW;

   time() NOTHROW;
   time( __time64_t time ) NOTHROW;
   time( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec,
      int nDST = -1 );
   time( WORD wDosDate, WORD wDosTime, int nDST = -1 );
   time( const SYSTEMTIME& st, int nDST = -1 );
   time( const FILETIME& ft, int nDST = -1 );

   time& operator=( __time64_t time ) NOTHROW;

   time& operator+=( date_span span );
   time& operator-=( date_span span );

   time& operator+=( time_span span ) NOTHROW;
   time& operator-=( time_span span ) NOTHROW;

   time_span operator-( time time ) const NOTHROW;
   time operator-( time_span span ) const NOTHROW;
   time operator+( time_span span ) const NOTHROW;

   time operator-( date_span span ) const;
   time operator+( date_span span ) const;

   bool operator==( time time ) const NOTHROW;
   bool operator!=( time time ) const NOTHROW;
   bool operator<( time time ) const NOTHROW;
   bool operator>( time time ) const NOTHROW;
   bool operator<=( time time ) const NOTHROW;
   bool operator>=( time time ) const NOTHROW;

   struct tm* GetGmtTm( struct tm* ptm ) const;
   struct tm* GetLocalTm( struct tm* ptm ) const;
/*
#if !_SECURE_ATL
   _ATL_INSECURE_DEPRECATE("Pass an output time structure to time::GetGmtTm")
   struct tm* GetGmtTm() const NOTHROW;
   _ATL_INSECURE_DEPRECATE("Pass an output time structure to time::GetLocalTm")
   struct tm* GetLocalTm() const NOTHROW;
#endif
*/

   bool get_as_system_time( SYSTEMTIME& st ) const NOTHROW;

   __time64_t get_time() const NOTHROW;

   int GetYear() const NOTHROW;
   int GetMonth() const NOTHROW;
   int GetDay() const NOTHROW;
   int GetHour() const NOTHROW;
   int GetMinute() const NOTHROW;
   int GetSecond() const NOTHROW;
   int GetDayOfWeek() const NOTHROW;

   int GetGmtYear() const NOTHROW;
   int GetGmtMonth() const NOTHROW;
   int GetGmtDay() const NOTHROW;
   int GetGmtHour() const NOTHROW;
   int GetGmtMinute() const NOTHROW;
   int GetGmtSecond() const NOTHROW;
   int GetGmtDayOfWeek() const NOTHROW;

   // formatting using "C" strftime
   template < class tstring >
   tstring Format(tstring & str, const char * pszFormat ) const;
   template < class tstring >
   tstring FormatGmt(tstring & str, const char * pszFormat ) const;
/*   template < class tstring >
   tstring Format(tstring & str, UINT nFormatID ) const;
   template < class tstring >
   tstring FormatGmt(tstring & str, UINT nFormatID ) const;*/
   string Format(const char * pszFormat);
   string FormatGmt(const char * pszFormat);

#if defined(_AFX) && defined(_UNICODE)
   // for compatibility with ca2 API 3.x
   string Format(const char * pFormat) const;
   string FormatGmt(const char * pFormat) const;
#endif

#ifdef _AFX
//   CArchive& Serialize64(CArchive& ar);
#endif


};

class CLASS_DECL_ca CFileTimeSpan
{
public:
   CFileTimeSpan() NOTHROW;
   CFileTimeSpan( const CFileTimeSpan& span ) NOTHROW;
   CFileTimeSpan( LONGLONG nSpan ) NOTHROW;

   CFileTimeSpan& operator=( const CFileTimeSpan& span ) NOTHROW;

   CFileTimeSpan& operator+=( CFileTimeSpan span ) NOTHROW;
   CFileTimeSpan& operator-=( CFileTimeSpan span ) NOTHROW;

   CFileTimeSpan operator+( CFileTimeSpan span ) const NOTHROW;
   CFileTimeSpan operator-( CFileTimeSpan span ) const NOTHROW;

   bool operator==( CFileTimeSpan span ) const NOTHROW;
   bool operator!=( CFileTimeSpan span ) const NOTHROW;
   bool operator<( CFileTimeSpan span ) const NOTHROW;
   bool operator>( CFileTimeSpan span ) const NOTHROW;
   bool operator<=( CFileTimeSpan span ) const NOTHROW;
   bool operator>=( CFileTimeSpan span ) const NOTHROW;

   LONGLONG GetTimeSpan() const NOTHROW;
   void SetTimeSpan( LONGLONG nSpan ) NOTHROW;

protected:
   LONGLONG m_nSpan;
};

class CLASS_DECL_ca CFileTime :
   public FILETIME
{
public:
   CFileTime() NOTHROW;
   CFileTime( const FILETIME& ft ) NOTHROW;
   CFileTime( ULONGLONG nTime ) NOTHROW;

   static CFileTime WINAPI get_current_time() NOTHROW;

   CFileTime& operator=( const FILETIME& ft ) NOTHROW;

   CFileTime& operator+=( CFileTimeSpan span ) NOTHROW;
   CFileTime& operator-=( CFileTimeSpan span ) NOTHROW;

   CFileTime operator+( CFileTimeSpan span ) const NOTHROW;
   CFileTime operator-( CFileTimeSpan span ) const NOTHROW;
   CFileTimeSpan operator-( CFileTime ft ) const NOTHROW;

   bool operator==( CFileTime ft ) const NOTHROW;
   bool operator!=( CFileTime ft ) const NOTHROW;
   bool operator<( CFileTime ft ) const NOTHROW;
   bool operator>( CFileTime ft ) const NOTHROW;
   bool operator<=( CFileTime ft ) const NOTHROW;
   bool operator>=( CFileTime ft ) const NOTHROW;

   ULONGLONG get_time() const NOTHROW;
   void SetTime( ULONGLONG nTime ) NOTHROW;

   CFileTime UTCToLocal() const NOTHROW;
   CFileTime LocalToUTC() const NOTHROW;

   static const ULONGLONG Millisecond;
   static const ULONGLONG Second;
   static const ULONGLONG Minute;
   static const ULONGLONG Hour;
   static const ULONGLONG Day;
   static const ULONGLONG Week;
};

// Used only if these strings could not be found in resources.
extern CLASS_DECL_ca const char * const szInvalidDateTime;
extern CLASS_DECL_ca const char * const szInvalidDateTimeSpan;

const int maxTimeBufferSize = 128;
const long maxDaysInSpan  =   3615897L;








enum _CTIMESPANFORMATSTEP
{
   _CTFS_NONE   = 0,
   _CTFS_FORMAT = 1,
   _CTFS_NZ     = 2
};
#define _CTIMESPANFORMATS 3


/*inline string time_span::Format(UINT nFormatID) const
{
   string strFormat;
   ATLENSURE(strFormat.load_string(nFormatID));
   return Format(strFormat);
}*/

#if defined(_AFX) && defined(_UNICODE)
inline string time_span::Format(const char * pFormat) const
{
   return Format(string(pFormat));
}
#endif

#ifdef __oledb_h__
inline time::time( const DBTIMESTAMP& dbts, int nDST ) NOTHROW
{
   struct tm atm;
   atm.tm_sec = dbts.second;
   atm.tm_min = dbts.minute;
   atm.tm_hour = dbts.hour;
   atm.tm_mday = dbts.day;
   atm.tm_mon = dbts.month - 1;        // tm_mon is 0 based
   ATLASSERT(dbts.year >= 1900);
   atm.tm_year = dbts.year - 1900;     // tm_year is 1900 based
   atm.tm_isdst = nDST;
   m_time = _mktime64(&atm);
   ATLASSUME(m_time != -1);       // indicates an illegal input time
}
#endif

inline string time::Format(const char * pFormat)
{
   string str;
   Format(str, pFormat);
   return str;
}
inline string time::FormatGmt(const char * pFormat)
{
   string str;
   FormatGmt(str, pFormat);
   return str;
}

template < class tstring >
inline tstring time::Format(tstring & str, const char * pszFormat) const
{
   if(pszFormat == NULL)
   {
      return pszFormat;
   }

   char szBuffer[maxTimeBufferSize];
#if defined(LINUX)
   struct tm* ptmTemp = localtime(&m_time);
   if (ptmTemp == NULL || !strftime(szBuffer, maxTimeBufferSize, pszFormat, ptmTemp))
    {
      szBuffer[0] = '\0';
    }
#elif defined(MACOS)
#if __WORDSIZE != 64
#pragma error "error: long should 8-byte on MACOS"
#endif
   struct tm* ptmTemp = localtime(&m_time);
   if (ptmTemp == NULL || !strftime(szBuffer, maxTimeBufferSize, pszFormat, ptmTemp))
   {
      szBuffer[0] = '\0';
   }
#elif _SECURE_ATL
   struct tm ptmTemp;
   errno_t err = _localtime64_s(&ptmTemp, &m_time);
   if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, pszFormat, &ptmTemp))
   {
      szBuffer[0] = '\0';
   }
#else
   struct tm* ptmTemp = _localtime64(&m_time);
   if (ptmTemp == NULL || !_tcsftime(szBuffer, maxTimeBufferSize, pszFormat, ptmTemp))
    {
      szBuffer[0] = '\0';
    }
#endif
   str = szBuffer;
   return szBuffer;
}

template < class tstring >
inline tstring time::FormatGmt(tstring & str, const char * pszFormat) const
{
   if(pszFormat == NULL)
   {
      return pszFormat;
   }

   char szBuffer[maxTimeBufferSize];

#if defined(LINUX) || defined(MACOS)
   struct tm* ptmTemp = gmtime(&m_time);
   if (ptmTemp == NULL || !strftime(szBuffer, maxTimeBufferSize, pszFormat, ptmTemp))
    {
      szBuffer[0] = '\0';
    }
#elif _SECURE_ATL
    struct tm ptmTemp;
   errno_t err = _gmtime64_s(&ptmTemp, &m_time);
   if (err != 0 || !_tcsftime(szBuffer, maxTimeBufferSize, pszFormat, &ptmTemp))
   {
      szBuffer[0] = '\0';
   }
#else
   struct tm* ptmTemp = _gmtime64(&m_time);
   if (ptmTemp == NULL || !_tcsftime(szBuffer, maxTimeBufferSize, pszFormat, ptmTemp))
    {
      szBuffer[0] = '\0';
    }
#endif
   str = szBuffer;
   return szBuffer;
}

/*
template < class tstring >
inline tstring time::Format(tstring & str, UINT nFormatID) const
{
   string strFormat;
   ATLENSURE(strFormat.load_string(nFormatID));
   return Format(str, strFormat);
}

template < class tstring >
inline tstring time::FormatGmt(tstring & str, UINT nFormatID) const
{
   string strFormat;
   ATLENSURE(strFormat.load_string(nFormatID));
   return FormatGmt(str, strFormat);
}
*/
