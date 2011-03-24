#include "StdAfx.h"
#include "malloc.h"


//extern UINT grbChanMsgLen[];
MidiEventV016::MidiEventV016()
{
    m_tkDelta = 0;
    m_iFlags = 0;
}

MidiEventV016::MidiEventV016(MidiEventV016 & event)
{
   operator =(event);
}

MidiEventV016::~MidiEventV016()
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


void MidiEventV016::clear()
{
    m_tkDelta = 0;
   MidiEventV508::clear();
}
VMSRESULT MidiEventV016::GetMidiEventV001(MidiEventV001 * lpMidiEventV001,  DWORD dwPositionTicks)
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


/*MidiEventBase & MidiEventV016::operator =(MidiEventBase &eventSrc)
{
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
    SetFlags(eventSrc.GetFlags());
   return *this;
}*/

MidiEventV016 & MidiEventV016::operator =(const MidiEventV016 &eventSrc)
{
   SetFullType(eventSrc.GetFullType());
   SetChB1(eventSrc.GetChB1());
   SetChB2(eventSrc.GetChB2());
    WriteParam(eventSrc.GetParam(), eventSrc.GetParamSize());
   SetDelta(eventSrc.GetDelta());
    SetFlags(eventSrc.GetFlags());
    return *this;
}



VMSRESULT MidiEventV016::WriteParam(LPVOID lpData, int iSize)
{
   return MidiEventV508::WriteParam(lpData, iSize);
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

VMSRESULT MidiEventV016::FromData(LPVOID lpData, LPINT lpiLeft, BYTE &bRunningStatus)
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

