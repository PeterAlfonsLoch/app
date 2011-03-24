#include "StdAfx.h"

MidiTrackV008::MidiTrackV008()
{
}

MidiTrackV008::~MidiTrackV008()
{

}

MidiTrackV008 & MidiTrackV008::operator =(const MidiTrackV008 &eventSrc)
{
   m_chunkHeader = eventSrc.m_chunkHeader;
   m_eventa = eventSrc.m_eventa;
   return *this;
}

void MidiTrackV008::insert_at(index iIndex, MidiEventV008 & event)
{
   m_eventa.insert_at(iIndex, event);
}

void MidiTrackV008::insert_at(index iIndex, imedia::position tkDelta, MidiEventV008 & event)
{
   m_eventa.insert_at(iIndex, event);
   m_eventa[iIndex]._SetDelta(tkDelta);
}

void MidiTrackV008::remove_all()
{
   m_eventa.remove_all();
}

void MidiTrackV008::remove_at(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < m_eventa.get_size());
   m_eventa.remove_at(iIndex);
}

void MidiTrackV008::clear()
{
   remove_all();
}




count MidiTrackV008::GetEventCount() const
{
   return m_eventa.get_size();
}

MidiEventV008 & MidiTrackV008::EventAt(index iIndex)
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < m_eventa.get_size());
   return m_eventa.element_at(iIndex);
}

MidiEventV008 MidiTrackV008::EventAt(index iIndex) const
{
   ASSERT(iIndex >= 0);
   ASSERT(iIndex < m_eventa.get_size());
   return m_eventa.element_at(iIndex);
}

void MidiTrackV008::add(MidiEventBase &event)
{
   m_eventAdd = event;
   add(m_eventAdd);
}

void MidiTrackV008::add(MidiEventV001 &event)
{
   m_eventAdd = event;
   add(m_eventAdd);
}

void MidiTrackV008::add(MidiEventV008 &event)
{
   insert_at(GetEventCount(), event);
}

void MidiTrackV008::add(imedia::position tkDelta, MidiEventV008 &event)
{
   insert_at(GetEventCount(), tkDelta, event);
}

MidiEventV008 & MidiTrackV008::LastEvent()
{
   ASSERT(GetEventCount() > 0);
   return EventAt(GetLastEventIndex());
}

count MidiTrackV008::GetLastEventIndex()
{
   return GetEventCount() - 1;
}
