#include "stdafx.h"
#include "MSEventMidi.h"

#include "mus/MidiEventV001.h"

extern UINT grbChanMsgLen[];

CMSEventMidi::CMSEventMidi()
{
    SetParam(NULL, 0);
    //SetParamSize(0);
}

CMSEventMidi::CMSEventMidi(CMSEvent &event)
{
    memcpy(this, &event, sizeof(CMSEvent));
}

CMSEventMidi::~CMSEventMidi()
{
    DeleteContents();
}

MidiEventBase & CMSEventMidi::operator =(MidiEventBase &eventSrc)
{
	SetFullType(eventSrc.GetFullType());
	SetChB1(eventSrc.GetChB1());
	SetChB2(eventSrc.GetChB2());
	//SetParamSize(eventSrc.GetParamSize());
	//SetParam(eventSrc.GetParam());
    Write(eventSrc.GetParam(), eventSrc.GetParamSize());
	SetDelta(eventSrc.GetDelta());
	//SetPositionTicks(eventSrc.GetPositionTicks());
	//SetImage(eventSrc.GetImage());
	//SetImageSize(eventSrc.GetImageSize());
	return *this;
}

CMSEventMidi & CMSEventMidi::operator =(CMSEventMidi &eventSrc)
{
	SetFullType(eventSrc.GetFullType());
	SetChB1(eventSrc.GetChB1());
	SetChB2(eventSrc.GetChB2());
    Write(eventSrc.GetParam(), eventSrc.GetParamSize());
	//SetParamSize(eventSrc.GetParamSize());
	//SetParam(eventSrc.GetParam());
	SetDelta(eventSrc.GetDelta());
	//SetPositionTicks(eventSrc.GetPositionTicks());
	//SetImage(eventSrc.GetImage());
//	SetImageSize(eventSrc.GetImageSize());
	return *this;
}

CMSEventMidi & CMSEventMidi::operator =(CMSEvent &eventSrc)
{
    if(GetParam() != NULL)
        DeleteContents();
    m_tkDelta = eventSrc.m_tkDelta;
    m_dwEventType = eventSrc.m_dwEventType;
    memcpy(m_lpbData, eventSrc.m_lpbData, sizeof(m_lpbData));
	return *this;
}

VMSRESULT CMSEventMidi::GetMidiEventV001(MidiEventV001 * lpMidiEventV001,  DWORD dwPositionTicks)
{
    lpMidiEventV001->SetFullType(GetFullType());
	lpMidiEventV001->SetChB1(GetChB1());
	lpMidiEventV001->SetChB2(GetChB2());
	//lpMidiEventV001->SetParamSize(GetParamSize());
	lpMidiEventV001->SetParam(GetParam(), GetParamSize());
	lpMidiEventV001->SetDelta(GetDelta());
	lpMidiEventV001->SetPosition(GetPosition());
	lpMidiEventV001->SetImage(NULL);
	lpMidiEventV001->SetImageSize(GetImageSize());
    return VMSR_SUCCESS;
}

VMSRESULT CMSEventMidi::DeleteContents()
{
    if(GetParam() != NULL)
        free(GetParam());
    return VMSR_SUCCESS;
}

VMSRESULT CMSEventMidi::FromData(LPVOID lpData, LPINT lpiLeft)
{
	BYTE                    bEvent;
	int                     iGotTotal;
	DWORD                   dwGot;
	DWORD                   cbEvent;
    HPBYTE                  hpbImage = (HPBYTE) lpData;

    if (*lpiLeft < 3)
    {
        return VMSR_E_INVALIDFILE;
    }
    
    bEvent = *hpbImage++;
    
    if (Midi::Msg > bEvent)
    {
        ASSERT(FALSE);
        iGotTotal = 1;
        //SetFullType(bRunningStatus);
//        m_event.m_abEvent[1] = bEvent;
  //      if (3 == grbChanMsgLen[(m_bRunningStatus >> 4) & 0x0F])
    //    {
      //      m_event.m_abEvent[2] = *m_hpbImage++;
        //    iGotTotal++;
//        }
    }
    else if (Midi::SysEx > bEvent)
    {
  //      m_bRunningStatus = bEvent;
        
        iGotTotal = 2;
        SetFullType(bEvent);
        SetChB1(*hpbImage++);
        if (3 == grbChanMsgLen[(bEvent >> 4) & 0x0F])
        {
            SetChB2(*hpbImage++);
            iGotTotal++;
        }
    }
    else
    {
        //m_bRunningStatus = 0;
        if (Midi::Meta == bEvent)
        {
            SetFullType(Midi::Meta);
            SetMetaType(*hpbImage++);
            if (Midi::MetaEOT == GetMetaType())
            {
                
//                m_fdwTrack |= SMF_TF_EOT;
//				m_smti.m_tkLength = m_tkPosition;
            }

            iGotTotal = 2;
        }
        else if (Midi::SysEx == bEvent || Midi::SysExEnd == bEvent)
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

        Write(hpbImage, cbEvent);

        hpbImage += cbEvent;
        iGotTotal += cbEvent;
    }

    ASSERT(*lpiLeft >= iGotTotal);

    *lpiLeft -= iGotTotal;

    return VMSR_SUCCESS;

}

VMSRESULT CMSEventMidi::Write(LPVOID lpData, int iSize)
{
    HPBYTE hpbParam = GetParam();
    if(iSize <= 0)
    {
        SetParam(NULL, 0);
        //SetParamSize(0);
        free(hpbParam);
        return VMSR_SUCCESS;
    }
    if(hpbParam == NULL)
    {   
        m_iDataRef = 1;
        hpbParam = (HPBYTE) malloc(iSize);
    }
    else
    {
        if(_msize(hpbParam) < (unsigned int) iSize)
        {
            hpbParam = (HPBYTE) realloc(hpbParam, iSize);
        }
    }
    if(hpbParam == NULL)
        return VMSR_E_NOMEMORY;
    memcpy(hpbParam, lpData, iSize);
    m_lpdwData[2] = (DWORD) hpbParam;
    m_lpdwData[1] = iSize;
    //SetParam(hpbParam, iSize);
    //SetParamSize(iSize);
    return VMSR_SUCCESS;
}


int CMSEventMidi::GetFlags() const
{
    //return m_iFlags;
    return 0;
}

void CMSEventMidi::SetFlags(int iFlags)
{
    //m_iFlags = iFlags;
    ASSERT(FALSE);
}

void CMSEventMidi::Clear()
{

}
