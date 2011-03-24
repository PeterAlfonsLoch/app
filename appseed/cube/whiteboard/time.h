#pragma once

namespace whiteboard
{
   class view;

   class CLASS_DECL_CA2_CUBE time :
      public xml::exportable,
      public xml::importable
   {
   public:
      class time();
      virtual ~time();
   public:
      void Now();
      void ToString(string & str) const;
      bool FromString(const char * lpcsz);
      void TimeToString(string & str) const;
      void HourMinuteToString(string & str) const;
      // Year
      int m_iYear;
      // January = 1
      int m_iMonth;
      // First day = 1
      int m_iDay;
      int m_iHour;
      int m_iMinute;
      int m_iSecond;

      void SetTime(__time64_t time64);
      void SetTime(class ::time & time);

      virtual void xml_export(xml::output_tree & xmlot);
      virtual void xml_import(xml::input_tree & xmlit);

      bool operator >(const class time & time) const;
      bool operator <(const class time & time) const;
      bool operator >=(const class time & time) const;
      bool operator <=(const class time & time) const;

      void Min(const class time & time1, const class time & time2);
      void Max(const class time & time1, const class time & time2);

   };

   inline bool time::operator >=(const class time & time) const
   {
      return !operator <(time);
   }
   inline bool time::operator <=(const class time & time) const
   {
      return !operator >(time);
   }

} // namespace whiteboard