#include "StdAfx.h"

//extern UINT grbChanMsgLen[];

#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

AFX_STATIC fixed_alloc _vmsMidiEventV008Alloc(ROUND4(sizeof(MidiEventV008)), ROUND4(1024));


MidiEventV008::MidiEventV008()
{
}

MidiEventV008::MidiEventV008(const MidiEventBase &eventSrc)
{
   operator =(eventSrc);
}

MidiEventV008::MidiEventV008(const MidiEventV001 &eventSrc)
{
   operator =(eventSrc);
}

MidiEventV008::MidiEventV008(const MidiEventV008 &eventSrc)
{
   operator =(eventSrc);
}

MidiEventV008::~MidiEventV008()
{

}

/*MidiEventBase & MidiEventV008::operator=(const MidiEventBase &eventSrc)
{
   _SetFullType   (eventSrc.GetFullType());
   _SetChB1       (eventSrc.GetChB1());
   _SetChB2       (eventSrc.GetChB2());
    SetParam      (eventSrc.GetParam(), eventSrc.GetParamSize());
   _SetDelta      (eventSrc.GetDelta());
   _SetPosition   (eventSrc.GetPosition());
   _SetFlags      (eventSrc.GetFlags());
   return *this;
}
*/

MidiEventV008 & MidiEventV008::operator = (const MidiEventV001 & eventSrc)
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


/*MidiEventV008 & MidiEventV008::operator =(const MidiEventV008 &eventSrc)
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


void * MidiEventV008::operator new(size_t st)
{
   return _vmsMidiEventV008Alloc.Alloc();
}

void MidiEventV008::operator delete (void * p)
{
   _vmsMidiEventV008Alloc.Free(p);
}

#endif _DEBUG



imedia::position MidiEventV008::GetPosition() const
{
   return m_tkPosition;
}
void MidiEventV008::SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}

imedia::position MidiEventV008::GetDelta() const
{
   return m_tkDelta;
}

void MidiEventV008::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}


BYTE MidiEventV008::GetFullType() const
{
   return m_lpbData[0];
}
void MidiEventV008::SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}
BYTE MidiEventV008::get_type() const
{
   return m_lpbData[0] & 0xf0;
}
void MidiEventV008::SetType_(BYTE bValue)
{
   m_lpbData[0] &= 0x0f;
   m_lpbData[0] |= bValue & 0xf0;
}
BYTE MidiEventV008::GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}
void MidiEventV008::SetTrack(BYTE bValue)
{
   m_lpbData[0] &= 0xf0;
   m_lpbData[0] |= bValue & 0x0f;
}
BYTE MidiEventV008::GetMetaType() const
{
   return m_lpbData[1];
}
void MidiEventV008::SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV008::GetChB1() const
{
   return m_lpbData[1];
}
void MidiEventV008::SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV008::GetChB2() const
{
   return m_lpbData[2];
}
void MidiEventV008::SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
BYTE MidiEventV008::GetNotePitch() const
{
   return m_lpbData[1];
}
void MidiEventV008::SetNotePitch(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV008::GetNoteVelocity() const
{
   return m_lpbData[2];
}
void MidiEventV008::SetNoteVelocity(BYTE bValue)
{
   m_lpbData[2] = bValue;
}


byte * MidiEventV008::GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int MidiEventV008::GetParamSize() const
{
   return m_lpdwData[1];
}


__forceinline imedia::position MidiEventV008::_GetPosition() const
{
   return m_tkPosition;
}
__forceinline void MidiEventV008::_SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}

byte * MidiEventV008::_GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int MidiEventV008::_GetParamSize() const
{
   return m_lpdwData[1];
}


