// LyricTrack.cpp: implementation of the CMidiLyricTrack class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricTrack.h"

#include "MidiFile.h"
#include "LyricEventsV2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CMidiLyricTrack, CMidiTrackBase)

CMidiLyricTrack::CMidiLyricTrack(CMidiFile * pfile)
{
    m_pfile = pfile;
    m_iDelay = 0;
    


}

CMidiLyricTrack::~CMidiLyricTrack()
{

}

VMSRESULT CMidiLyricTrack::GetNextEventPosition(TICKS *ptkPosition, TICKS tkMax)
{
    if(m_iCurrentEvent >= m_trackWorkStorage.m_events.GetSize())
    {
        return CMidiFile::EndOfTrack;
    }
    CMidiEventV008 & event = m_trackWorkStorage.m_events.ElementAt(m_iCurrentEvent);
    
    TICKS tkPosition = -1;
    if(m_iCurrentEvent == m_iLastEvent &&
        m_iDelay == m_iLastDelay)
    {
        tkPosition = m_tkLastPosition;
    }
    else
    {
        tkPosition = m_tkPosition + event.GetDelta();
        int iMsPosition  = m_pfile->TicksToMillisecs(tkPosition);
        iMsPosition += m_iDelay;
        tkPosition = m_pfile->MillisecsToTicks(iMsPosition);
        m_iLastEvent = m_iCurrentEvent;
        m_iLastDelay = m_iDelay;
        m_tkLastPosition = tkPosition;
    }

    if(tkPosition > tkMax)
    {
        return CMidiFile::ReachedTkMax;
    }
    *ptkPosition = tkPosition;
    return VMSR_SUCCESS;
}

int CMidiLyricTrack::GetFlags()
{
    return m_iFlags;
}

VMSRESULT CMidiLyricTrack::GetEvent(
    CMidiEventBase * pEvent,
    TICKS	tkMax,
	BOOL	bTkMaxInclusive)
{
    if(m_iCurrentEvent > m_trackWorkStorage.m_events.GetSize())
    {
        return CMidiFile::EndOfTrack;
    }
    CMidiEventV008 & event = m_trackWorkStorage.m_events.ElementAt(m_iCurrentEvent);
    TICKS tkPosition = m_tkPosition + event.GetDelta();
    if(tkPosition > tkMax)
    {
        return CMidiFile::ReachedTkMax;
    }
    m_tkPosition = tkPosition;
    *pEvent = event;
    m_iCurrentEvent++;
    return VMSR_SUCCESS;
}

TICKS CMidiLyricTrack::GetPosition()
{
    TICKS tkPosition = m_tkPosition;
    int iMsPosition  = m_pfile->TicksToMillisecs(tkPosition);
    iMsPosition += m_iDelay;
    tkPosition = m_pfile->MillisecsToTicks(iMsPosition);
    return tkPosition;
}

VMSRESULT CMidiLyricTrack::SeekBegin()
{
    m_iCurrentEvent = 0;
    m_tkPosition = 0;
    m_iFlags = 0;
    m_tkLastPosition = -1;
    m_iLastEvent = -1;
    return VMSR_SUCCESS;
}

VMSRESULT CMidiLyricTrack::Prepare(CLyricEventsV1 & events)
{
    m_trackWorkStorage.m_events.RemoveAll();
    CMidiEventV008 event;
    TICKS tkPosition;
    TICKS tkLastPosition = 0;
    events.m_iCurrentToken = 0;
   	CBaseArray<
		CLyricEventV1,
		CLyricEventV1&>	lvaPending;

    while(events.m_iCurrentToken < events.m_tkaTokensPosition.GetSize())
    {
        lvaPending.Add(events);
        tkPosition = events.m_tkaTokensPosition.ElementAt(events.m_iCurrentToken);
        if(tkLastPosition != tkPosition)
        {
            event.SetFlags(1); // Flag 1 means POSITIONCB
            event.SetDelta(tkPosition - tkLastPosition);

           	CMemFile memFile;
	        CArchive ar(&memFile, CArchive::store);
            ar << EVENT_ID_LYRIC_V1;
	        lvaPending.Serialize(ar);
	        ar.Flush();
            DWORD dwLength = memFile.GetLength();
            LPBYTE lpData = memFile.Detach();
            event.SetParam(lpData, dwLength);
            //memFile.Attach(lpData, dwLength);
            lvaPending.RemoveAll();
            m_trackWorkStorage.m_events.Add(event);
        }
        tkLastPosition = tkPosition;
        events.m_iCurrentToken++;
    }

    return VMSR_SUCCESS;
}

VMSRESULT CMidiLyricTrack::Prepare(CLyricEventsV2 & events)
{
    m_trackWorkStorage.m_events.RemoveAll();
    CMidiEventV008 event;
    TICKS tkPosition;
    TICKS tkLastPosition = 0;
    events.m_iCurrentToken = 0;
    events.m_iCurrentNote = 0;
   	CBaseArray<
		CLyricEventV1,
		CLyricEventV1&>	lvaPending;
    CBaseArray<DWORD, DWORD> dwArray;
    //CMemFile memFile;
	//CArchive ar(&memFile, CArchive::store);
    while(events.m_iCurrentNote < events.m_msaNotesPosition.GetSize())
    {
		
        dwArray.RemoveAll();
		events.GetNoteTokens(events.m_iCurrentNote, dwArray);
		if(dwArray.GetSize() > 0)
        {
			events.m_iCurrentToken = dwArray.GetAt(0);
//		else
//			events.m_iCurrentToken = -1;
            lvaPending.Add(events);
            tkPosition = events.m_tkaNotesPosition.ElementAt(events.m_iCurrentNote);
            if(tkLastPosition != tkPosition)
            {

                event.SetFlags(1); // Flag 1 means POSITIONCB
                event.SetDelta(tkPosition - tkLastPosition);
                CMemFile memFile;
	            CArchive ar(&memFile, CArchive::store);
                ar << EVENT_ID_LYRIC_V1;
	            lvaPending.Serialize(ar);
	            ar.Flush();

	            lvaPending.Serialize(ar);
	            ar.Flush();
                DWORD dwLength = memFile.GetLength();
    //            LPBYTE lpData = memFile.Detach();
                memFile.SeekToBegin();
                event.SetParam(memFile);
                m_trackWorkStorage.m_events.Add(event);
                lvaPending.RemoveAll();
            }
            
        }
        tkLastPosition = tkPosition;
        events.m_iCurrentNote++;
    }
    return VMSR_SUCCESS;
}
