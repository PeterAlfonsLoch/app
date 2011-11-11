#pragma once

class midi_event_v001;



class CLASS_DECL_ca midi_event_v008 :
   public midi_event_v016
{
protected:
   imedia::position          m_tkPosition;
public:
   midi_event_v008();
   midi_event_v008(const midi_event_base &eventSrc);
   midi_event_v008(const midi_event_v001 &eventSrc);
   midi_event_v008(const midi_event_v008 &eventSrc);
   virtual ~midi_event_v008();

   virtual midi_event_base & operator = (const midi_event_base & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_base & operator = (const midi_event_v008 & eventSrc) { return midi_event_base::operator = (eventSrc); }
   virtual midi_event_v508 & operator = (const midi_event_v508 & eventSrc) { return midi_event_v508::operator = (eventSrc); }
   virtual midi_event_v016 & operator = (const midi_event_v016 & eventSrc) { return midi_event_v016::operator = (eventSrc); }
   virtual midi_event_v008 & operator = (const midi_event_v001 & eventSrc);

   imedia::position get_position() const;
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


