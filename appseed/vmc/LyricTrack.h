#pragma once

#include "MidiTrackBase.h"
#include "MidiTrackV008.h"
#include "Midi.h"	// Added by ClassView
#include "VMSException.h"	// Added by ClassView

class CLyricEventsV1;
class CLyricEventsV2;


class CMidiLyricTrack : public MidiTrackBase
{
    DECLARE_DYNAMIC(CMidiLyricTrack)
public:
	CMidiLyricTrack(MidiFile * pfile = NULL);
	virtual ~CMidiLyricTrack();

public:
	VMSRESULT Prepare(CLyricEventsV1 & events);
    VMSRESULT Prepare(CLyricEventsV2 & events);
	VMSRESULT SeekBegin();
	TICKS GetPosition();
    virtual VMSRESULT GetNextEventPosition(TICKS *tkPosition, TICKS tkMax);
    virtual int GetFlags();
    virtual VMSRESULT GetEvent(
        MidiEventBase * pEvent,
		TICKS	tkMax,
		BOOL	bTkMaxInclusive);
    MidiFile *     m_pfile;
    int             m_iDelay; // in milliseconds
protected:
    MidiTrackV008  m_trackWorkStorage;
    int             m_iFlags;
    TICKS           m_tkPosition;
    int             m_iCurrentEvent;
    
    TICKS           m_tkLastPosition;
    int             m_iLastEvent;
    int             m_iLastDelay;
    
};
