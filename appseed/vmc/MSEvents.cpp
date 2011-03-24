#include "stdafx.h"
#include "MSEvents.h"

#include "MSEventMidi.h"
#include "MSEventSymbol.h"


CMSEvents::CMSEvents()
: BaseArray<CMSEvent, CMSEvent>()
{

}

CMSEvents::~CMSEvents()
{

}

VMSRESULT CMSEvents::GetNextEventMidi(
    BYTE bType,
    CMSEvent ** lppEventMidiParam,
    int iIndex,
    LPINT lpiIndex,
    LPDWORD lptkDelta,
    CMSEvents * lpevaSymbols)
{
    CMSEvent *          lpEvent;
    CMSEvent *          lpEventMidi;
    CMSEventMidi        eventMidi;
    bool                bReturn;
    bool                bFirst = true;

    for(int i = iIndex; i < GetSize(); i++)
    {
        eventMidi.SetParam(NULL, 0);
        lpEvent = &ElementAt(i);
        if(lptkDelta != NULL)
            *lptkDelta += lpEvent->m_tkDelta;
        switch(lpEvent->GetEventType())
        {
        case VMS_EVENT_MIDI:
        case VMS_EVENT_MIDI_DELETED:
            lpEventMidi = lpEvent;
            bFirst = false;
            break;
        case VMS_EVENT_SYMBOL:
        case VMS_EVENT_SYMBOL_DELETED:
            lpEventMidi = NULL;
            ASSERT(lpEvent->m_tkDelta == 0);
            if(bFirst)
                if(lpevaSymbols != NULL)
                    lpevaSymbols->Add(*lpEvent);
            break;
        default:;
            lpEventMidi = NULL;
        }
        if(lpEventMidi != NULL)
        {
            eventMidi = *lpEventMidi;
            if(bType == Midi::NoteOn  &&
                eventMidi.GetType() == Midi::NoteOn &&
                eventMidi.GetNoteVelocity() != 0)
            {
                bReturn = true;
            }
            else if(bType == Midi::NoteOff  &&
                (eventMidi.GetType() == Midi::NoteOff ||
                (eventMidi.GetType() == Midi::NoteOn &&
                eventMidi.GetNoteVelocity() == 0)))
            {
                bReturn = true;
            }
            else
            {
                bReturn = false;
            }

            if(bReturn)
            {
                *lppEventMidiParam = lpEventMidi;
                eventMidi.SetParam(NULL, 0);
                if(lpiIndex != NULL)
                    *lpiIndex = i + 1;
                return VMSR_SUCCESS;
            }
        }
   }
   eventMidi.SetParam(NULL, 0);
   return VMSR_S_NOTFOUND;
}


VMSRESULT CMSEvents::GetNextEventMidi(
    BYTE bType,
    BYTE bPitch,
    CMSEvent ** lppEventMidiParam,
    int iIndex,
    LPINT lpiIndex,
    LPDWORD lptkDelta,
    CMSEvents * lpevaSymbols)
{
    VMSRESULT vmsr;
//    CMSEvent *          lpEvent;
    CMSEvent *          lpEventMidi;
    CMSEventMidi        eventMidi;
  //  bool                bReturn;

    while(true)
    {
        if(VMSR_S_NOTFOUND == (vmsr = GetNextEventMidi(bType, &lpEventMidi, iIndex, &iIndex, lptkDelta, lpevaSymbols)))
        {
            eventMidi.SetParam(NULL, 0);
            return vmsr;
        }
        eventMidi = *lpEventMidi;
        if(bPitch == eventMidi.GetNotePitch())
        {
            *lppEventMidiParam = lpEventMidi;
            if(lpiIndex != NULL)
                *lpiIndex = iIndex;
            eventMidi.SetParam(NULL, 0);
            return VMSR_SUCCESS;
        }
    }
}

bool CMSEvents::HasNotes()
{
    CMSEvent *          lpEvent;
    CMSEventSymbol      eventSymbol;
    bool                bOk = false;

    for(int i = 0; i < GetSize(); i++)
    {
        lpEvent = &ElementAt(i);
        switch(lpEvent->GetEventType())
        {
        case VMS_EVENT_MIDI:
        case VMS_EVENT_MIDI_DELETED:
            bOk = false;
            break;
        case VMS_EVENT_SYMBOL:
        case VMS_EVENT_SYMBOL_DELETED:
            bOk = true;
            lpEvent->GetEventSymbol(eventSymbol);
            break;
        default:;
            bOk = false;
        }
        if(bOk)
        {
            if(eventSymbol.IsNote())
                return true;
        }
    }
    return false;
}
VMSRESULT CMSEvents::GetNotesSymbolsIndexes(BaseDWORDArray &dwArray)
{
    CMSEvent *          lpEvent;
    CMSEventSymbol      eventSymbol;
    bool                bOk = false;

    for(int i = 0; i < GetSize(); i++)
    {
        lpEvent = &ElementAt(i);
        switch(lpEvent->GetEventType())
        {
        case VMS_EVENT_MIDI:
        case VMS_EVENT_MIDI_DELETED:
            bOk = false;
            break;
        case VMS_EVENT_SYMBOL:
        case VMS_EVENT_SYMBOL_DELETED:
            bOk = true;
            lpEvent->GetEventSymbol(eventSymbol);
            break;
        default:;
            bOk = false;
        }
        if(bOk)
        {
            dwArray.Add(i);            
        }
    }
    return VMSR_SUCCESS;
}
void CMSEvents::InsertAt(int iIndex, CMSEvent &event)
{
    BaseArray<CMSEvent, CMSEvent>::InsertAt(iIndex, event);
}

void CMSEvents::InsertAt(int iIndex, CMSNotes &notes, LPINT lpiNextIndex)
{
    for(int iNoteIndex = 0; iNoteIndex < notes.GetSize(); iNoteIndex++)
    {
        InsertAt(iIndex, notes.ElementAt(iNoteIndex), &iIndex);
    }
    *lpiNextIndex = iIndex;
}

void CMSEvents::InsertAt(int iIndex, CMSNote &note, LPINT lpiNextIndex)
{
    for(int iNoteIndex = 0; iNoteIndex < note.GetSize(); iNoteIndex++)
    {
        InsertAt(iIndex, note.ElementAt(iNoteIndex), &iIndex);
    }
    *lpiNextIndex = iIndex;
}

void CMSEvents::InsertAt(int iIndex, CMSNoteUnit &noteUnit, LPINT lpiNextIndex)
{
    CMSEventSymbol es(noteUnit);
    InsertAt(iIndex, (CMSEvent &) es);
    if(lpiNextIndex != NULL)
    {
        *lpiNextIndex = iIndex + 1;
    }
}


VMSRESULT CMSEvents::GetNextEventSymbol(
    CMSEvent ** lppEventSymbolParam,
    int iIndex,
    LPINT lpiIndex,
    LPDWORD lptkDelta)
{
    CMSEvent *          lpEvent;

    for(int i = iIndex; i < GetSize(); i++)
    {
        lpEvent = &ElementAt(i);
        if(lptkDelta != NULL)
            *lptkDelta += lpEvent->m_tkDelta;
        switch(lpEvent->GetEventType())
        {
        case VMS_EVENT_SYMBOL:
        case VMS_EVENT_SYMBOL_DELETED:
            if(lpiIndex != NULL)
                *lpiIndex = i + 1;
            *lppEventSymbolParam = lpEvent;
            return VMSR_SUCCESS;
        default:;
        }
   }
   return VMSR_S_NOTFOUND;
}

VMSRESULT CMSEvents::GetPositionEventSymbol(
    CMSEvent ** lppEventSymbolParam,
    int iPosition,
    LPINT lpiIndex,
    LPINT lpiPosition,
    LPDWORD lptkDelta)
{
    CMSEvent *          lpEvent;
    CMSEvent *          lpEventSymbol;
    CMSEventSymbol      eventSymbol;
    CDC dc;
    dc.CreateCompatibleDC(NULL);
    int iPositionPointsLimit = MulDiv(iPosition, 72, dc.GetDeviceCaps(LOGPIXELSY));
    int iPositionPoints = 0;
    
    for(int i = 0; i < GetSize(); i++)
    {
        lpEvent = &ElementAt(i);
        if(lptkDelta != NULL)
            *lptkDelta += lpEvent->m_tkDelta;
        switch(lpEvent->GetEventType())
        {
        case VMS_EVENT_SYMBOL:
        case VMS_EVENT_SYMBOL_DELETED:
            lpEventSymbol = lpEvent;
            lpEvent->GetEventSymbol(eventSymbol);
            iPositionPoints += eventSymbol.GetPositionX();
            if(iPositionPoints > iPositionPointsLimit)
            {
                if(lpiPosition != NULL)
                    *lpiPosition = MulDiv(iPositionPoints, dc.GetDeviceCaps(LOGPIXELSY), 72);
                if(lpiIndex != NULL)
                    *lpiIndex = i;
                *lppEventSymbolParam = lpEventSymbol;
                return VMSR_SUCCESS;
            }
            
        default:;
        }
   }
   return VMSR_S_NOTFOUND;
}

VMSRESULT CMSEvents::UpdateSymbolsDelta()
{
    int iIndex = 0;
    CMSEvent * lpEventSymbol;
    CMSEventSymbol eventSymbol;
    VMSRESULT vmsr;
    int iPositionX = 0;
    while(true)
    {
        if(VMS_FAILED(vmsr = GetNextEventSymbol(&lpEventSymbol, iIndex, &iIndex,  NULL)) ||
            vmsr == VMSR_S_NOTFOUND)
            break;
        eventSymbol = *lpEventSymbol;
        eventSymbol.SetPositionX(eventSymbol.m_iPositionX - iPositionX);
        iPositionX = eventSymbol.m_iPositionX;
        *lpEventSymbol = eventSymbol;
    }
    if(VMS_FAILED(vmsr))
        return vmsr;
    else
        return VMSR_SUCCESS;
}
