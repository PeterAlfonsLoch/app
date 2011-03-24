#pragma once

#include "MSEvent.h"
#include "MSNoteUnit.h"

class CMSEventSymbol : public CMSEvent  
{
public:
   	CMSEventSymbol();
    CMSEventSymbol(CMSNoteUnit &noteUnit);
    CMSEventSymbol(CMSEvent &event);
        
	virtual ~CMSEventSymbol();

    static const unsigned short cushSymbolStaff;
    static const unsigned short cushSymbolBreve;
    static const unsigned short cushSymbolBreveRest;
    static const unsigned short cushSymbolSemibreve;
    static const unsigned short cushSymbolSemibreveRest;
    static const unsigned short cushSymbolHalfNoteUp;
    static const unsigned short cushSymbolHalfNoteDown;
    static const unsigned short cushSymbolHalfNoteRest;
    static const unsigned short cushSymbolQuarterNoteUp;
    static const unsigned short cushSymbolQuarterNoteDown;
    static const unsigned short cushSymbolQuarterNoteRest;
    static const unsigned short cushSymbolEighthNoteUp;
    static const unsigned short cushSymbolEighthNoteDown;
    static const unsigned short cushSymbolEighthNoteRest;
    static const unsigned short cushSymbolSixteenthNoteUp;
    static const unsigned short cushSymbolSixteenthNoteDown;
    static const unsigned short cushSymbolSixteenthNoteRest;
    static const unsigned short cushSymbolThirtySecondNoteUp;
    static const unsigned short cushSymbolThirtySecondNoteDown;
    static const unsigned short cushSymbolThirtySecondNoteRest;
    static const unsigned short cushSymbolSixtyFourthNoteUp;
    static const unsigned short cushSymbolSixtyFourthNoteDown;
    static const unsigned short cushSymbolSixtyFourthNoteRest;
    
    static const unsigned short cushSymbolSharp;
    static const unsigned short cushSymbolNatural;
    static const unsigned short cushSymbolFlat;
    
    static const unsigned short cushSymbolFirstHalfNotePoint;
    static const unsigned short cushSymbolSecondHalfNotePoint;

public:
	DWORD GetSpacingDuration(DWORD tkQuarterNote, DWORD tkDuration, LPDWORD lptkDuration);
    CMSEventSymbol & operator =(CMSEvent &eventSrc);
    CMSEventSymbol &operator =(CMSNoteUnit &noteUnit);
	bool IsNote();
	VMSRESULT FromData(LPVOID lpData, LPINT lpiLeft);
	int GetDataSize();
	LPVOID GetData();
	virtual VMSRESULT DeleteContents();

    inline void SetSymbol(unsigned short ushSymbol);
    inline void SetSize(unsigned short shSize);
    inline void SetPositionX(short ushPositionX);
    inline void SetPositionY(short shPositionY);
    inline void SetSymbolDelta(short ushSymbolDelta);

    inline unsigned short GetSymbol();
    inline unsigned short GetSize();
    inline short GetPositionX();
    inline short GetPositionY();
    inline short GetSymbolDelta();

};
inline void CMSEventSymbol::SetSymbol(unsigned short ushSymbol)
{
    m_lpushData[0] = ushSymbol;
}

inline unsigned short CMSEventSymbol::GetSymbol()
{
    return m_lpushData[0];
}

inline void CMSEventSymbol::SetSize(unsigned short ushSize)
{
    m_lpushData[1] = ushSize;
}

inline unsigned short CMSEventSymbol::GetSize()
{
    return m_lpushData[1];
}

inline void CMSEventSymbol::SetPositionX(short shPositionX)
{
    m_lpshData[2] = shPositionX;
}

inline short CMSEventSymbol::GetPositionX()
{
    return m_lpshData[2];
}

inline void CMSEventSymbol::SetPositionY(short shPositionY)
{
    m_lpshData[3] = shPositionY;
}

inline short CMSEventSymbol::GetPositionY()
{
    return m_lpshData[3];
}

inline void CMSEventSymbol::SetSymbolDelta(short ushSymbolDelta)
{
    m_lpshData[4] = ushSymbolDelta;
}

inline short CMSEventSymbol::GetSymbolDelta()
{
    return m_lpshData[4];
}
