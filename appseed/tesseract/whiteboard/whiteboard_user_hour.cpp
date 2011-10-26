#include "StdAfx.h"

namespace user_hour
{

   interval::interval()
   {
      m_bClosed = false;
   }
   
   interval::interval(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      m_bClosed = false;
      m_timeStart = time;
      if(eevent == event_timer)
      {
         m_varReasonOpened = "Timer has opened interval.";
      }
      else if(eevent == event_wts_unlock)
      {
         m_varReasonOpened = "Session unlock";
      }
      else if(eevent == event_wts_logon)
      {
         m_varReasonOpened = "Session Logon";
      }
      else if(eevent == event_logon_time)
      {
         //m_varReasonOpened = "Whiteboard Startup";
         m_varReasonOpened = "Logon";
      }
      else if(eevent == event_start_application)
      {
         //m_varReasonOpened = "Whiteboard Startup";
         m_varReasonOpened = "Whiteboard Start";
      }
      else
      {
         throw "Not expected constructing with this event"; // Not expected constructing with this event
      }
      PulseEvent(pview, time, eevent);
   }

   interval::~interval()
   {
   }

   void interval::PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      UNREFERENCED_PARAMETER(pview);
      if(eevent == event_timer ||
         eevent == event_wts_unlock ||
         eevent == event_wts_logon ||
         eevent == event_logon_time ||
         eevent == event_start_application)
      {
         ASSERT(!m_bClosed);
         ASSERT(time >= m_timeStart);
         if(m_bClosed)
            return;
         if(time < m_timeStart)
            return;
         if(eevent == event_timer)
         {
            if(m_varReasonOpened.is_empty())
            {
               m_varReasonOpened = "Timer has opened interval.";
            }
         }
         else if(eevent == event_wts_unlock)
         {
            m_varReasonOpened = "Session unlock";
         }
         else if(eevent == event_wts_logon)
         {
            m_varReasonOpened = "Session Logon";
         }
         else if(eevent == event_logon_time)
         {
            //m_varReasonOpened = "Whiteboard Startup";
            m_varReasonOpened = "Logon";
         }
         else if(eevent == event_start_application)
         {
            m_varReasonOpened = "Whiteboard Startup";
            //m_varReasonOpened = "System Start";
         }
         m_timeEnd = time;
      }
      else if(
            eevent == event_wts_lock
         || eevent == event_wts_logoff
         || eevent == event_exit_application
         || eevent == event_end_session
         )
      {
         switch(eevent)
         {
         case event_wts_lock:
            m_varReasonClosed = "Session lock";
            break;
         case event_wts_logoff:
            m_varReasonClosed = "Session Logoff";
            break;
         case event_exit_application:
            m_varReasonClosed = "Exit System";
            break;
         case event_end_session:
            m_varReasonClosed = "Session End (PwOff,Rst,...)";
            break;
         }
       CaSys(::ca::get_thread()).log().trace("interval::PulseEvent::Reason Closed: %s", m_varReasonClosed.get_string());
         m_bClosed = true;
         m_timeEnd = time;
      }
      else
      {
         /// Not expected until now
         ASSERT(FALSE);
      }
   }

   void interval::xml_export(xml::output_tree & xmlot)
   {
      string str;

      m_timeStart.ToString(str);
      xmlot.set_attr("time_start", str);

      m_timeEnd.ToString(str);
      xmlot.set_attr("time_end", str);

      xmlot.set_attr("closed", m_bClosed ? 1 : 0);
      xmlot.export_node("open_reason", m_varReasonOpened);
      xmlot.export_node("close_reason", m_varReasonClosed);

   }

   void interval::xml_import(xml::input_tree & xmlit)
   {
      string str;
      
      xmlit.get_attr("time_start", str);
      m_timeStart.FromString(str);

      xmlit.get_attr("time_end", str);
      m_timeEnd.FromString(str);

      int i;
      xmlit.get_attr("closed", i);
      m_bClosed = i != FALSE ? true : false; 

      xmlit.import_node("open_reason", m_varReasonOpened);
      xmlit.import_node("close_reason", m_varReasonClosed);
   }

   index interval::CompareUserHour(interval * pinterval1, interval * pinterval2)
   {
      if(pinterval1->m_timeStart > pinterval2->m_timeStart)
         return 1;
      else if(pinterval2->m_timeStart > pinterval1->m_timeStart)
         return -1;
      else
      {
         if(pinterval1->m_timeEnd > pinterval2->m_timeEnd)
            return 1;
         else if(pinterval2->m_timeEnd > pinterval1->m_timeEnd)
            return -1;
         else 
            return 0;
      }
   }

   interval_array & interval_array::operator = (const interval_array & intervala)
   {
      array_ptr_alloc < interval, interval & >::operator =(intervala);
      return *this;
   }

   void interval_array::Sort()
   {
      sort::array::quick_sort(m_ptra, &interval::CompareUserHour);
   }

   day::day()
   {
      m_iDay   = -1;
   }

   day::day(const day & day)
   {
      m_iDay      = day.m_iDay;
      m_intervala = day.m_intervala;
   }

   day::day(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      m_iDay   = time.m_iDay;
      PulseEvent(pview, time, eevent);
   }

   day::~day()
   {
   }



   interval * day::FindInterval(whiteboard::time & time)
   {
      ASSERT(time.m_iDay == m_iDay);
      interval * pintervalFound = NULL;
      whiteboard::time timeMax;
      for(int i = 0; i < m_intervala.get_size(); i++)
      {
         interval * pinterval = &m_intervala[i];
         if(!pinterval->m_bClosed
            && pinterval->m_timeStart <= time)
         {
            if(pintervalFound != NULL)
            {
               if(time > timeMax)
               {
                  // the last interval found should be closed
                  // because it is not so recent
             //     pintervalFound->m_bClosed = true;
                  timeMax = time;
               }
               else
               {
               //   pinterval->m_bClosed = false;
               }
            }
            pintervalFound = pinterval;
         }
      }
      return pintervalFound;
   }

   interval * day::last_interval()
   {
      interval * pintervalFound = NULL;
      whiteboard::time timeMax;
      for(int i = 0; i < m_intervala.get_size(); i++)
      {
         interval * pinterval = &m_intervala[i];
         if(pinterval->m_timeEnd >= timeMax)
         {
            timeMax = pinterval->m_timeEnd;
            pintervalFound = pinterval;
         }
      }
      return pintervalFound;
   }

   void day::PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      if(eevent == event_timer)
      {
         interval * pinterval = last_interval();


         if(pinterval == NULL) /* || pinterval->m_varReasonOpened != "Timer has opened interval.")*/
         {
            interval * pinterval = new interval(pview, time, eevent);
            m_intervala.add(pinterval);         
         }
         else
         {
            if(pinterval->m_bClosed)
            {
               return;
            }
            pinterval->PulseEvent(pview, time, eevent);
         }
      }
      else if(eevent == event_wts_unlock ||
         eevent == event_wts_logon ||
         eevent == event_logon_time ||
         eevent == event_start_application)
      {
         interval * pinterval = new interval(pview, time, eevent);
         m_intervala.add(pinterval);         
      }
      else if(eevent == event_wts_lock
           || eevent == event_wts_logoff
           || eevent == event_end_session)
      {
/*         interval * pinterval = FindInterval(time);
         ASSERT(pinterval != NULL);
         if(pinterval == NULL)
            return;*/

  //       pinterval->PulseEvent(time, eevent);
         interval * pinterval = last_interval();

         if(pinterval == NULL)
         {
            interval * pinterval = new interval(pview, time, eevent);
            m_intervala.add(pinterval);         
         }
         else
         {
            pinterval->PulseEvent(pview, time, eevent);
         }

      }
      else
      {
         ASSERT(FALSE); // Not expected event
      }
   }

   void day::xml_export(xml::output_tree & xmlot)
   {
      xmlot.export_node("intervals", m_intervala);
      xmlot.set_attr("day", m_iDay);
   }
  
   void day::xml_import(xml::input_tree & xmlit)
   {
      xmlit.import_node("intervals", m_intervala);
      xmlit.get_attr("day", m_iDay);
   }

   void day::Merge(day & day)
   {
      ASSERT(m_iDay == day.m_iDay);
      for(int i = 0; i < m_intervala.get_size(); i++)
      {
         interval & interval1 = m_intervala.element_at(i);
         for(int j = 0; j < day.m_intervala.get_size(); j++)
         {
            interval & interval2 = day.m_intervala.element_at(j);
            if((interval1.m_timeStart <= interval2.m_timeStart
            && interval1.m_timeEnd >= interval2.m_timeStart)
            || (interval1.m_timeStart <= interval2.m_timeEnd
            && interval1.m_timeEnd >= interval2.m_timeEnd))
            {
               if(interval2.m_timeStart < interval1.m_timeStart)
               {
                  interval1.m_timeStart = interval2.m_timeStart;
                  interval1.m_varReasonOpened = interval2.m_varReasonOpened;
               }
               if(interval2.m_timeEnd > interval1.m_timeEnd)
               {
                  interval1.m_timeEnd = interval2.m_timeStart;
                  interval1.m_varReasonClosed = interval2.m_varReasonOpened;
                  interval1.m_bClosed = interval2.m_bClosed;
               }
            }
         }
      }
   }

   index day::CompareUserHour(day * pday1, day * pday2)
   {
      return pday1->m_iDay - pday2->m_iDay;
   }

   void day::Sort()
   {
      m_intervala.Sort();
   }


   day_array & day_array::operator = (const day_array & daya)
   {
      array_ptr_alloc < day, day & >::operator = (daya);
      return *this;
   }

   void day_array::Sort()
   {
      ::sort::array::quick_sort(m_ptra, day::CompareUserHour);
      for(int i = 0; i < get_size(); i++)
      {
         element_at(i).Sort();
      }
   }

   month::month()
   {
      m_iYear     = -1;
      m_iMonth    = -1;
   }

   month::month(const month & month)
   {
      m_iYear     = month.m_iYear;
      m_iMonth    = month.m_iMonth;
      m_daya      = month.m_daya;
   }

   month::month(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      m_iYear     = time.m_iYear;
      m_iMonth    = time.m_iMonth;
      PulseEvent(pview, time, eevent);
   }

   day * month::FindDay(whiteboard::time & time)
   {
      ASSERT(time.m_iYear == m_iYear);
      ASSERT(time.m_iMonth == m_iMonth);
      return FindDay(time.m_iDay);
   }

   day * month::FindDay(int iDay)
   {
      for(int i = 0; i < m_daya.get_size(); i++)
      {
         day * pday = &m_daya[i];
         if(pday->m_iDay == iDay)
         {
            return pday;
         }
      }
      return NULL;
   }

   void month::PulseEvent(whiteboard::view * pview, whiteboard::time & time, e_event eevent)
   {
      day * pday = FindDay(time);

      if(pday == NULL)
      {
         day * pday = new day(pview, time, eevent);
         m_daya.add(pday);         
      }
      else
      {
         pday->PulseEvent(pview, time, eevent);
      }
   }

   void month::xml_export(xml::output_tree & xmlot)
   {
      xmlot.export_node("days", m_daya);
      xmlot.set_attr("year", m_iYear);
      xmlot.set_attr("month", m_iMonth);
   }
  
   void month::xml_import(xml::input_tree & xmlit)
   {
      xmlit.import_node("days", m_daya);
      xmlit.get_attr("year", m_iYear);
      xmlit.get_attr("month", m_iMonth);
   }

   void month::Merge(month & month)
   {
      ASSERT(m_iYear == month.m_iYear);
      ASSERT(m_iMonth == month.m_iMonth);
      for(int i = 0; i < month.m_daya.get_size(); i++)
      {
         day & day = month.m_daya.element_at(i);
         class day * pday = FindDay(day.m_iDay);
         if(pday == NULL)
         {
            m_daya.add(day);
         }
         else
         {
            pday->Merge(day);
         }
      }
   }

   index month::CompareUserHour(month * pmonth1, month * pmonth2)
   {
      int iCompare = pmonth1->m_iYear - pmonth2->m_iYear;
      if(iCompare != 0)
         return iCompare;
      else
         return pmonth1->m_iMonth - pmonth2->m_iMonth;
   }

   void month::Sort()
   {
      m_daya.Sort();
   }

   void month_array::Sort()
   {
      ::sort::array::quick_sort(m_ptra, &month::CompareUserHour);
      for(int i = 0; i < get_size(); i++)
      {
         element_at(i).Sort();
      }
   }

   tree_schema::tree_schema()
   {
      set_node_name(node_interval   , "interval");
      set_node_name(node_day        , "day");
      set_node_name(node_month      , "month");
   }

   user_hour_set::user_hour_set(::ca::application * papp) :
      ca(papp)
   {
   }

   user_hour_set::~user_hour_set()
   {
   }

   bool user_hour_set::LoadFile(const char * lpcszFileName)
   {
      xml::document doc(get_app());

      if(!doc.load(Application.file().as_string(lpcszFileName)))
         return false;

      xml::input_tree xmlit(get_app());
      xmlit.m_pdocument = &doc;
      xmlit.set_schema(&m_treeschema);
      try
      {
         xmlit.import_node("userhourset", *this);
      }
      catch(...)
      {
         return false;
      }
      return true;
   }

   bool user_hour_set::WriteFile(const char * lpcszFileName)
   {
      xml::document doc(get_app());

      xml::output_tree xmlot(get_app());
      xmlot.m_pdocument = &doc;
      xmlot.set_schema(&m_treeschema);
      xmlot.export_node("userhourset", *this);

      Application.file().put_contents(lpcszFileName, doc.get_xml());
      
      return true;
   }

   void user_hour_set::PulseEvent(whiteboard::view * pview, e_event eevent)
   {
      whiteboard::time time;
      if(eevent == event_logon_time)
      {
         whiteboard::util::get_current_user_logon_time(time);
      }
      else
      {
         time.Now();
      }
      month * pmonth = FindMonth(time);

      if(pmonth == NULL)
      {
         month * pmonth = new month(pview, time, eevent);
         m_montha.add(pmonth);         
      }
      else
      {
         pmonth->PulseEvent(pview, time, eevent);
      }
   }

   void user_hour_set::Merge(user_hour_set & set)
   {
      for(int i = 0; i < set.m_montha.get_size(); i++)
      {
         month & month = set.m_montha.element_at(i);
         class month * pmonth = FindMonth(month.m_iYear, month.m_iMonth);
         if(pmonth == NULL)
         {
            m_montha.add(month);
         }
         else
         {
            pmonth->Merge(month);
         }
      }
   }

   month * user_hour_set::FindMonth(whiteboard::time & time)
   {
      return FindMonth(time.m_iYear, time.m_iMonth);
   }
   month * user_hour_set::FindMonth(int iYear, int iMonth)
   {
      for(int i = 0; i < m_montha.get_size(); i++)
      {
         month * pmonth = &m_montha[i];
         if(pmonth->m_iYear == iYear
         && pmonth->m_iMonth == iMonth)
         {
            return pmonth;
         }
      }
      return NULL;
   }

   void user_hour_set::xml_export(xml::output_tree & xmlot)
   {
      xmlot.export_node("months", m_montha);
   }
  
   void user_hour_set::xml_import(xml::input_tree & xmlit)
   {
      xmlit.import_node("months", m_montha);
   }

   void user_hour_set::Sort()
   {
      m_montha.Sort();
   }


} // namespace user_hour