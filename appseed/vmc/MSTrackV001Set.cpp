// MSTrackV001Set.cpp: implementation of the CMSTrackV001Set class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSTrackV001Set.h"

#include "MSDoc.h"
#include "MSEvents.h"
#include "MSTrack.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSTrackV001Set::CMSTrackV001Set()
: BaseArray<CMSTrackV001, CMSTrackV001 &>()
{
    m_lpDoc = NULL;
}

CMSTrackV001Set::CMSTrackV001Set(CMSDoc *lpDoc)
: BaseArray<CMSTrackV001, CMSTrackV001 &>()
{
    OpenDoc(lpDoc);
}

CMSTrackV001Set::~CMSTrackV001Set()
{

}

VMSRESULT CMSTrackV001Set::OpenDoc(CMSDoc *lpDoc)
{
    ASSERT(lpDoc != NULL);
    m_lpDoc = lpDoc;
    RemoveAll(false);
    BaseArray<CMSTrack *, CMSTrack *> * lpTracks = lpDoc->GetTracks();
    CMSTrack * lpTrack;
    for(int i = 0; i < lpTracks->GetSize(); i++)
    {
        lpTrack = lpTracks->ElementAt(i);
        CMSTrackV001 trackV001(lpTrack);
        trackV001.SeekBegin();
        Add(trackV001);
    }
    return VMSR_SUCCESS;
}

VMSRESULT CMSTrackV001Set::GetNextEventMidi(
    BYTE bType,
    CMSEvent **lppEventMidiParam,
    LPINT lpiTrack,
    LPINT lpiIndex,
    LPDWORD lptkPosition,
    CMSEvents *lpevaSymbols)
{
    CMSTrackV001 *lpTrack;
    CMSEvents evaSymbols;
    CMSEvents evaFoundSymbols;
    int iIndex, iFoundIndex;
    int iTrack, iFoundTrack;
    DWORD tkFoundPosition = 0xffffffff;
    CMSEvent * lpEventMidi;
    CMSEvent * lpFoundEventMidi = NULL;
    VMSRESULT vmsr;
    for(iTrack = 0; iTrack < GetSize(); iTrack++)
    {
        lpTrack = &ElementAt(iTrack);
        if(VMS_FAILED(vmsr = lpTrack->m_lpTrack->GetEvents()->GetNextEventMidi(
            bType,
            &lpEventMidi,
            lpTrack->m_iCurrentEvent,
            &iIndex,
            NULL,
            lpevaSymbols)) ||
            vmsr == VMSR_S_NOTFOUND)
            continue;
        lpTrack->SeekBegin(iIndex);
        if(lpTrack->m_tkPosition < tkFoundPosition)
        {
            lpFoundEventMidi = lpEventMidi;
            tkFoundPosition = lpTrack->m_tkPosition;
            iFoundTrack = iTrack;
            iFoundIndex = iIndex;
            evaFoundSymbols.RemoveAll();
            evaFoundSymbols.Append(*lpevaSymbols);
        }
    }
    if(lpFoundEventMidi != NULL)
    {
        *lppEventMidiParam = lpFoundEventMidi;
       lpTrack = &ElementAt(iFoundTrack);
       lpTrack->m_iCurrentEvent = iFoundIndex + 1;
        if(lpiTrack != NULL)
           *lpiTrack = iFoundTrack;
        if(lpiIndex != NULL)
            *lpiIndex = iFoundIndex;
        if(lpevaSymbols != NULL)
            lpevaSymbols->Append(evaFoundSymbols);
        if(lptkPosition != NULL)
            *lptkPosition = tkFoundPosition;
        return VMSR_SUCCESS;
    }
    else
    {
        return VMSR_S_NOTFOUND;
    }
}
    
VMSRESULT CMSTrackV001Set::GetNextEventMidi(
    BYTE bType,
    BYTE bPitch,
    CMSEvent **lppEventMidiParam,
    LPINT lpiTrack,
    LPINT lpiIndex,
    LPDWORD lptkPosition,
    CMSEvents *lpevaSymbols)
{
    ASSERT(FALSE);
    return VMSR_E_FAIL;
}
