#include "StdAfx.h"
#include "malloc.h"

MidiEventV508::MidiEventV508()
{
   m_iFlags = 0;
   m_iAllocate = 0;
   m_pvoid = NULL;
   m_lpdwData[0] = 0;
   m_lpdwData[1] = 0;
   m_lpdwData[2] = 0;
}

MidiEventV508::~MidiEventV508()
{

}
#define ROUND(x,y) (((x)+(y-1))&~(y-1))
#define ROUND4(x) ROUND(x, 4)

AFX_STATIC fixed_alloc _vmsAlloc8(ROUND4(8));
AFX_STATIC fixed_alloc _vmsAlloc64(ROUND4(64));
AFX_STATIC fixed_alloc _vmsAlloc128(ROUND4(128));
AFX_STATIC fixed_alloc _vmsAlloc256(ROUND4(256));
AFX_STATIC fixed_alloc _vmsAlloc512(ROUND4(512));

//CMidiEventV007 * CMidiEventV007::operator =(CMidiEventV007 *pEventSrc)
//{
//   abEvent[0]   = pEventSrc->abEvent[0];
//   abEvent[1]   = pEventSrc->abEvent[1];
//   abEvent[2]   = pEventSrc->abEvent[2];
//   cbParm      = pEventSrc->cbParm;
//   hpbParm      = pEventSrc->hpbParm;
//   tkDelta      = pEventSrc->tkDelta;
//   return this;
//}


void MidiEventV508::clear()
{
   memset(m_lpbData, 0, sizeof(m_lpbData));
}
VMSRESULT MidiEventV508::GetMidiEventV001(MidiEventV001 * lpMidiEventV001,  DWORD dwPositionTicks)
{
   UNREFERENCED_PARAMETER(dwPositionTicks);
   lpMidiEventV001->SetFullType(GetFullType());
   lpMidiEventV001->SetChB1(GetChB1());
   lpMidiEventV001->SetChB2(GetChB2());
   //   lpMidiEventV001->SetParamSize(GetParamSize());
   lpMidiEventV001->SetParam(GetParam(), GetParamSize());
   lpMidiEventV001->SetDelta(GetDelta());
   lpMidiEventV001->SetPosition(GetPosition());
   lpMidiEventV001->SetImage(NULL);
   lpMidiEventV001->SetImageSize(GetImageSize());
   return VMSR_SUCCESS;
}


/*MidiEventBase & MidiEventV508::operator =(MidiEventBase &eventSrc)
{
_SetFullType(eventSrc.GetFullType());
_SetChB1(eventSrc.GetChB1());
_SetChB2(eventSrc.GetChB2());
//SetParamSize(eventSrc.GetParamSize());
//SetParam(eventSrc.GetParam());
WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
SetDelta(eventSrc.GetDelta());
//SetPositionTicks(eventSrc.GetPositionTicks());
//SetImage(eventSrc.GetImage());
//SetImageSize(eventSrc.GetImageSize());
SetFlags(eventSrc.GetFlags());
return *this;
}*/

MidiEventV508 & MidiEventV508::operator =(const MidiEventV508 &eventSrc)
{
   _SetFullType(eventSrc._GetFullType());
   _SetChB1(eventSrc._GetChB1());
   _SetChB2(eventSrc._GetChB2());
   WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   _SetFlags(eventSrc._GetFlags());
   //   SetDelta(eventSrc.GetDelta());
   return *this;
}



VMSRESULT MidiEventV508::WriteParam(LPVOID lpData, int iSize)
{
   if(!_Allocate(iSize))
      return VMSR_E_NOMEMORY;
   memcpy(GetParam(), lpData, iSize);
   return VMSR_SUCCESS;
}

VMSRESULT MidiEventV508::SetParam(ex1::file & file, int iLength)
{
   byte * hpbParam = GetParam();
   if(iLength <= 0 && iLength != -1)
   {
      //SetParam(NULL, 0);
      m_lpdwData[2] = NULL;
      free(hpbParam);
      return VMSR_SUCCESS;
   }
   else if(iLength == -1)
   {
      iLength = file.get_length();
   }
   if(hpbParam == NULL)
   {   
      //        m_iDataRef = 1;
      hpbParam = (byte *) malloc(iLength);
   }
   else
   {
      if(_msize(hpbParam) < (unsigned int) iLength)
      {
         hpbParam = (byte *) realloc(hpbParam, iLength);
      }
   }
   if(hpbParam == NULL)
      return VMSR_E_NOMEMORY;
   file.read(hpbParam, iLength);
   //SetParam(hpbParam, iSize);
   //SetParamSize(iSize);
   m_lpdwData[2] = (DWORD) hpbParam;
   m_lpdwData[1] = (DWORD) iLength;

   return VMSR_SUCCESS;
}
VMSRESULT MidiEventV508::FromData(LPVOID lpData, LPINT lpiLeft, BYTE &bRunningStatus)
{
   BYTE                    bEvent;
   int                     iGotTotal;
   DWORD                   dwGot;
   DWORD                   cbEvent;
   byte *                  hpbImage = (byte *) lpData;

   if (*lpiLeft < 3)
   {
      return VMSR_E_INVALIDFILE;
   }

   bEvent = *hpbImage++;

   if (::mus::midi::Msg > bEvent)
   {
      ASSERT(FALSE);
      iGotTotal = 1;
      SetFullType(bRunningStatus);
      SetChB1(*hpbImage++);
      if (3 == ::mus::midi::grbChanMsgLen[(bEvent >> 4) & 0x0F])
      {
         SetChB2(*hpbImage++);
         iGotTotal++;
      }
   }
   else if (::mus::midi::SysEx > bEvent)
   {
      bRunningStatus = bEvent;

      iGotTotal = 2;
      SetFullType(bEvent);
      SetChB1(*hpbImage++);
      if (3 == ::mus::midi::GetMessageLen(bEvent))
      {
         SetChB2(*hpbImage++);
         iGotTotal++;
      }
   }
   else
   {
      bRunningStatus = 0;
      if (::mus::midi::Meta == bEvent)
      {
         SetFullType(::mus::midi::Meta);
         SetMetaType(*hpbImage++);
         if (::mus::midi::MetaEOT == GetMetaType())
         {

            //                m_fdwTrack |= SMF_TF_EOT;
            //            m_smti.m_tkLength = m_tkPosition;
         }

         iGotTotal = 2;
      }
      else if (::mus::midi::SysEx == bEvent || ::mus::midi::SysExEnd == bEvent)
      {
         SetFullType(bEvent);
         iGotTotal = 1;
      }
      else
      {
         return VMSR_E_INVALIDFILE;
      }

      if (0 == (dwGot = MidiEventBase::GetVDWord(hpbImage, *lpiLeft - iGotTotal, &cbEvent)))
      {
         return VMSR_E_INVALIDFILE;
      }

      hpbImage  += dwGot;
      iGotTotal  += dwGot;

      if (iGotTotal + (int) cbEvent > *lpiLeft)
      {
         return VMSR_E_INVALIDFILE;
      }

      WriteParam(hpbImage, cbEvent);

      hpbImage += cbEvent;
      iGotTotal += cbEvent;
   }

   ASSERT(*lpiLeft >= iGotTotal);

   *lpiLeft -= iGotTotal;

   return VMSR_SUCCESS;

}

int MidiEventV508::GetFlags()  const
{
   return m_iFlags;
}

void MidiEventV508::SetFlags(int iFlags)
{
   m_iFlags = iFlags;
}

void MidiEventV508::_Free()
{
   void * pvoid = m_pvoid;
   if(pvoid == NULL)
      return;
   if(m_iAllocate == 8)
   {
      _vmsAlloc8.Free(pvoid);
   }
   else if(m_iAllocate == 64)
   {
      _vmsAlloc64.Free(pvoid);
   }
   else if(m_iAllocate == 128)
   {
      _vmsAlloc128.Free(pvoid);
   }
   else if(m_iAllocate == 256)
   {
      _vmsAlloc256.Free(pvoid);
   }
   else if(m_iAllocate == 512)
   {
      _vmsAlloc512.Free(pvoid);
   }
   else
   {
      free(pvoid);
   }
   m_pvoid = NULL;
   m_iAllocate = 0;
   m_lpdwData[1] = 0;
   m_lpdwData[2] = NULL;
}


bool MidiEventV508::_Allocate(int iSize)
{
   if(iSize == 0)
   {
      _Free();
      return true;
   }
   void * pvoid = m_pvoid;
   bool bFree = pvoid != NULL && (iSize > m_iAllocate);
   if(bFree)
   {
      _Free();
   }
   pvoid = m_pvoid;
   if(pvoid == NULL)
   {   
      if(iSize <= 8)
      {
         pvoid = _vmsAlloc8.Alloc();
         m_iAllocate = 8;
      }
      else if(iSize <= 64)
      {
         pvoid = _vmsAlloc64.Alloc();
         m_iAllocate = 64;
      }
      else if(iSize <= 128)
      {
         pvoid = _vmsAlloc128.Alloc();
         m_iAllocate = 128;
      }
      else if(iSize <= 256)
      {
         pvoid =  _vmsAlloc256.Alloc();
         m_iAllocate = 256;
      }
      else if(iSize <= 512)
      {
         pvoid =  _vmsAlloc512.Alloc();
         m_iAllocate = 512;
      }
      else
      {
         pvoid = malloc(iSize);
         m_iAllocate = iSize;
      }
      if(pvoid == NULL)
         return false;
   }
   else
   {
   }

   m_pvoid        = pvoid;
   m_lpdwData[1]  = iSize;
   m_lpdwData[2]  = (DWORD) pvoid;

   return true;
}

void MidiEventV508::SetParamSize(int iSize)
{
   UNREFERENCED_PARAMETER(iSize);
   throw not_implemented_exception();
}



imedia::position MidiEventV508::GetDelta() const
{
    return 0;
}

void MidiEventV508::SetDelta(imedia::position tkDelta)
{
   UNREFERENCED_PARAMETER(tkDelta);
   ASSERT(FALSE);
}

imedia::position MidiEventV508::GetPosition() const
{
   return 0xffffffff;
}

void MidiEventV508::SetPosition(imedia::position tkPosition)
{
   UNREFERENCED_PARAMETER(tkPosition);
   ASSERT(FALSE);
}

BYTE MidiEventV508::GetFullType() const
{
   return m_lpbData[0];
}

void MidiEventV508::SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}

BYTE MidiEventV508::get_type() const
{
   return m_lpbData[0] & 0xf0;
}

void MidiEventV508::set_type(BYTE bValue)
{
   m_lpbData[0] &= 0x0f;
   m_lpbData[0] |= bValue & 0xf0;
}
BYTE MidiEventV508::GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}
void MidiEventV508::SetTrack(BYTE bValue)
{
   m_lpbData[0] &= 0xf0;
   m_lpbData[0] |= bValue & 0x0f;
}
BYTE MidiEventV508::GetMetaType() const
{
   return m_lpbData[1];
}
void MidiEventV508::SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV508::GetChB1() const
{
   return m_lpbData[1];
}
void MidiEventV508::SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV508::GetChB2() const
{
   return m_lpbData[2];
}
void MidiEventV508::SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
BYTE MidiEventV508::GetNotePitch() const
{
   return m_lpbData[1];
}
void MidiEventV508::SetNotePitch(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE MidiEventV508::GetNoteVelocity() const
{
   return m_lpbData[2];
}
void MidiEventV508::SetNoteVelocity(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
byte * MidiEventV508::GetImage() const
{
   return (byte *) m_lpdwData[0];
}

void MidiEventV508::SetImage(byte * hpbImage)
{
   UNREFERENCED_PARAMETER(hpbImage);
   ASSERT(FALSE);
}

int MidiEventV508::GetImageSize() const
{
    return 0xffffffff;
}
void MidiEventV508::SetImageSize(int cbImage)
{
   UNREFERENCED_PARAMETER(cbImage);
   ASSERT(FALSE);
}

void MidiEventV508::SetParam(void * pVoid, int iSize)
{
   WriteParam(pVoid, iSize);
}

byte * MidiEventV508::GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int MidiEventV508::GetParamSize() const
{
   return m_lpdwData[1];
}

BYTE MidiEventV508::_GetType() const
{
   return m_lpbData[0] & 0xf0;
}

BYTE MidiEventV508::_GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}

BYTE MidiEventV508::_GetFullType() const
{
   return m_lpbData[0];
}

BYTE MidiEventV508::_GetMetaType() const
{
   return m_lpbData[1];
}

void MidiEventV508::_SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}

void MidiEventV508::_SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}

BYTE MidiEventV508::_GetChB1() const
{
   return m_lpbData[1];
}

void MidiEventV508::_SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}

BYTE MidiEventV508::_GetChB2() const
{
   return m_lpbData[2];
}

void MidiEventV508::_SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}

byte * MidiEventV508::_GetImage() const
{
   return (byte *) m_lpdwData[0];
}

void MidiEventV508::_SetImage(byte * hpbImage)
{
   UNREFERENCED_PARAMETER(hpbImage);
   ASSERT(FALSE);
}

int MidiEventV508::_GetImageSize() const
{
    return 0xffffffff;
}
void MidiEventV508::_SetImageSize(int cbImage)
{
   UNREFERENCED_PARAMETER(cbImage);
   ASSERT(FALSE);
}

int MidiEventV508::_GetFlags()  const
{
    return m_iFlags;
}

void MidiEventV508::_SetFlags(int iFlags)
{
    m_iFlags = iFlags;
}
