// MSTrack.cpp: implementation of the CMSTrack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSTrack.h"

#include "MSDoc.h"
#include "MSEventMidi.h"
#include "MSEventSymbol.h"
#include "MSHeader.h"
#include "MSQuantize.h"
#include "MSNotes.h"
#include "MSPositions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSTrack::CMSTrack(CMSDoc *pDoc)
:CMSChunk(pDoc)
{
    
}

CMSTrack::~CMSTrack()
{

}


VMSRESULT CMSTrack::Write(bool bInsert)
{
    VMSRESULT vmsr;

    for(int i = 0; i < m_evaData.GetSize(); i++)
    {
        if(VMS_FAILED(vmsr = CMSChunk::Write(&m_evaData.ElementAt(i), bInsert)))
            return vmsr;
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSTrack::Write()
{
    VMSRESULT vmsr;

    if(VMS_FAILED(vmsr =
        SetSize(0)))
        return vmsr;
    
    if(VMS_FAILED(vmsr =
        SeekBegin()))
        return vmsr;

    if(VMS_FAILED(vmsr =
        Write(true)))
        return vmsr;

    if(VMS_FAILED(vmsr =
        CMSChunk::SetHeader(FOURCC_MStk)))
        return vmsr;

    return VMSR_SUCCESS;
}

VMSRESULT CMSTrack::Read()
{
    CMSEvent event;
    VMSRESULT vmsr;

    SeekBegin();
    while(m_evaData.GetSize() > 0)
    {
       m_evaData.RemoveAt(0);
    }
    while(true)
    {
        
        if(VMS_FAILED(vmsr = CMSChunk::Read(&event)))
            return vmsr;
        if(vmsr == VMSR_S_ENDOFFILE)
            return vmsr;
        m_evaData.Add(event);
    }
}


VMSRESULT CMSTrack::DoDefaultNotesCreation(DWORD tkDelta)
{
//    CMSEvent *          lpEvent;
    CMSEventMidi    eventMidiNoteOn;
    CMSEventMidi    eventMidiNoteOnNext;
    CMSEventMidi    eventMidiNoteOff;
    CMSEventMidi    eventMidiNoteOffNext;
    CMSEvent *      lpEventMidiNoteOn;
    CMSEvent *      lpEventMidiNoteOnNext;
    CMSEvent *      lpEventMidiNoteOff;
    CMSEvent *      lpEventMidiNoteOffNext;
    CMSEventSymbol  eventSymbol;
    CMSEvents evaSymbols;
    CMSNotes aNotes;
    DWORD               tkPosition = 0;
    DWORD               tkQuantizedPosition = 0;
    DWORD               tkLastQuantizedPosition = 0;
    int iNoteOnIndex = 0;
    int iNoteOnNextIndex;
    int iNoteOffIndex = 0;
    int iNoteOffNextIndex;
    int iSymbolNextIndex;
    DWORD tkNoteOnDelta = 0;
    DWORD tkNoteOffDelta = 0;
    DWORD tkDuration;
    DWORD tkQuantizedDuration;
    DWORD tkQuarterNote =  m_lpDoc->m_lpHeader->m_midiFileHeader.GetQuarterNoteTicks();
    VMSRESULT vmsr;
    bool bFirst = false;
    while(true)
    {
        evaSymbols.RemoveAll();
        tkNoteOnDelta = 0;
        if(VMS_FAILED(vmsr = m_evaData.GetNextEventMidi(
            Midi::NoteOn,
            &lpEventMidiNoteOnNext,
            iNoteOnIndex,
            &iNoteOnNextIndex,
            &tkNoteOnDelta,
            &evaSymbols)) ||
            vmsr == VMSR_S_NOTFOUND)
            break;
        eventMidiNoteOnNext = *lpEventMidiNoteOnNext;
        tkNoteOffDelta = tkNoteOnDelta;
        iNoteOffIndex = iNoteOnNextIndex;
        m_evaData.GetNextEventMidi(
            Midi::NoteOff,
            eventMidiNoteOnNext.GetNoteVelocity(),
            &lpEventMidiNoteOffNext,
            iNoteOffIndex,
            &iNoteOffNextIndex,
            &tkNoteOffDelta,
            NULL);
        eventMidiNoteOffNext = *lpEventMidiNoteOffNext;
        tkPosition += tkNoteOnDelta;
        if(bFirst)
        {

            aNotes.RemoveAll();
            tkDuration = tkNoteOffDelta;
            if(tkDuration > tkQuarterNote * 4)
                tkDuration = tkQuarterNote * 4;
            CMSQuantize::Quantize(
                tkQuarterNote,
                tkDelta,
                0xffffffff,
                tkPosition,
                &tkQuantizedPosition,
                tkDuration,
                &tkQuantizedDuration,
                &aNotes,
                127 - eventMidiNoteOnNext.GetNotePitch());
            if(!evaSymbols.HasNotes())
            {
                m_evaData.InsertAt(iNoteOnIndex, aNotes, &iSymbolNextIndex);
                iNoteOnIndex = iNoteOnNextIndex - iNoteOnIndex + iSymbolNextIndex;
            }
            else
            {
                iNoteOnIndex = iNoteOnNextIndex;
            }
            tkLastQuantizedPosition = tkQuantizedPosition;
            
        }
        else
        {
            iNoteOnIndex = iNoteOnNextIndex;
        }
        eventMidiNoteOn = eventMidiNoteOnNext;
        eventMidiNoteOff = eventMidiNoteOffNext;
        
        bFirst = true;
    }
    eventMidiNoteOn.SetParam(NULL, 0);
    eventMidiNoteOff.SetParam(NULL, 0);
    eventMidiNoteOnNext.SetParam(NULL, 0);
    eventMidiNoteOffNext.SetParam(NULL, 0);
    return VMSR_SUCCESS;
}


VMSRESULT CMSTrack::DoDefaultNotesSpacing()
{
//    CMSEvent *          lpEvent;
    return VMSR_SUCCESS;
}

int CMSTrack::GetPointsSizeX()
{
    VMSRESULT vmsr;
    int iIndex = 0;
    CMSEvent  *      lpEventSymbol;
    CMSEventSymbol eventSymbol;
    int iSizeX = 0;
    while(VMS_SUCCEEDED(vmsr = m_evaData.GetNextEventSymbol(&lpEventSymbol, iIndex, &iIndex))
        && vmsr != VMSR_S_NOTFOUND)
    {
        eventSymbol = *lpEventSymbol;
        iSizeX += eventSymbol.GetPositionX();
    }
    return iSizeX;

}

int CMSTrack::GetPixelsSizeX()
{
    CDC dc;
    dc.CreateCompatibleDC(NULL);
    return MulDiv(GetPointsSizeX(), dc.GetDeviceCaps(LOGPIXELSX), 72);

}

CMSEvents * CMSTrack::GetEvents()
{
    return &m_evaData;
}
