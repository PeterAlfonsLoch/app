#pragma once

class MidiEventV001;

class CLASS_DECL_ca MidiTrackV008
{

protected:


   MidiEventV008 m_eventAdd;
   array_ptr_alloc < MidiEventV008, MidiEventV008 & > m_eventa;


public:

   MidiTrackV008();
   virtual ~MidiTrackV008();

   index GetLastEventIndex();
   MidiEventV008 & LastEvent();
   void clear();
   void remove_at(index iIndex);
   MidiEventV008 & EventAt(index iIndex);
   MidiEventV008 EventAt(index iIndex) const;
   count GetEventCount() const;
   void remove_all();

   void add(MidiEventV001 & event);
   void add(MidiEventV008 & event);
   void add(imedia::position tkDelta, MidiEventV008 & event);
   void add(MidiEventBase & event);
   void insert_at(index iIndex, MidiEventV008 & event);
   void insert_at(index iIndex, imedia::position tkDelta, MidiEventV008 & event);

   MidiTrackV008 & operator = (const MidiTrackV008 &eventSrc);
   CHUNKHDR    m_chunkHeader;    

};
