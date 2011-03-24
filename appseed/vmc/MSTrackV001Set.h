#pragma once
#include "MSTrackV001.h"

class CMSDoc;
class CMSEvent;

class CMSTrackV001Set : public BaseArray<CMSTrackV001, CMSTrackV001 &>
{

public:
    CMSTrackV001Set();
	CMSTrackV001Set(CMSDoc * lpDoc);
	virtual ~CMSTrackV001Set();

protected:
    CMSDoc *        m_lpDoc;

public:
	VMSRESULT OpenDoc(CMSDoc *lpDoc);
    VMSRESULT GetNextEventMidi(
        BYTE bType,
        CMSEvent **lppEventMidiParam,
        LPINT lpiTrack,
        LPINT lpiIndex,
        LPDWORD lptkPosition,
        CMSEvents *lpevaSymbols);
    
    VMSRESULT GetNextEventMidi(
        BYTE bType,
        BYTE bPitch,
        CMSEvent **lppEventMidiParam,
        LPINT lpiTrack,
        LPINT lpiIndex,
        LPDWORD lptkPosition,
        CMSEvents *lpevaSymbols);
};

