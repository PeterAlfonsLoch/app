#pragma once

namespace datetime
{


   class CLASS_DECL_ACE time_span
   {
   public:


      __time64_t m_timeSpan;


      time_span() NOTHROW;
      time_span(__time64_t time) NOTHROW;
      time_span(int64_t lDays,int32_t nHours,int32_t nMins,int32_t nSecs) NOTHROW;

      int64_t GetDays() const NOTHROW;
      int64_t GetTotalHours() const NOTHROW;
      int32_t GetHours() const NOTHROW;
      int64_t GetTotalMinutes() const NOTHROW;
      int32_t GetMinutes() const NOTHROW;
      int64_t GetTotalSeconds() const NOTHROW;
      int32_t GetSeconds() const NOTHROW;

      __time64_t GetTimeSpan() const NOTHROW;

      time_span operator+(time_span span) const NOTHROW;
      time_span operator-(time_span span) const NOTHROW;
      time_span& operator+=(time_span span) NOTHROW;
      time_span& operator-=(time_span span) NOTHROW;
      bool operator==(time_span span) const NOTHROW;
      bool operator!=(time_span span) const NOTHROW;
      bool operator<(time_span span) const NOTHROW;
      bool operator>(time_span span) const NOTHROW;
      bool operator<=(time_span span) const NOTHROW;
      bool operator>=(time_span span) const NOTHROW;

   public:

      string Format(const char * pszFormat) const;

#ifdef _AFX
      //   CArchive& Serialize64(CArchive& ar);
#endif

   };


} // namespace datetime





