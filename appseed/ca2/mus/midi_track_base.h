#pragma once

class midi_event_base;
class midi_event_v001;
class midi_event_v008;

class CLASS_DECL_ca midi_track_base :
   virtual public ::radix::object
{
public:


   enum e_type
   {
      TypeMidi,
      TypeLyric,
   };
   
   midi_track_base(::ca::application * papp);
   virtual ~midi_track_base();

   virtual bool IsType(e_type e_type);
   virtual e_type get_type() = 0;
   virtual ::mus::midi::e_file_result get_position(imedia::position &tkPosition, imedia::position tkMax) = 0;
   virtual ::mus::midi::file_flags & GetFlags() = 0;
   virtual ::mus::midi::e_file_result GetEvent(midi_event_base * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual ::mus::midi::e_file_result GetEvent(midi_event_v001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual imedia::position get_position() = 0;
   virtual ::mus::midi::e_file_result seek_begin() = 0;
   virtual ::mus::midi::e_file_result MoveNext() = 0;
   virtual imedia::position WorkGetPosition() = 0;
   virtual ::mus::midi::e_file_result WorkMoveNext() = 0;
   virtual void WorkGetEvent(midi_event_base * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual void WorkGetEvent(midi_event_v008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual bool WorkIsEOT() = 0;
   virtual ::mus::midi::e_file_result WorkSeekBegin() = 0;
   virtual ::mus::midi::e_file_result WorkSeekEnd() = 0;
};

