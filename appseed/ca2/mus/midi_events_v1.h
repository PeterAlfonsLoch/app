#pragma once

class CLASS_DECL_ca midi_events_v1
{
public:
   void InsertEvent(int iPosition, const midi_event_v001 & event);
   void remove_all();
   void copy(midi_events_v1 &events);
   int get_size();
//   void AddEvent(midi_event_v001 * pEvent);
   void AddEvent(midi_event_v008 * pevent);
   void AddEvent(midi_event_base * pevent, imedia::position tkPosition);
   void AddEvent(midi_event_base * pevent);
   imedia::position get_position(int iIndex);
   void GetEvent(midi_event_v001 * pEvent, int iIndex);
   midi_events_v1();
   virtual ~midi_events_v1();


   imedia::position_array            m_tkaEventsPosition;
   dword_array         m_dwaEventsData;
};
