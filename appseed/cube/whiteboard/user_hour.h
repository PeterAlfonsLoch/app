#pragma once

namespace whiteboard
{
   class time;

} // namespace whiteboard


namespace user_hour
{

   enum e_event
   {
      event_start_application,
      event_exit_application,
      event_timer,
      event_wts_lock,
      event_wts_unlock,
      event_wts_logon,
      event_logon_time,
      event_wts_logoff,
      event_end_session,
   };

   enum e_node
   {
      node_interval,
      node_day,
      node_month,
      node_user_hour_set,
   };

   class interval :
      public xml::exportable,
      public xml::importable
   {
   public:
      interval();
      interval(whiteboard::view * pview, whiteboard::time & time, e_event eevent);
      virtual ~interval();

      whiteboard::time    m_timeStart;
      whiteboard::time    m_timeEnd;
      bool              m_bClosed;
      var          m_varReasonOpened;
      var          m_varReasonClosed;

      void PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent);

      virtual void xml_export(xml::output_tree & xmlot);
      virtual void xml_import(xml::input_tree & xmlit);

      static index CompareUserHour(interval * pinterval1, interval * pinterval2);
   };

   class interval_array : 
      public xml::base_array < node_interval, interval, interval & >
   {
   public:
      interval_array & operator = (const interval_array & intervala);
      void Sort();
   };

   class day :
      public xml::exportable,
      public xml::importable
   {
   public:
      day();
      day(const day & day);
      day(whiteboard::view * pview, whiteboard::time & time, e_event eevent);
      virtual ~day();
      int               m_iDay;
      interval_array     m_intervala;

      void PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent);
      interval * FindInterval(whiteboard::time & time);
      interval * last_interval();
      virtual void xml_export(xml::output_tree & xmlot);
      virtual void xml_import(xml::input_tree & xmlit);
      void Merge(day & day);
      static index CompareUserHour(day * pday1, day * pday2);
      void Sort();
   };

   class day_array :
      public xml::base_array < node_day, day, day & >
   {
   public:
      void Sort();
      day_array & operator = (const day_array & daya);
   };


   class month :
      public xml::exportable,
      public xml::importable
   {
   public:
      month();
      month(const month & month);
      month(whiteboard::view * pview, whiteboard::time & time, e_event eevent);
      int   m_iYear;
      int   m_iMonth;

      day * FindDay(whiteboard::time & time);
      day * FindDay(int iDay);

      void PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent);

      day_array  m_daya;
      virtual void xml_export(xml::output_tree & xmlot);
      virtual void xml_import(xml::input_tree & xmlit);
      void Merge(month & set);

      static index CompareUserHour(month * pmonth1, month * pmonth2);
      void Sort();
   };


   class month_array : 
      public xml::base_array < node_month, month, month & >
   {
   public:
      void Sort();
   };

   class tree_schema :
      public xml::tree_schema
   {
   public:
      tree_schema();
   };

   class user_hour_set :
      public xml::exportable,
      public xml::importable,
      virtual public ::radix::object
   {
   public:
      user_hour_set(::ca::application * papp);
      virtual ~user_hour_set();

      void PulseEvent(whiteboard::view * pview, e_event eevent);
      

      month_array     m_montha;
      tree_schema     m_treeschema;

      month * FindMonth(whiteboard::time & time);
      month * FindMonth(int iYear, int iMonth);
      virtual void xml_export(xml::output_tree & xmlot);
      virtual void xml_import(xml::input_tree & xmlit);
      bool LoadFile(const char * lpcszFileName);
      bool WriteFile(const char * lpcszFileName);

      void Merge(user_hour_set & set);
      void Sort();
   };


} // namespace user_hour