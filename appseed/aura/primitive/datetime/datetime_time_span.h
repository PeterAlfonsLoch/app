#pragma once

namespace datetime
{


   class CLASS_DECL_AURA time_span
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

   inline time_span::time_span() throw() :
      m_timeSpan(0)
   {
   }

   inline time_span::time_span(__time64_t time) throw() :
      m_timeSpan(time)
   {
   }

   inline time_span::time_span(int64_t lDays, int32_t nHours, int32_t nMins, int32_t nSecs) throw()
   {
      m_timeSpan = nSecs + 60 * (nMins + 60 * (nHours + int64_t(24) * lDays));
   }

   inline int64_t time_span::GetDays() const throw()
   {
      return(m_timeSpan / (24 * 3600));
   }

   inline int64_t time_span::GetTotalHours() const throw()
   {
      return(m_timeSpan / 3600);
   }

   inline int32_t time_span::GetHours() const throw()
   {
      return(LONG(GetTotalHours() - (GetDays() * 24)));
   }

   inline int64_t time_span::GetTotalMinutes() const throw()
   {
      return(m_timeSpan / 60);
   }

   inline int32_t time_span::GetMinutes() const throw()
   {
      return(LONG(GetTotalMinutes() - (GetTotalHours() * 60)));
   }

   inline int64_t time_span::GetTotalSeconds() const throw()
   {
      return(m_timeSpan);
   }

   inline int32_t time_span::GetSeconds() const throw()
   {
      return(LONG(GetTotalSeconds() - (GetTotalMinutes() * 60)));
   }

   inline __time64_t time_span::GetTimeSpan() const throw()
   {
      return(m_timeSpan);
   }

   inline time_span time_span::operator+(time_span span) const throw()
   {
      return(time_span(m_timeSpan + span.m_timeSpan));
   }

   inline time_span time_span::operator-(time_span span) const throw()
   {
      return(time_span(m_timeSpan - span.m_timeSpan));
   }

   inline time_span& time_span::operator+=(time_span span) throw()
   {
      m_timeSpan += span.m_timeSpan;
      return *this;
   }

   inline time_span& time_span::operator-=(time_span span) throw()
   {
      m_timeSpan -= span.m_timeSpan;
      return *this;
   }

   inline bool time_span::operator==(time_span span) const throw()
   {
      return(m_timeSpan == span.m_timeSpan);
   }

   inline bool time_span::operator!=(time_span span) const throw()
   {
      return(m_timeSpan != span.m_timeSpan);
   }

   inline bool time_span::operator<(time_span span) const throw()
   {
      return(m_timeSpan < span.m_timeSpan);
   }

   inline bool time_span::operator>(time_span span) const throw()
   {
      return(m_timeSpan > span.m_timeSpan);
   }

   inline bool time_span::operator<=(time_span span) const throw()
   {
      return(m_timeSpan <= span.m_timeSpan);
   }

   inline bool time_span::operator>=(time_span span) const throw()
   {
      return(m_timeSpan >= span.m_timeSpan);
   }



} // namespace datetime





