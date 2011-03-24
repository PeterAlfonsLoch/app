#include "StdAfx.h"
#include "malloc.h"

Star350EventV008::Star350EventV008()
{
    m_tkDelta = 0;
    m_iFlags = 0;
}

Star350EventV008::~Star350EventV008()
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


void Star350EventV008::clear()
{
    m_tkDelta = 0;
    if(GetParam() != NULL)
    {
        free(GetParam());
    }
    memset(m_lpbData, 0, sizeof(m_lpbData));
//    return VMSR_SUCCESS;
}
VMSRESULT Star350EventV008::GetEventV001(Star350EventV001 * lpMidiEventV001,  DWORD dwPositionTicks)
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


/*Star350EventBase & Star350EventV008::operator =(Star350EventBase &eventSrc)
{
//   SetFullType(eventSrc.GetFullType());
//   SetChB1(eventSrc.GetChB1());
//   SetChB2(eventSrc.GetChB2());
   //SetParamSize(eventSrc.GetParamSize());
   //SetParam(eventSrc.GetParam());
  //  WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   //SetDelta(eventSrc.GetDelta());
   //SetPositionTicks(eventSrc.GetPositionTicks());
   //SetImage(eventSrc.GetImage());
   //SetImageSize(eventSrc.GetImageSize());
    //SetFlags(eventSrc.GetFlags());
    SetDuration(eventSrc.GetDuration());
    SetStar350Type(eventSrc.GetStar350Type());
   return *(Star350EventBase *)this;
}*/

Star350EventV008 & Star350EventV008::operator =(const Star350EventV008 &eventSrc)
{
    SetStar350Type(eventSrc.GetStar350Type());
    SetDuration(eventSrc.GetDuration());
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
    WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
    SetFlags(eventSrc.GetFlags());
    return *this;
}



VMSRESULT Star350EventV008::WriteParam(LPVOID lpData, int iSize)
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

//VMSRESULT Star350EventV008::FromData(LPVOID lpData, LPINT lpiLeft, BYTE &bRunningStatus)
VMSRESULT Star350EventV008::FromData(LPVOID lpData, LPINT lpiLeft, Star350EventBase::EventType eeventtype)
{
   UNREFERENCED_PARAMETER(eeventtype);
   int                     iGotTotal = 0;
   DWORD                   dwGot;
   DWORD                   dwDelta;
   DWORD                   dwDuration;
   int                     iType;
   byte *                  hpbImage = (byte *) lpData;

    //////////////////////////////
    // Getting Delta /////////////
    //////////////////////////////

    if (*lpiLeft < 6) // est・correto ???ｿｿｿ
    {
        return VMSR_E_INVALIDFILE;
    }

    dwGot = MidiEventBase::GetVDWord(
        hpbImage, 
        *lpiLeft,
        &dwDelta);
    
    if (dwGot <= 0)
    {
        return VMSR_E_INVALIDFILE;
    }

    iGotTotal += dwGot;
    hpbImage  += dwGot;

    m_tkDelta = dwDelta;

    //////////////////////////////
    // Getting Duration //////////
    //////////////////////////////

    if (*lpiLeft < 5) // est・correto ???ｿｿｿ
    {
        return VMSR_E_INVALIDFILE;
    }

    dwGot = MidiEventBase::GetVDWord(
        hpbImage, 
        *lpiLeft,
        &dwDuration);
    
    if (dwGot <= 0)
    {
        return VMSR_E_INVALIDFILE;
    }

    iGotTotal += dwGot;
    hpbImage  += dwGot;

    m_tkDuration = dwDuration;

    //////////////////////////////
    // Getting Type //////////////
    //////////////////////////////

    if (*lpiLeft < 5) // est・correto ???ｿｿｿ
    {
        return VMSR_E_INVALIDFILE;
    }

    dwGot = MidiEventBase::GetVDWord(
        hpbImage, 
        *lpiLeft,
        (DWORD *)&iType);
    
    if (dwGot <= 0)
    {
        return VMSR_E_INVALIDFILE;
    }

    iGotTotal += dwGot;
    hpbImage  += dwGot;

    m_iType = iType;

    


    ///////////////////////////////
    // Getting Event //////////////
    ///////////////////////////////
    VMSRESULT vmsr = VMSR_SUCCESS;
    EventType evtype = (EventType) GetStar350Type();
//    if(evtype == EventTypeTrackName)
  //  {
    //    WORD * lpw = (WORD *) hpbImage;
//
  //      iGotTotal += 2;
      //  iGotTotal += *lpw;
    //    vmsr = VMSR_S_SKIP;
    //}
    
    if(evtype == EventTypeCopyright)
    //else if(evtype == EventTypeCopyright)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
//        vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeInstrumentName)
    //else if(evtype == EventTypeCopyright)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
  //      vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMidiLyric)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
    //    vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeImage)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
      //  vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeText)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
        //vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventType123)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
        //vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMidiMeta)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
        //vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMidiSysEx)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
        //vmsr = VMSR_S_SKIP;
    }
//    else if(evtype == EventTypeMidiTempo)
  //  {
    //    iGotTotal += 3;
      //  vmsr = VMSR_S_SKIP;
    //}
    else if(evtype == EventTypeMidiTimeSignature)
    {
        iGotTotal += 4;
        //vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMidiKeySignature)
    {
        iGotTotal += 2;
        //vmsr = VMSR_S_SKIP;
    }
//    else if(evtype == EventTypeLyrics)
  //  {
    //    iGotTotal += 4;
      //  vmsr = VMSR_S_SKIP;
    //}
    else if(evtype == EventTypeLineBreak)
    {
        iGotTotal += 4;
//        vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeNextLine)
    {
        iGotTotal += 4;
//        vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMarker)
    {
        WORD * lpw = (WORD *) hpbImage;

        iGotTotal += 2;
        iGotTotal += *lpw;
        //vmsr = VMSR_S_SKIP;
    }
    else if(evtype == EventTypeMidi ||
        evtype == EventTypeLyrics ||
        evtype == EventTypeMidiTempo ||
        evtype == EventTypeTrackName)
    {
//        *lpiLeft -= iGotTotal;
        vmsr  = Star350EventV016::FromData(hpbImage, lpiLeft, (EventType) GetStar350Type());
    }
    else
    {
        // Aten鈬o
        ASSERT(FALSE);
        vmsr = VMSR_S_SKIP;
    }

    *lpiLeft -= iGotTotal;
    return vmsr;
}


imedia::position Star350EventV008::GetDelta() const
{
   return m_tkDelta;
}

void Star350EventV008::SetDelta(imedia::position tkDelta)
{
   m_tkDelta = tkDelta;
}

imedia::position Star350EventV008::GetDuration() const
{
   return m_tkDuration;
}

void Star350EventV008::SetDuration(imedia::position tkDuration)
{
   m_tkDuration = tkDuration;
}

int Star350EventV008::GetStar350Type() const
{
   return m_iType;
}

void Star350EventV008::SetStar350Type(int iType)
{
   m_iType = iType;
}
