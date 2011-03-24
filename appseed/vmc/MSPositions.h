#pragma once


class CMSPositions : public BaseArray<CMSPosition, CMSPosition>
{
public:
	
	CMSPositions();
	virtual ~CMSPositions();
protected:
   int     m_iPositionX;
public:
   VMSRESULT DoDefaultNotesSpacing(DWORD tkPosition);
	VMSRESULT AddPosition(CMSEvent *lpEventSymbol, DWORD tkPosition);
};

