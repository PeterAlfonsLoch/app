#pragma once

class CMSTrack;
class CMSTrackV001Set;
class CMSEvents;

class CMSTrackV001  
{
public:
    CMSTrackV001();
	CMSTrackV001(CMSTrack *lpTrack);
	virtual ~CMSTrackV001();
    friend class CMSTrackV001Set;
    enum
    {
        SeekEvent = 1,
        SeekEventBegin = 2,
        SeekEventCurrent = 3,
        SeekEventEnd = 4,
    };
public:
	CMSEvents * GetEvents();
	VMSRESULT SeekBegin(int iOffset = 0);
	VMSRESULT Seek(int iOffset, int iFrom);
protected:
    CMSTrack *  m_lpTrack;
    int         m_iCurrentEvent;
    DWORD       m_tkPosition;
};

