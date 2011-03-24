#pragma once

class CMSEvent;

class CMSPosition 
{
public:
	CMSPosition(const CMSPosition & position);
	CMSPosition();
	virtual ~CMSPosition();
   DWORD       m_tkPosition;
   BaseArray<CMSEvent *, CMSEvent *>   m_esaSymbols;
public:
    CMSPosition & operator =(const CMSPosition & position);
    VMSRESULT DoDefaultNotesSpacing(int iPositionX, int * lpiPositionX);
};

