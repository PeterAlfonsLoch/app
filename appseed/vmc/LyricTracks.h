// LyricTracks.h: interface for the CLyricTracks class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LYRICTRACKS_H__6841FA98_4175_4937_99BF_2CF9915CC360__INCLUDED_)
#define AFX_LYRICTRACKS_H__6841FA98_4175_4937_99BF_2CF9915CC360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseArray.h"
#include "LyricTrack.h"

class CMidiLyricTracks : public BaseArray<CMidiLyricTrack, CMidiLyricTrack &>
{
public:
	CMidiLyricTracks();
	virtual ~CMidiLyricTracks();
    
    VMSRESULT GetNextEventTkPosition(
        TICKS *					pTkPosition,
        TICKS                   tkMax);

    VMSRESULT GetNextEvent(
        MidiEventV001 *			pEvent,
        TICKS                   tkMax,
	    BOOL					bTkMaxInclusive);

    void SeekBegin();

};

#endif // !defined(AFX_LYRICTRACKS_H__6841FA98_4175_4937_99BF_2CF9915CC360__INCLUDED_)
