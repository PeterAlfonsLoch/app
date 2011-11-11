#pragma once

class midi_event_v001;

class CLASS_DECL_ca midi_track_v008
{

protected:


   midi_event_v008 m_eventAdd;
   array_ptr_alloc < midi_event_v008, midi_event_v008 & > m_eventa;


public:

   midi_track_v008();
   virtual ~midi_track_v008();

   index GetLastEventIndex();
   midi_event_v008 & LastEvent();
   void clear();
   void remove_at(index iIndex);
   midi_event_v008 & EventAt(index iIndex);
   midi_event_v008 EventAt(index iIndex) const;
   count GetEventCount() const;
   void remove_all();

   void add(midi_event_v001 & event);
   void add(midi_event_v008 & event);
   void add(imedia::position tkDelta, midi_event_v008 & event);
   void add(midi_event_base & event);
   void insert_at(index iIndex, midi_event_v008 & event);
   void insert_at(index iIndex, imedia::position tkDelta, midi_event_v008 & event);

   midi_track_v008 & operator = (const midi_track_v008 &eventSrc);
   CHUNKHDR    m_chunkHeader;    

};
