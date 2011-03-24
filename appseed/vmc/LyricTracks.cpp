// LyricTracks.cpp: implementation of the CMidiLyricTracks class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "LyricTracks.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMidiLyricTracks::CMidiLyricTracks()
{

}

CMidiLyricTracks::~CMidiLyricTracks()
{

}

/*VMSRESULT CMidiLyricTracks::GetNextEventTkPosition(
    TICKS *					pTkPosition,
    TICKS                   tkMax)
{
	CMidiTrack *			pTrk;
	CMidiTrack *			pTrkFound ;
	int						idxTrack;
    TICKS					tkEventDelta;
    TICKS                   tkRelTime;
    TICKS                   tkMinRelTime;
    DWORD                   dwGot;
    

//    ASSERT(pSmf != NULL);
    ASSERT(pTkPosition != NULL);

    if (m_fdwSMF & CMidiFile::FlagEof)
    {
        return CMidiFile::EndOfFile;
    }

    pTrkFound       = NULL;
    tkMinRelTime    = MAX_TICKS;
    
    //for (pTrk = m_rTracks, idxTrack = m_dwTracks; idxTrack--; pTrk++)
	for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
		pTrk = &operator [](idxTrack);
        if (pTrk->m_fdwTrack & SMF_TF_EOT)
            continue;

		if(pTrk->GetState() == CMidiTrack::StateOnDelta)
		{
			if(pTrk->ReadDelta() != CMidiFile::Success)
			{
				TRACE(_T("Hit end of track w/o end marker!\n"));
	            return CMidiFile::InvalidFile;
			}
		}
	
		tkEventDelta = pTrk->m_tkDelta;

	    tkRelTime = pTrk->m_tkPosition + tkEventDelta - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = pTrk;
        }
    }

    if (pTrkFound == NULL)
    {
        m_fdwSMF |= CMidiFile::FlagEof;
        return CMidiFile::EndOfFile;
    }

    pTrk = pTrkFound;

    if (m_tkPosition + tkMinRelTime > tkMax)
    {
        return CMidiFile::ReachedTkMax;
    }
        

    dwGot = pTrk->m_dwUsed;
	tkEventDelta = pTrk->m_tkDelta;
    //pTrk->cbLeft   -= dwGot;

    /* We MUST have at least three bytes here (cause we haven't hit
    ** the end-of-track meta yet, which is three bytes long). Checking
    ** against three means we don't have to check how much is left
    ** in the track again for any short event, which is most cases.
    */
    //if (pTrk->cbLeft < 3)
    //{
        //return CMidiFile::InvalidFile;
    //}

/*    *pTkPosition = pTrk->m_tkPosition + tkEventDelta;

    return CMidiFile::Success;
}

void CMidiLyricTracks::SeekBegin()
{
	for (int i = 0; i < m_nSize; i++)
    {
		CLyricTrack *pTrk = &ElementAt(i);
		pTrk->SeekBegin();
    }
}

VMSRESULT CMidiLyricTracks::GetNextEvent(
    CMidiEventV001 *			pEvent,
    TICKS                   tkMax,
	BOOL					bTkMaxInclusive)
{
	CMidiTrack *			pTrk;
	CMidiTrack *			pTrkFound;
	int						idxTrackFound;
	int						idxTrack;
    TICKS                   tkEventDelta;
    TICKS                   tkRelTime;
    TICKS                   tkMinRelTime;
	SMFRESULT				smfrc;

    ASSERT(pEvent != NULL);


    tkMinRelTime    = MAX_TICKS;
	pTrkFound = NULL;

	for (idxTrack = 0; idxTrack < m_nSize; idxTrack++)
    {
		pTrk = &operator [](idxTrack);
        if (pTrk->m_fdwTrack & SMF_TF_EOT)
            continue;

        
        if (pTrk->GetState() == CMidiTrack::StateOnDelta)
        {
			if(pTrk->ReadDelta() != CMidiFile::Success)
			{
				TRACE(_T("Hit end of track w/o end marker!\n"));
				return CMidiFile::InvalidFile;
			}
        }
		tkEventDelta = pTrk->m_tkDelta;

        tkRelTime = pTrk->m_tkPosition + tkEventDelta - m_tkPosition;

        if (tkRelTime < tkMinRelTime)
        {
            tkMinRelTime = tkRelTime;
            pTrkFound = pTrk;
			idxTrackFound = idxTrack;
        }
    }

    if (pTrkFound == NULL)
    {
        return CMidiFile::EndOfFile;
    }

    pTrk = pTrkFound;

	if(bTkMaxInclusive)
	{
		if (m_tkPosition + tkMinRelTime > tkMax)
		{
			return CMidiFile::ReachedTkMax;
		}
	}
	else
	{
		if (m_tkPosition + tkMinRelTime >= tkMax)
		{
			return CMidiFile::ReachedTkMax;
		}
	}
    
	smfrc = pTrk->ReadEvent(tkMax, bTkMaxInclusive);

	if(smfrc != CMidiFile::Success)
		return smfrc;

	pEvent->operator =(*pTrk->GetEvent());


	pEvent->m_tkDelta = pTrk->m_tkPosition - m_tkPosition;
	m_tkPosition = pTrk->m_tkPosition;
    m_iCurrentTrack = idxTrackFound;

    return CMidiFile::Success;
}
*/