#pragma once

class CLASS_DECL_ca MidiEventsV1  
{
public:
   void InsertEvent(int iPosition, const MidiEventV001 & event);
   void remove_all();
   void copy(MidiEventsV1 &events);
   int get_size();
//   void AddEvent(MidiEventV001 * pEvent);
   void AddEvent(MidiEventV008 * pevent);
   void AddEvent(MidiEventBase * pevent, imedia::position tkPosition);
   void AddEvent(MidiEventBase * pevent);
   imedia::position GetPosition(int iIndex);
   void GetEvent(MidiEventV001 * pEvent, int iIndex);
   MidiEventsV1();
   virtual ~MidiEventsV1();


   imedia::position_array            m_tkaEventsPosition;
   dword_array         m_dwaEventsData;
};