#pragma once

class CMSEventMidi;
class CMSEventSymbol;

class CMSEvent  
{
public:
	CMSEvent();
	virtual ~CMSEvent();

public:
    DWORD           m_tkDelta;
    DWORD           m_dwEventType;
    int             m_iDataRef;
    int             m_iPositionX;
    union
    {
        DWORD               m_lpdwData[3];
        short               m_lpshData[3 * sizeof(DWORD) / sizeof(short)];
        unsigned short      m_lpushData[3 * sizeof(DWORD) / sizeof(short)];
        BYTE                m_lpbData[3 * sizeof(DWORD)];
    };
public:
    CMSEvent & operator =(const CMSEvent &eventSrc);
	virtual VMSRESULT DeleteContents();
	VMSRESULT GetEventMidi(CMSEventMidi & event);
    VMSRESULT GetEventSymbol(CMSEventSymbol & event);
    
	virtual DWORD GetEventType();

};

