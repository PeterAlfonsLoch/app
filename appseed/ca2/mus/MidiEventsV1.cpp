#include "StdAfx.h"

midi_events_v1::midi_events_v1()
{

}

midi_events_v1::~midi_events_v1()
{

}

void midi_events_v1::GetEvent(midi_event_v001 *pEvent, int iIndex)
{
   DWORD dw = m_dwaEventsData.get_at(iIndex);
   memcpy(pEvent->m_abEvent , &dw, 3);
   pEvent->m_tkPosition = m_tkaEventsPosition.get_at(iIndex);
}

imedia::position midi_events_v1::get_position(int iIndex)
{
   return m_tkaEventsPosition.get_at(iIndex);
}

/*void midi_events_v1::AddEvent(midi_event_v001 *pEvent)
{
   DWORD dw = 0;
   memcpy(&dw, pEvent->m_abEvent, 3);
   m_dwaEventsData.add(dw);
   m_tkaEventsPosition.add(pEvent->m_tkPosition);
}*/
void midi_events_v1::AddEvent(midi_event_base * pevent)
{
   AddEvent(pevent, pevent->get_position());
}

void midi_events_v1::AddEvent(midi_event_base * pevent, imedia::position tkPosition)
{
   DWORD dw(0);
   dw |= pevent->GetFullType();
   dw |= pevent->GetChB1() << 8;
   dw |= pevent->GetChB2() << 16;
   m_dwaEventsData.add(dw);
   m_tkaEventsPosition.add(imedia::position(tkPosition));
}

void midi_events_v1::AddEvent(midi_event_v008 * pevent)
{
   DWORD dw(0);
   dw |= pevent->_GetFullType();
   dw |= pevent->_GetChB1() << 8;
   dw |= pevent->_GetChB2() << 16;
   m_dwaEventsData.add(dw);
   m_tkaEventsPosition.add(imedia::position(pevent->_GetPosition()));
}

int midi_events_v1::get_size()
{
   ASSERT(m_dwaEventsData.get_size() == m_tkaEventsPosition.get_size());
   return m_dwaEventsData.get_size();
}

void midi_events_v1::copy(midi_events_v1 &events)
{
   ASSERT(events.m_dwaEventsData.get_size() ==
         events.m_tkaEventsPosition.get_size());
   m_dwaEventsData.copy(events.m_dwaEventsData);
   m_tkaEventsPosition.copy(events.m_tkaEventsPosition);

}

void midi_events_v1::remove_all()
{
   m_dwaEventsData.remove_all();
   m_tkaEventsPosition.remove_all();
}

void midi_events_v1::InsertEvent(int iPosition, const midi_event_v001 &event)
{
   DWORD dw = 0;
   memcpy(&dw, event.m_abEvent, 3);
   m_dwaEventsData.insert_at(iPosition, dw);
   m_tkaEventsPosition.insert_at(iPosition, imedia::position(event.m_tkPosition));
}
