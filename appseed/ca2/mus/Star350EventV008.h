#pragma once

class Star350EventBase;
class Star350EventV001;

class CLASS_DECL_ca Star350EventV008 :
   public Star350EventV016
{
protected:

    imedia::position    m_tkDelta;
    imedia::position    m_tkDuration;
    int                 m_iType;

public:

   Star350EventV008();
   virtual ~Star350EventV008();
   virtual void clear();

   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }

   virtual Star350EventBase & operator = (const Star350EventBase & eventSrc) { return Star350EventBase::operator = (eventSrc); }
   virtual Star350EventV016 & operator = (const Star350EventV016 & eventSrc) { return Star350EventV016::operator = (eventSrc); }
   virtual Star350EventV008 & operator = (const Star350EventV008 & eventSrc);

   virtual VMSRESULT WriteParam(LPVOID lpData, int iSize);
   virtual VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft, EventType evtype);
   virtual inline imedia::position GetDelta() const;
   virtual inline void SetDelta(imedia::position tkDelta);
   VMSRESULT GetEventV001(Star350EventV001 * lpMidiEventV001,  DWORD dwPositionTicks);

   virtual inline imedia::position GetDuration() const;
   virtual inline void SetDuration(imedia::position tkDelta);

   virtual inline int GetStar350Type() const;
   virtual inline void SetStar350Type(int iType);

};

