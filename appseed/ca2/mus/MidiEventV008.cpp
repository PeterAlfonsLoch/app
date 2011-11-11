#include "StdAfx.h"

//extern UINT grbChanMsgLen[];

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

AFX_STATIC fixed_alloc _vmsMidiEventV008Alloc(ROUND4(sizeof(midi_event_v008)), ROUND4(1024));


midi_event_v008::midi_event_v008()
{
}

midi_event_v008::midi_event_v008(const midi_event_base &eventSrc)
{
   operator =(eventSrc);
}

midi_event_v008::midi_event_v008(const midi_event_v001 &eventSrc)
{
   operator =(eventSrc);
}

midi_event_v008::midi_event_v008(const midi_event_v008 &eventSrc)
{
   operator =(eventSrc);
}

midi_event_v008::~midi_event_v008()
{

}

/*midi_event_base & midi_event_v008::operator=(const midi_event_base &eventSrc)
{
   _SetFullType   (eventSrc.GetFullType());
   _SetChB1       (eventSrc.GetChB1());
   _SetChB2       (eventSrc.GetChB2());
    SetParam      (eventSrc.GetParam(), eventSrc.GetParamSize());
   _SetDelta      (eventSrc.GetDelta());
   _SetPosition   (eventSrc.get_position());
   _SetFlags      (eventSrc.GetFlags());
   return *this;
}
*/

midi_event_v008 & midi_event_v008::operator = (const midi_event_v001 & eventSrc)
{
   _SetFullType   (eventSrc._GetFullType());
   _SetChB1       (eventSrc._GetChB1());
   _SetChB2       (eventSrc._GetChB2());
    SetParam      (eventSrc._GetParam(), eventSrc._GetParamSize());
   _SetDelta      (eventSrc._GetDelta());
   _SetPosition   (eventSrc._GetPosition());
   _SetFlags      (eventSrc._GetFlags());

// _SetImage      (eventSrc._GetImage());
// _SetImageSize  (eventSrc._GetImageSize());
   return *this;
}


/*midi_event_v008 & midi_event_v008::operator =(const midi_event_v008 &eventSrc)
{
   _SetFullType   (eventSrc._GetFullType());
   _SetChB1       (eventSrc._GetChB1());
   _SetChB2       (eventSrc._GetChB2());
   _SetDelta      (eventSrc._GetDelta());
   _SetPosition   (eventSrc._GetPosition());
   _SetFlags      (eventSrc._GetFlags());
    SetParam      (eventSrc._GetParam(), eventSrc._GetParamSize());

//   _SetImage(eventSrc._GetImage());
//   _SetImageSize(eventSrc._GetImageSize());
   return *this;
}*/

#ifndef _DEBUG


void * midi_event_v008::operator new(size_t st)
{
   return _vmsMidiEventV008Alloc.Alloc();
}

void midi_event_v008::operator delete (void * p)
{
   _vmsMidiEventV008Alloc.Free(p);
}

#endif _DEBUG



imedia::position midi_event_v008::get_position() const
{
   return m_tkPosition;
}
void midi_event_v008::SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}

imedia::position midi_event_v008::GetDelta() const
{
   return m_tkDelta;
}

void midi_event_v008::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}


BYTE midi_event_v008::GetFullType() const
{
   return m_lpbData[0];
}
void midi_event_v008::SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}
BYTE midi_event_v008::get_type() const
{
   return m_lpbData[0] & 0xf0;
}
void midi_event_v008::SetType_(BYTE bValue)
{
   m_lpbData[0] &= 0x0f;
   m_lpbData[0] |= bValue & 0xf0;
}
BYTE midi_event_v008::GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}
void midi_event_v008::SetTrack(BYTE bValue)
{
   m_lpbData[0] &= 0xf0;
   m_lpbData[0] |= bValue & 0x0f;
}
BYTE midi_event_v008::GetMetaType() const
{
   return m_lpbData[1];
}
void midi_event_v008::SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE midi_event_v008::GetChB1() const
{
   return m_lpbData[1];
}
void midi_event_v008::SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE midi_event_v008::GetChB2() const
{
   return m_lpbData[2];
}
void midi_event_v008::SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
BYTE midi_event_v008::GetNotePitch() const
{
   return m_lpbData[1];
}
void midi_event_v008::SetNotePitch(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE midi_event_v008::GetNoteVelocity() const
{
   return m_lpbData[2];
}
void midi_event_v008::SetNoteVelocity(BYTE bValue)
{
   m_lpbData[2] = bValue;
}


byte * midi_event_v008::GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int midi_event_v008::GetParamSize() const
{
   return m_lpdwData[1];
}


__forceinline imedia::position midi_event_v008::_GetPosition() const
{
   return m_tkPosition;
}
__forceinline void midi_event_v008::_SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}

byte * midi_event_v008::_GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int midi_event_v008::_GetParamSize() const
{
   return m_lpdwData[1];
}


