#pragma once


class LyricEventsV1;
class LyricEventsV2;


class CLASS_DECL_ca MidiLyricTrack : 
   public MidiTrackBase
{
public:


   ::mus::midi::file *        m_pfile;
   MidiEventV001              m_eventv001;
   MidiTrackV008              m_trackWorkStorage;
   ::mus::midi::file_flags    m_flagsFile;
   imedia::position           m_tkPosition;
   int                        m_iCurrentEvent;
   int                        m_iDelay; // in milliseconds
    
   imedia::position           m_tkLastPosition;
   int                        m_iLastEvent;
   int                        m_iLastDelay;


   MidiLyricTrack(::ca::application * papp);
   MidiLyricTrack(::mus::midi::file * pfile);
   MidiLyricTrack(const MidiLyricTrack & track);
   virtual ~MidiLyricTrack();

   imedia::position ApplyDelay(imedia::position tkPosition);
   void SetDelay(int iMillis);
   virtual bool WorkIsEOT();
   e_type get_type();
   ::mus::midi::e_file_result MoveNext();
   VMSRESULT Prepare(::ca::application * papp, LyricEventsV1 & events);
   VMSRESULT Prepare(::ca::application * papp, LyricEventsV2 & events);
   ::mus::midi::e_file_result seek_begin();
   ::mus::midi::e_file_result seek_end();
   imedia::position GetPosition();
   virtual ::mus::midi::e_file_result GetPosition(imedia::position &tkPosition, imedia::position tkMax);
   virtual const ::mus::midi::file_flags & GetFlags() const;
   virtual ::mus::midi::file_flags & GetFlags();
   
   virtual ::mus::midi::e_file_result GetEvent(MidiEventBase * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual ::mus::midi::e_file_result GetEvent(MidiEventV001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual imedia::position WorkGetPosition();
   virtual ::mus::midi::e_file_result WorkSeekBegin();
   virtual ::mus::midi::e_file_result WorkSeekEnd();

   virtual ::mus::midi::e_file_result WorkMoveNext();
   
   virtual void WorkGetEvent(MidiEventBase * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual void WorkGetEvent(MidiEventV008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);


   MidiLyricTrack & operator =(const MidiLyricTrack &track);
    
};

