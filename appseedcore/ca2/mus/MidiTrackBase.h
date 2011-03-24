#pragma once

class MidiEventBase;
class MidiEventV001;
class MidiEventV008;

class CLASS_DECL_ca MidiTrackBase :
   virtual public ::radix::object
{
public:


   enum e_type
   {
      TypeMidi,
      TypeLyric,
   };
   
   MidiTrackBase(::ca::application * papp);
   virtual ~MidiTrackBase();

   virtual bool IsType(e_type e_type);
   virtual e_type get_type() = 0;
   virtual ::mus::midi::e_file_result GetPosition(imedia::position &tkPosition, imedia::position tkMax) = 0;
   virtual ::mus::midi::file_flags & GetFlags() = 0;
   virtual ::mus::midi::e_file_result GetEvent(MidiEventBase * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual ::mus::midi::e_file_result GetEvent(MidiEventV001 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual imedia::position GetPosition() = 0;
   virtual ::mus::midi::e_file_result seek_begin() = 0;
   virtual ::mus::midi::e_file_result MoveNext() = 0;
   virtual imedia::position WorkGetPosition() = 0;
   virtual ::mus::midi::e_file_result WorkMoveNext() = 0;
   virtual void WorkGetEvent(MidiEventBase * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual void WorkGetEvent(MidiEventV008 * & pevent, imedia::position tkMax, BOOL bTkMaxInclusive) = 0;
   virtual bool WorkIsEOT() = 0;
   virtual ::mus::midi::e_file_result WorkSeekBegin() = 0;
   virtual ::mus::midi::e_file_result WorkSeekEnd() = 0;
};

