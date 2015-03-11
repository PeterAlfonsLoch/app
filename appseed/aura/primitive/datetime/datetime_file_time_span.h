#pragma once


namespace datetime
{


   class CLASS_DECL_AURA file_time_span
   {
   protected:


      LONGLONG m_nSpan;


   public:


      file_time_span() NOTHROW;
      file_time_span(const file_time_span& span) NOTHROW;
      file_time_span(LONGLONG nSpan) NOTHROW;


      file_time_span& operator=(const file_time_span& span) NOTHROW;

      file_time_span& operator+=(file_time_span span) NOTHROW;
      file_time_span& operator-=(file_time_span span) NOTHROW;

      file_time_span operator+(file_time_span span) const NOTHROW;
      file_time_span operator-(file_time_span span) const NOTHROW;

      bool operator==(file_time_span span) const NOTHROW;
      bool operator!=(file_time_span span) const NOTHROW;
      bool operator<(file_time_span span) const NOTHROW;
      bool operator>(file_time_span span) const NOTHROW;
      bool operator<=(file_time_span span) const NOTHROW;
      bool operator>=(file_time_span span) const NOTHROW;

      LONGLONG GetTimeSpan() const NOTHROW;
      void SetTimeSpan(LONGLONG nSpan) NOTHROW;


   };


} // namespace datetime









