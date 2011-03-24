#pragma once

class MidiEventV001;



class CLASS_DECL_ca MidiEventV008 :
   public MidiEventV016
{
protected:
   imedia::position          m_tkPosition;
public:
   MidiEventV008();
   MidiEventV008(const MidiEventBase &eventSrc);
   MidiEventV008(const MidiEventV001 &eventSrc);
   MidiEventV008(const MidiEventV008 &eventSrc);
   virtual ~MidiEventV008();

   virtual MidiEventBase & operator = (const MidiEventBase & eventSrc) { return MidiEventBase::operator = (eventSrc); }
   virtual MidiEventBase & operator = (const MidiEventV008 & eventSrc) { return MidiEventBase::operator = (eventSrc); }
   virtual MidiEventV508 & operator = (const MidiEventV508 & eventSrc) { return MidiEventV508::operator = (eventSrc); }
   virtual MidiEventV016 & operator = (const MidiEventV016 & eventSrc) { return MidiEventV016::operator = (eventSrc); }
   virtual MidiEventV008 & operator = (const MidiEventV001 & eventSrc);

   imedia::position GetPosition() const;
   void SetPosition(imedia::position tkPosition);
   imedia::position GetDelta() const;
   void SetDelta(imedia::position tkDelta);
   BYTE GetFullType() const;
   void SetFullType(BYTE bValue);
   BYTE get_type() const;
   void SetType_(BYTE bValue);
   BYTE GetTrack() const;
   void SetTrack(BYTE bValue);
   BYTE GetMetaType() const;
   void SetMetaType(BYTE bValue);
   BYTE GetChB1() const;
   void SetChB1(BYTE bValue);
   BYTE GetChB2() const;
   void SetChB2(BYTE bValue);
   BYTE GetNotePitch() const;
   void SetNotePitch(BYTE bValue);
   BYTE GetNoteVelocity() const;
   void SetNoteVelocity(BYTE bValue);
   byte * GetParam() const;
   int GetParamSize() const;

   imedia::position _GetPosition() const;
   void _SetPosition(imedia::position tkPosition);

   byte * _GetParam() const;
   int _GetParamSize() const;

#ifndef _DEBUG
   void * operator new(size_t st);
   void operator delete (void *);
#endif

};


