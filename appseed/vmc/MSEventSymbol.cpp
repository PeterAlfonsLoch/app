// MSEventSymbol.cpp: implementation of the CMSEventSymbol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSEventSymbol.h"
#include "VMS_.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const unsigned short CMSEventSymbol::cushSymbolStaff = 1;
const unsigned short CMSEventSymbol::cushSymbolBreve = 2;
const unsigned short CMSEventSymbol::cushSymbolBreveRest = 3;
const unsigned short CMSEventSymbol::cushSymbolSemibreve = 4;
const unsigned short CMSEventSymbol::cushSymbolSemibreveRest = 5;
const unsigned short CMSEventSymbol::cushSymbolHalfNoteUp = 6;
const unsigned short CMSEventSymbol::cushSymbolHalfNoteDown = 7;
const unsigned short CMSEventSymbol::cushSymbolHalfNoteRest = 8;
const unsigned short CMSEventSymbol::cushSymbolQuarterNoteUp = 9;
const unsigned short CMSEventSymbol::cushSymbolQuarterNoteDown = 10;
const unsigned short CMSEventSymbol::cushSymbolQuarterNoteRest = 11;
const unsigned short CMSEventSymbol::cushSymbolEighthNoteUp = 12;
const unsigned short CMSEventSymbol::cushSymbolEighthNoteDown = 13;
const unsigned short CMSEventSymbol::cushSymbolEighthNoteRest = 14;
const unsigned short CMSEventSymbol::cushSymbolSixteenthNoteUp = 15;
const unsigned short CMSEventSymbol::cushSymbolSixteenthNoteDown = 16;
const unsigned short CMSEventSymbol::cushSymbolSixteenthNoteRest = 17;
const unsigned short CMSEventSymbol::cushSymbolThirtySecondNoteUp = 18;
const unsigned short CMSEventSymbol::cushSymbolThirtySecondNoteDown = 19;
const unsigned short CMSEventSymbol::cushSymbolThirtySecondNoteRest = 20;
const unsigned short CMSEventSymbol::cushSymbolSixtyFourthNoteUp = 21;
const unsigned short CMSEventSymbol::cushSymbolSixtyFourthNoteDown = 22;
const unsigned short CMSEventSymbol::cushSymbolSixtyFourthNoteRest = 23;

const unsigned short CMSEventSymbol::cushSymbolSharp = 24;
const unsigned short CMSEventSymbol::cushSymbolNatural = 25;
const unsigned short CMSEventSymbol::cushSymbolFlat = 26;

const unsigned short CMSEventSymbol::cushSymbolFirstHalfNotePoint = 27;
const unsigned short CMSEventSymbol::cushSymbolSecondHalfNotePoint = 28;

CMSEventSymbol::CMSEventSymbol()
{

}

CMSEventSymbol::CMSEventSymbol(CMSNoteUnit &noteUnit)
{
    *this = noteUnit;
}

CMSEventSymbol::CMSEventSymbol(CMSEvent &event)
{
    memcpy(this, &event, sizeof(CMSEvent));
}


CMSEventSymbol::~CMSEventSymbol()
{

}

VMSRESULT CMSEventSymbol::DeleteContents()
{
    return VMSR_SUCCESS;
}

LPVOID CMSEventSymbol::GetData()
{
    return m_lpbData;
}

int CMSEventSymbol::GetDataSize()
{
    return sizeof(unsigned short) * 3 + sizeof(short);
}

VMSRESULT CMSEventSymbol::FromData(LPVOID lpData, LPINT lpiLeft)
{
    //ASSERT(*lpiLeft >= sizeof(unsigned short) * 3 + sizeof(short));
    if(*lpiLeft < GetDataSize())
        return VMSR_E_INVALIDFILE;
    memcpy(m_lpbData, lpData, GetDataSize());
    *lpiLeft -= GetDataSize();
    return VMSR_SUCCESS;
}

bool CMSEventSymbol::IsNote()
{
    switch(GetSymbol())
    {
        case cushSymbolBreve:
        case cushSymbolSemibreve:
        case cushSymbolHalfNoteUp:
        case cushSymbolHalfNoteDown:
        case cushSymbolQuarterNoteUp:
        case cushSymbolQuarterNoteDown:
        case cushSymbolEighthNoteUp:
        case cushSymbolEighthNoteDown:
        case cushSymbolSixteenthNoteUp:
        case cushSymbolSixteenthNoteDown:
        case cushSymbolThirtySecondNoteUp:
        case cushSymbolThirtySecondNoteDown:
        case cushSymbolSixtyFourthNoteUp:
        case cushSymbolSixtyFourthNoteDown:
            return true;
        default:
            return false;
    }
}

CMSEventSymbol & CMSEventSymbol::operator =(CMSNoteUnit &noteUnit)
{
    m_tkDelta = 0;
    m_dwEventType = VMS_EVENT_SYMBOL;
    SetSymbol(noteUnit.GetSymbol());
    SetPositionX(noteUnit.GetPositionX());
    SetPositionY(noteUnit.GetPositionY());
    SetSize(noteUnit.GetSize());
    SetSymbolDelta(noteUnit.GetSymbolDelta());
    return *this;
}

CMSEventSymbol & CMSEventSymbol::operator =(CMSEvent &eventSrc)
{
    m_tkDelta = eventSrc.m_tkDelta;
    m_dwEventType = eventSrc.m_dwEventType;
    memcpy(m_lpbData, eventSrc.m_lpbData, sizeof(m_lpbData));
	return *this;
}

DWORD CMSEventSymbol::GetSpacingDuration(DWORD tkQuarterNote, DWORD tkDuration, LPDWORD lptkDuration)
{
    DWORD tkSpacingDuration;
    if(GetSymbol() == cushSymbolEighthNoteDown ||
        GetSymbol() == cushSymbolEighthNoteRest ||
        GetSymbol() == cushSymbolEighthNoteUp)
    {
        tkSpacingDuration = tkQuarterNote / 2;
    }
    else if(GetSymbol() == cushSymbolQuarterNoteDown ||
        GetSymbol() == cushSymbolQuarterNoteRest ||
        GetSymbol() == cushSymbolQuarterNoteUp)
    {
        tkSpacingDuration = tkQuarterNote;
    }
    else if(GetSymbol() == cushSymbolHalfNoteDown ||
        GetSymbol() == cushSymbolHalfNoteRest ||
        GetSymbol() == cushSymbolHalfNoteUp)
    {
        tkSpacingDuration = tkQuarterNote * 2;
    }
    else if(GetSymbol() == cushSymbolFirstHalfNotePoint ||
        GetSymbol() == cushSymbolSecondHalfNotePoint)
    {
        tkSpacingDuration = tkDuration / 2;
    }
    else
    {
        tkSpacingDuration = 0;
    }

    *lptkDuration = tkSpacingDuration;
    return tkSpacingDuration;
}
