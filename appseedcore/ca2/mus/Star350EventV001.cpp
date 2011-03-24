#include "StdAfx.h"

Star350EventV001::Star350EventV001()
{
   m_abEvent[0] = 0;
   m_abEvent[1] = 0;
   m_abEvent[2] = 0;
   m_cbParm  = 0;
   m_hpbParm = 0;
   m_tkDelta = 0;
   m_hpbImage =  0;
   m_cbImage = 0;
   m_pfile = NULL;
   m_ptrack = NULL;
   m_iFlags = 0;
}

Star350EventV001::~Star350EventV001()
{

}

/*MidiEventBase & Star350EventV001::operator = (const MidiEventBase & eventSrc)
{
   return MidiEventBase::operator = (eventSrc);
}*/

Star350EventV001 & Star350EventV001::operator =(const Star350EventV001 &eventSrc)
{
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
   SetParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
   SetPosition(eventSrc.GetPosition());
   SetImage(eventSrc.GetImage());
   SetImageSize(eventSrc.GetImageSize());
   return *this;
}

int Star350EventV001::GetFlags() const
{
    return m_iFlags;
}

void Star350EventV001::SetFlags(int iFlags)
{
    m_iFlags = iFlags;
}


VMSRESULT Star350EventV001::SetParam(ex1::file & file, int iLength)
{
   UNREFERENCED_PARAMETER(file);
   UNREFERENCED_PARAMETER(iLength);
   ASSERT(FALSE);
   return VMSR_E_FAIL;
}

WORD Star350EventV001::GetLyricsOffset() const
{
    ASSERT(FALSE);
    return 0xffff;
}
void Star350EventV001::GetLyricsOffset(WORD iOffset)
{
   UNREFERENCED_PARAMETER(iOffset);
   ASSERT(FALSE);
}

WORD Star350EventV001::GetLyricsCount() const
{
    ASSERT(FALSE);
    return 0xffff;
}

void Star350EventV001::GetLyricsCount(WORD iCount)
{
   UNREFERENCED_PARAMETER(iCount);
   ASSERT(FALSE);
}

void Star350EventV001::clear()
{
   m_abEvent[0] = 0;
   m_abEvent[1] = 0;
   m_abEvent[2] = 0;
   m_cbImage = 0;
   m_cbParm = 0;
   m_hpbImage = 0;
   m_hpbParm = 0;
   m_iFlags = 0;
   m_iType = 0;
   m_pfile = 0;
   m_ptrack = 0;
   m_tkDelta = 0;
   m_tkDuration = 0;
   m_tkPosition = 0;

}


imedia::position Star350EventV001::GetDelta() const
{
   return m_tkDelta;
}

void Star350EventV001::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}

imedia::position Star350EventV001::GetPosition() const
{
   return m_tkPosition;
}

void Star350EventV001::SetPosition(imedia::position tkPosition)
{
   m_tkPosition = tkPosition;
}
BYTE Star350EventV001::GetFullType() const
   {
      return m_abEvent[0];
   }
void Star350EventV001::SetFullType(BYTE bValue)
   {
      m_abEvent[0] = bValue;
   }
BYTE Star350EventV001::get_type() const
   {
      return m_abEvent[0] & 0xf0;
   }
   void Star350EventV001::set_type(BYTE bValue)
   {
      m_abEvent[0] &= 0x0f;
      m_abEvent[0] |= bValue & 0xf0;
   }
   BYTE Star350EventV001::GetTrack() const
   {
      return m_abEvent[0] & 0x0f;
   }
   void Star350EventV001::SetTrack(BYTE bValue)
   {
      m_abEvent[0] &= 0xf0;
      m_abEvent[0] |= bValue & 0x0f;
   }
   BYTE Star350EventV001::GetMetaType() const
   {
      return m_abEvent[1];
   }
   void Star350EventV001::SetMetaType(BYTE bValue)
   {
      m_abEvent[1] = bValue;
   }
   BYTE Star350EventV001::GetChB1() const
   {
      return m_abEvent[1];
   }
   void Star350EventV001::SetChB1(BYTE bValue)
   {
      m_abEvent[1] = bValue;
   }
   BYTE Star350EventV001::GetChB2() const
   {
      return m_abEvent[2];
   }
   void Star350EventV001::SetChB2(BYTE bValue)
   {
      m_abEvent[2] = bValue;
   }
   BYTE Star350EventV001::GetNotePitch() const
   {
      return m_abEvent[1];
   }
   void Star350EventV001::SetNotePitch(BYTE bValue)
   {
      m_abEvent[1] = bValue;
   }
   BYTE Star350EventV001::GetNoteVelocity() const
   {
      return m_abEvent[2];
   }
   void Star350EventV001::SetNoteVelocity(BYTE bValue)
   {
      m_abEvent[2] = bValue;
   }
   byte * Star350EventV001::GetImage() const
   {
      return m_hpbImage;
   }
   void Star350EventV001::SetImage(byte * hpbImage)
   {
      m_hpbImage = hpbImage;
   }

   int Star350EventV001::GetImageSize() const
   {
      return m_cbImage;
   }
   void Star350EventV001::SetImageSize(int cbImage)
   {
      m_cbImage = cbImage;
   }
//   void Star350EventV001::SetParam(byte * hpbParam)
//   {
//      m_hpbParm = hpbParam;
//   }
   void Star350EventV001::SetParam(void * pVoid, int iSize)
   {
      m_hpbParm = (byte *) pVoid;
        m_cbParm = iSize;
   }

   byte * Star350EventV001::GetParam() const
   {
      return m_hpbParm;
   }
//   void Star350EventV001::SetParamSize(DWORD cbSize)
//   {
//      m_cbParm = cbSize;
//   }
   int Star350EventV001::GetParamSize() const
   {
      return m_cbParm;
   }

    imedia::position Star350EventV001::GetDuration() const
{
   return m_tkDuration;
}

void Star350EventV001::SetDuration(imedia::position tkDuration)
{
   m_tkDuration = tkDuration;
}

int Star350EventV001::GetStar350Type() const
{
   return m_iType;
}

void Star350EventV001::SetStar350Type(int iType)
{
   m_iType = iType;
}
