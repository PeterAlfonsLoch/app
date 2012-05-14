#pragma once

namespace datetime
{

   class CLASS_DECL_ca value
   {
   public:

      int            m_iYear;
      int            m_iMonth;
      int            m_iDay;
      int            m_iHour;
      int            m_iMinute;
      int            m_iSecond;
      bool           m_bSpan;

      value(const ::datetime::time & time);
      value();
      ~value();

      // ano gregoriano médio de 365,2425 dias solares
      double get_years() const;
      // baseado no ano gregoriano médio de 365,2425 dias solares * 12.0
      double get_months() const;
      double get_days() const;
      double get_hours() const;
      double get_minutes() const;
      double get_seconds() const;

      ::datetime::time get_time() const;
      ::datetime::time_span GetSpan() const;
      value & operator = (const ::datetime::time & time);

      string to_string(::ca::application * pcaapp, ::user::str_context * pcontext);

   };

   CLASS_DECL_ca value span_strtotime(::ca::application * pcaapp, ::user::str_context * pcontext, const char * psz);
   CLASS_DECL_ca value strtotime(::ca::application * pcaapp, ::user::str_context * pcontext, const char * psz, int & iPath, int & iPathCount);

} // namespace datetime


CLASS_DECL_ca datetime::value operator + (const datetime::value & val1, const datetime::value & val2);
CLASS_DECL_ca datetime::value operator - (const datetime::value & val1, const datetime::value & val2);
CLASS_DECL_ca datetime::value operator * (const datetime::value & val1, double d);
CLASS_DECL_ca datetime::value operator / (const datetime::value & val1, double d);
