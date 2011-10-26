#include "StdAfx.h"

midi_event_v001::midi_event_v001()
{
   m_abEvent[0] = 0;
   m_abEvent[1] = 0;
   m_abEvent[2] = 0;
   m_cbParm  = 0;
   m_hpbParm = 0;
   m_tkDelta = 0;
   m_hpbImage =  0;
   m_cbImage = 0;
   m_pFile = NULL;
   m_pTrack = NULL;
   m_iFlags = 0;

}

midi_event_v001::~midi_event_v001()
{

}



//midi_event_v001 * midi_event_v001::operator =(midi_event_v001 *pEventSrc)
//{
//   abEvent[0]   = pEventSrc->abEvent[0];
//   abEvent[1]   = pEventSrc->abEvent[1];
//   abEvent[2]   = pEventSrc->abEvent[2];
//   cbParm      = pEventSrc->cbParm;
//   hpbParm      = pEventSrc->hpbParm;
//   tkDelta      = pEventSrc->tkDelta;
//   return this;
//}






midi_event_v001 & midi_event_v001::operator =(const midi_event_v001 &eventSrc)
{
   _SetFullType   (eventSrc._GetFullType());
   _SetChB1       (eventSrc._GetChB1());
   _SetChB2       (eventSrc._GetChB2());
   _SetParam      (eventSrc._GetParam(), eventSrc._GetParamSize());
   _SetDelta      (eventSrc._GetDelta());
   _SetPosition   (eventSrc._GetPosition());
   _SetImage      (eventSrc._GetImage());
   _SetImageSize  (eventSrc._GetImageSize());
   _SetFlags      (eventSrc._GetFlags());
   return *this;
}

/*midi_event_base & midi_event_v001::operator = (const midi_event_v008 &eventSrc)
{
_SetFullType   (eventSrc._GetFullType());
_SetChB1       (eventSrc._GetChB1());
_SetChB2       (eventSrc._GetChB2());
_SetParam      (eventSrc._GetParam(), eventSrc._GetParamSize());
_SetDelta      (eventSrc._GetDelta());
_SetPosition   (eventSrc._GetPosition());
_SetImage      (eventSrc._GetImage());
_SetImageSize  (eventSrc._GetImageSize());
_SetFlags      (eventSrc._GetFlags());
return *this;
}

midi_event_base & midi_event_v001::operator =(const midi_event_base &eventSrc)
{
SetFullType(eventSrc.GetFullType());
SetChB1(eventSrc.GetChB1());
SetChB2(eventSrc.GetChB2());
SetParam(eventSrc.GetParam(), eventSrc.GetParamSize());
SetDelta(eventSrc.GetDelta());
SetPosition(eventSrc.get_position());
SetImage(eventSrc.GetImage());
SetImageSize(eventSrc.GetImageSize());
SetFlags(eventSrc.GetFlags());
return *this;
}*/

int midi_event_v001::GetFlags() const
{
   return m_iFlags;
}

void midi_event_v001::SetFlags(int iFlags)
{
   m_iFlags = iFlags;
}


VMSRESULT midi_event_v001::SetParam(ex1::file & file, int iLength)
{
   UNREFERENCED_PARAMETER(file);
   UNREFERENCED_PARAMETER(iLength);
   ASSERT(FALSE);
   return VMSR_E_FAIL;
}


void midi_event_v001::clear()
{
   m_abEvent[0] = 0;
   m_abEvent[1] = 0;
   m_abEvent[2] = 0;
   m_cbImage = 0;
   m_cbParm = 0;
   m_hpbImage = 0;
   m_hpbParm = 0;
   m_iFlags = 0;
   m_pFile = 0;
   m_pTrack = 0;
   m_tkDelta = 0;
   m_tkPosition = 0;


}



imedia::position midi_event_v001::GetDelta() const
{
   return m_tkDelta;
}

void midi_event_v001::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}

imedia::position midi_event_v001::get_position() const
{
   return m_tkPosition;
}

void midi_event_v001::SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}
BYTE midi_event_v001::GetFullType() const
{
   return m_abEvent[0];
}
void midi_event_v001::SetFullType(BYTE bValue)
{
   m_abEvent[0] = bValue;
}
BYTE midi_event_v001::get_type() const
{
   return m_abEvent[0] & 0xf0;
}

void midi_event_v001::set_type(BYTE bValue)
{
   m_abEvent[0] &= 0x0f;
   m_abEvent[0] |= bValue & 0xf0;
}

BYTE midi_event_v001::GetTrack() const
{
   return m_abEvent[0] & 0x0f;
}
void midi_event_v001::SetTrack(BYTE bValue)
{
   m_abEvent[0] &= 0xf0;
   m_abEvent[0] |= bValue & 0x0f;
}
BYTE midi_event_v001::GetMetaType() const
{
   return m_abEvent[1];
}
void midi_event_v001::SetMetaType(BYTE bValue)
{
   m_abEvent[1] = bValue;
}
BYTE midi_event_v001::GetChB1() const
{
   return m_abEvent[1];
}
void midi_event_v001::SetChB1(BYTE bValue)
{
   m_abEvent[1] = bValue;
}
BYTE midi_event_v001::GetChB2() const
{
   return m_abEvent[2];
}
void midi_event_v001::SetChB2(BYTE bValue)
{
   m_abEvent[2] = bValue;
}
BYTE midi_event_v001::GetNotePitch() const
{
   return m_abEvent[1];
}
void midi_event_v001::SetNotePitch(BYTE bValue)
{
   m_abEvent[1] = bValue;
}
BYTE midi_event_v001::GetNoteVelocity() const
{
   return m_abEvent[2];
}
void midi_event_v001::SetNoteVelocity(BYTE bValue)
{
   m_abEvent[2] = bValue;
}
byte * midi_event_v001::GetImage() const
{
   return m_hpbImage;
}
void midi_event_v001::SetImage(byte * hpbImage)
{
   m_hpbImage = hpbImage;
}

int midi_event_v001::GetImageSize() const
{
   return m_cbImage;
}
void midi_event_v001::SetImageSize(int cbImage)
{
   m_cbImage = cbImage;
}
//   void midi_event_v001::SetParam(byte * hpbParam)
//   {
//      m_hpbParm = hpbParam;
//   }
void midi_event_v001::SetParam(void * pVoid, int iSize)
{
   m_hpbParm = (byte *) pVoid;
   m_cbParm = iSize;
}

byte * midi_event_v001::GetParam() const
{
   return m_hpbParm;
}
int midi_event_v001::GetParamSize() const
{
   return m_cbParm;
}

index midi_event_v001::CompareTkPosition(midi_event_v001 * p1, midi_event_v001 * p2)
{
   if(p1->m_tkPosition > p2->m_tkPosition)
      return 1;
   else if(p1->m_tkPosition < p2->m_tkPosition)
      return -1;
   else 
      return 0;
}
void midi_event_v001::swap(midi_event_v001 * p1, midi_event_v001 * p2)
{
   midi_event_v001 ev;
   ev = *p1;
   *p1 = *p2;
   *p2 = ev;
}





imedia::position midi_event_v001::_GetDelta() const
{
   return m_tkDelta;
}

void  midi_event_v001::_SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}

imedia::position midi_event_v001::_GetPosition() const
{
   return m_tkPosition;
}

void  midi_event_v001::_SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}

BYTE  midi_event_v001::_GetFullType() const
{
   return m_abEvent[0];
}

void  midi_event_v001::_SetFullType(BYTE bValue)
{
   m_abEvent[0] = bValue;
}

BYTE  midi_event_v001::_GetType() const
{
   return m_abEvent[0] & 0xf0;
}

void midi_event_v001::_SetType(BYTE bValue)
{
   m_abEvent[0] &= 0x0f;
   m_abEvent[0] |= bValue & 0xf0;
}

BYTE midi_event_v001::_GetTrack() const
{
   return m_abEvent[0] & 0x0f;
}

void midi_event_v001::_SetTrack(BYTE bValue)
{
   m_abEvent[0] &= 0xf0;
   m_abEvent[0] |= bValue & 0x0f;
}

BYTE midi_event_v001::_GetMetaType() const
{
   return m_abEvent[1];
}

void midi_event_v001::_SetMetaType(BYTE bValue)
{
   m_abEvent[1] = bValue;
}

BYTE midi_event_v001::_GetChB1() const
{
   return m_abEvent[1];
}

void midi_event_v001::_SetChB1(BYTE bValue)
{
   m_abEvent[1] = bValue;
}

BYTE midi_event_v001::_GetChB2() const
{
   return m_abEvent[2];
}

void midi_event_v001::_SetChB2(BYTE bValue)
{
   m_abEvent[2] = bValue;
}

BYTE midi_event_v001::_GetNotePitch() const
{
   return m_abEvent[1];
}

void midi_event_v001::_SetNotePitch(BYTE bValue)
{
   m_abEvent[1] = bValue;
}

BYTE midi_event_v001::_GetNoteVelocity() const
{
   return m_abEvent[2];
}

void midi_event_v001::_SetNoteVelocity(BYTE bValue)
{
   m_abEvent[2] = bValue;
}

byte * midi_event_v001::_GetImage() const
{
   return m_hpbImage;
}

void midi_event_v001::_SetImage(byte * hpbImage)
{
   m_hpbImage = hpbImage;
}

int midi_event_v001::_GetImageSize() const
{
   return m_cbImage;
}

void midi_event_v001::_SetImageSize(int cbImage)
{
   m_cbImage = cbImage;
}

void midi_event_v001::_SetParam(void * pVoid, int iSize)
{
   m_hpbParm = (byte *) pVoid;
   m_cbParm = iSize;
}

byte * midi_event_v001::_GetParam() const
{
   return m_hpbParm;
}

int midi_event_v001::_GetParamSize() const
{
   return m_cbParm;
}

int midi_event_v001::_GetFlags() const
{
   return m_iFlags;
}

void midi_event_v001::_SetFlags(int iFlags)
{
   m_iFlags = iFlags;
}
