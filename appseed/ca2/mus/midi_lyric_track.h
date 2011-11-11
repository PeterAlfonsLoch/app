#pragma once


class LyricEventsV1;
class LyricEventsV2;


class CLASS_DECL_ca midi_lyric_track : 
   public midi_track_base
{
public:


   ::mus::midi::file *        m_pfile;
   midi_event_v001              m_eventv001;
   midi_track_v008              m_trackWorkStorage;
   ::mus::midi::file_flags    m_flagsFile;
   imedia::position           m_tkPosition;
   int                        m_iCurrentEvent;
   int                        m_iDelay; // in milliseconds
    
   imedia::position           m_tkLastPosition;
   int                        m_iLastEvent;
   int                        m_iLastDelay;


   midi_lyric_track(::ca::application * papp);
   midi_lyric_track(::mus::midi::file * pfile);
   midi_lyric_track(const midi_lyric_track & track);
   virtual ~midi_lyric_track();

   imedia::position ApplyDelay(imedia::position tkPosition);
   void SetDelay(int iMillis);
   virtual bool WorkIsEOT();
   e_type get_type();
   ::mus::midi::e_file_result MoveNext();
   VMSRESULT Prepare(::ca::application * papp, LyricEventsV1 & events);
   VMSRESULT Prepare(::ca::application * papp, LyricEventsV2 & events);
   ::mus::midi::e_file_result seek_begin();
   ::mus::midi::e_file_result seek_end();
   imedia::position get_position();
   virtual ::mus::midi::e_file_result get_position(imedia::position &tkPosition, imedia::position tkMax);
   virtual const ::mus::midi::file_flags & GetFlags() const;
   virtual ::mus::midi::file_flags & GetFlags();
   
   virtual ::mus::midi::e_file_result GetEvent(midi_event_base * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual ::mus::midi::e_file_result GetEvent(midi_event_v001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual imedia::position WorkGetPosition();
   virtual ::mus::midi::e_file_result WorkSeekBegin();
   virtual ::mus::midi::e_file_result WorkSeekEnd();

   virtual ::mus::midi::e_file_result WorkMoveNext();
   
   virtual void WorkGetEvent(midi_event_base * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);

   virtual void WorkGetEvent(midi_event_v008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive);


   midi_lyric_track & operator =(const midi_lyric_track &track);
    
};

