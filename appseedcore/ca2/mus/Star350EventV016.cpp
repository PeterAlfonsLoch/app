#include "StdAfx.h"
#include "malloc.h"

Star350EventV016::Star350EventV016()
{
    m_iFlags = 0;
    memset(m_lpbData, 0, sizeof(m_lpbData));
}

Star350EventV016::~Star350EventV016()
{

}

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


void Star350EventV016::clear()
{
//    m_tkDelta = 0;
    if(GetParam() != NULL)
    {
        free(GetParam());
    }
    memset(m_lpbData, 0, sizeof(m_lpbData));
    //return VMSR_SUCCESS;
}

VMSRESULT Star350EventV016::GetEventV001(Star350EventV001 * lpMidiEventV001,  DWORD dwPositionTicks)
{
   UNREFERENCED_PARAMETER(dwPositionTicks);
   lpMidiEventV001->SetFullType(GetFullType());
   lpMidiEventV001->SetChB1(GetChB1());
   lpMidiEventV001->SetChB2(GetChB2());
   //   lpMidiEventV001->SetParamSize(GetParamSize());
   lpMidiEventV001->SetParam(GetParam(), GetParamSize());
   lpMidiEventV001->SetDelta(GetDelta());
   lpMidiEventV001->SetPosition(get_position());
   lpMidiEventV001->SetImage(NULL);
   lpMidiEventV001->SetImageSize(GetImageSize());
   return VMSR_SUCCESS;
}


/*Star350EventBase & Star350EventV016::operator =(Star350EventBase &eventSrc)
{
    /*
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
   //SetParamSize(eventSrc.GetParamSize());
   //SetParam(eventSrc.GetParam());
    WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
   //SetPositionTicks(eventSrc.GetPositionTicks());
   //SetImage(eventSrc.GetImage());
   //SetImageSize(eventSrc.GetImageSize());
   return *this;*/
  /*  SetDuration(eventSrc.GetDuration());
    SetStar350Type(eventSrc.GetStar350Type());
   return *this;

}*/

Star350EventV016 & Star350EventV016::operator =(const Star350EventV016 &eventSrc)
{
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
    WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
//   SetDelta(eventSrc.GetDelta());
    return *this;
}



VMSRESULT Star350EventV016::WriteParam(LPVOID lpData, int iSize)
{
    byte * hpbParam = GetParam();
    if(iSize <= 0)
    {
        //SetParam(NULL, 0);
        m_lpdwData[2] = NULL;
        free(hpbParam);
        return VMSR_SUCCESS;
    }
    if(hpbParam == NULL)
    {   
//        m_iDataRef = 1;
        hpbParam = (byte *) malloc(iSize);
    }
    else
    {
        if(_msize(hpbParam) < (unsigned int) iSize)
        {
            hpbParam = (byte *) realloc(hpbParam, iSize);
        }
    }
    if(hpbParam == NULL)
        return VMSR_E_NOMEMORY;
    memcpy(hpbParam, lpData, iSize);
    //SetParam(hpbParam, iSize);
    //SetParamSize(iSize);
    m_lpdwData[2] = (DWORD) hpbParam;
    m_lpdwData[1] = (DWORD) iSize;

    return VMSR_SUCCESS;
}

VMSRESULT Star350EventV016::SetParam(ex1::file & file, int iLength)
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
        iLength = (int) file.get_length();
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

VMSRESULT Star350EventV016::FromData(LPVOID lpData, LPINT lpiLeft, EventType evtype)
{
   BYTE                    bEvent;
   int                     iGotTotal;
   DWORD                   dwGot;
   DWORD                   cbEvent;
    byte *                  hpbImage = (byte *) lpData;

    if(evtype == EventTypeTrackName)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal = 2;
        hpbImage += 2;

        dwGot = *lpw;
        WriteParam(hpbImage, dwGot);

        iGotTotal += dwGot;
        *lpiLeft -= iGotTotal;
    }
    else if(evtype == EventTypeLyrics)
    {
        dwGot = 4;
        memcpy(m_lpbData, hpbImage, dwGot);
        iGotTotal = dwGot;
        *lpiLeft -= iGotTotal;
    }
    else if(evtype == EventTypeLineBreak)
    {
    }
    else if(evtype == EventTypeMidiTempo)
    {
        dwGot = 3;
//        SetFullType(::mus::midi::Meta);
//        SetMetaType(::mus::midi::MetaTempo);
        WriteParam(hpbImage, dwGot);
        iGotTotal = dwGot;
        *lpiLeft -= iGotTotal;
     
    }
    else if(evtype == EventTypeMidi)
    {
        if (*lpiLeft < 3)
        {
            return VMSR_E_INVALIDFILE;
        }
    
        bEvent = *hpbImage++;
    
        if (::mus::midi::Msg > bEvent)
        {
            ASSERT(FALSE);
            iGotTotal = 1;
//            SetFullType(bRunningStatus);
            SetChB1(*hpbImage++);
            if (3 == ::mus::midi::GetMessageLen(bEvent))
            {
                SetChB2(*hpbImage++);
                iGotTotal++;
            }
        }
        else if (::mus::midi::SysEx > bEvent)
        {
//            bRunningStatus = bEvent;
            
            iGotTotal = 2;
            SetFullType(bEvent);
            if(get_type() == 0x90)
            {
//                int i = 1 + 2;
            }
            SetChB1(*hpbImage++);
            if (3 == ::mus::midi::GetMessageLen(bEvent))
            {
                SetChB2(*hpbImage++);
                iGotTotal++;
            }
        }
        else
        {
//            bRunningStatus = 0;
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
        
            if (0 == (dwGot = midi_event_base::GetVDWord(hpbImage, *lpiLeft - iGotTotal, &cbEvent)))
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
    }

    return VMSR_SUCCESS;

}

int Star350EventV016::GetFlags()  const
{
    return m_iFlags;
}

void Star350EventV016::SetFlags(int iFlags)
{
    m_iFlags = iFlags;
}

imedia::position Star350EventV016::GetDuration() const
{
    ASSERT(FALSE);
    return 0x7fffffff;
}

void Star350EventV016::SetDuration(imedia::position tkDelta)
{
   UNREFERENCED_PARAMETER(tkDelta);
   ASSERT(FALSE);
}

int Star350EventV016::GetStar350Type() const
{
    ASSERT(FALSE);
    return 0x7fffffff;
}

void Star350EventV016::SetStar350Type(int iType)
{
   UNREFERENCED_PARAMETER(iType);
   ASSERT(FALSE);
}

WORD Star350EventV016::GetLyricsOffset() const
{
    return m_lpushData[0];
}

void Star350EventV016::GetLyricsOffset(WORD bOffset)
{
    m_lpushData[0] = bOffset;
}
    
WORD Star350EventV016::GetLyricsCount() const
{
    return m_lpushData[1];
}

void Star350EventV016::GetLyricsCount(WORD bCount)
{
    
    m_lpushData[1] = bCount;
    
}

imedia::position Star350EventV016::GetDelta() const
{
    ASSERT(FALSE);
    return -1;
}

void Star350EventV016::SetDelta(imedia::position tkDelta)
{
   UNREFERENCED_PARAMETER(tkDelta);
   ASSERT(FALSE);
}

imedia::position Star350EventV016::get_position() const
{
   ASSERT(FALSE);
    return 0xffffffff;
}

void Star350EventV016::SetPosition(imedia::position tkPosition)
{
   UNREFERENCED_PARAMETER(tkPosition);
   ASSERT(FALSE);
}
BYTE Star350EventV016::GetFullType() const
{
   return m_lpbData[0];
}
void Star350EventV016::SetFullType(BYTE bValue)
{
   m_lpbData[0] = bValue;
}
BYTE Star350EventV016::get_type() const
{
   return m_lpbData[0] & 0xf0;
}
void Star350EventV016::set_type(BYTE bValue)
{
   m_lpbData[0] &= 0x0f;
   m_lpbData[0] |= bValue & 0xf0;
}
BYTE Star350EventV016::GetTrack() const
{
   return m_lpbData[0] & 0x0f;
}
void Star350EventV016::SetTrack(BYTE bValue)
{
   m_lpbData[0] &= 0xf0;
   m_lpbData[0] |= bValue & 0x0f;
}
BYTE Star350EventV016::GetMetaType() const
{
   return m_lpbData[1];
}
void Star350EventV016::SetMetaType(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE Star350EventV016::GetChB1() const
{
   return m_lpbData[1];
}
void Star350EventV016::SetChB1(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE Star350EventV016::GetChB2() const
{
   return m_lpbData[2];
}
void Star350EventV016::SetChB2(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
BYTE Star350EventV016::GetNotePitch() const
{
   return m_lpbData[1];
}
void Star350EventV016::SetNotePitch(BYTE bValue)
{
   m_lpbData[1] = bValue;
}
BYTE Star350EventV016::GetNoteVelocity() const
{
   return m_lpbData[2];
}
void Star350EventV016::SetNoteVelocity(BYTE bValue)
{
   m_lpbData[2] = bValue;
}
byte * Star350EventV016::GetImage() const
{
   return (byte *) m_lpdwData[0];
}

void Star350EventV016::SetImage(byte * hpbImage)
{
   UNREFERENCED_PARAMETER(hpbImage);
   ASSERT(FALSE);
}

int Star350EventV016::GetImageSize() const
{
    ASSERT(FALSE);
    return 0xffffffff;
}

void Star350EventV016::SetImageSize(int cbImage)
{
   UNREFERENCED_PARAMETER(cbImage);
   ASSERT(FALSE);
}

void Star350EventV016::SetParam(void * pVoid, int iSize)
{
   WriteParam(pVoid, iSize);
}

byte * Star350EventV016::GetParam() const
{
   return (byte *) m_lpdwData[2];
}

int Star350EventV016::GetParamSize() const
{
   return m_lpdwData[1];
}
