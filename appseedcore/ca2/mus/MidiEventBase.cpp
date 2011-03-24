#include "StdAfx.h"


DWORD MidiEventBase::SetVDWord(
   byte * hpbImage,
   DWORD dwLeft,
   DWORD dw)
{
    DWORD                   dwUsed  = 0;
   DWORD               dwBuffer;

    ASSERT(hpbImage != NULL);
   ASSERT(dw <= 0x0fffffff);
   
   
   if(!dwLeft)
      return 0;
   dwBuffer = dw & 0x7f;
   dwLeft--;
   dwUsed++;
   while ((dw >>= 7) > 0)
   {
      if(!dwLeft)
         return 0;
      dwBuffer <<= 8;
      dwBuffer |= 0x80;
      dwBuffer |= (dw & 0x7f);
      dwLeft--;
      dwUsed++;
   }
   while (TRUE)
   {
      *hpbImage++ = (BYTE) dwBuffer;
      if (dwBuffer & 0x80)
         dwBuffer >>= 8;
      else
         break;
   }


    return dwUsed;
}


MidiEventBase & MidiEventBase::operator = (const MidiEventBase &eventSrc)
{
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
   SetParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
   SetPosition(eventSrc.GetPosition());
   SetImage(eventSrc.GetImage());
   SetImageSize(eventSrc.GetImageSize());
   SetFlags(eventSrc.GetFlags());
   return *this;
}

MidiEventBase & MidiEventBase::operator = (const MidiEventV008 &eventSrc)
{
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
   SetParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
   SetPosition(eventSrc.GetPosition());
   SetFlags(eventSrc.GetFlags());
   return *this;
}

DWORD MidiEventBase::GetVDWord(
   byte * hpbImage,
   DWORD dwLeft,
   DWORD * pDw)
{
    BYTE                    b;
    DWORD                   dwUsed  = 0;

    ASSERT(hpbImage != NULL);
    ASSERT(pDw != NULL);
    
    *pDw = 0;

    do
    {
        if (!dwLeft)
        {
            return 0;
        }

        b = *hpbImage++;
        dwLeft--;
        dwUsed++;
        
        *pDw = (*pDw << 7) | (b & 0x7F);
    } while (b&0x80);

    return dwUsed;
}

void MidiEventBase::SetParam(primitive::memory & memstorage)
{
   SetParam(
      memstorage.GetAllocation(),
      memstorage.GetStorageSize());
}

int MidiEventBase::GetPitchBendLevel() const
{
   ASSERT(get_type() == ::mus::midi::PitchBend);
   return GetChB1() | (GetChB2() << 8);
}