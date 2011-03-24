// MSPosition.cpp: implementation of the CMSPosition class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSPosition.h"

#include "VMS_.h"
#include "MSEventSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSPosition::CMSPosition()
{

}

CMSPosition::CMSPosition(const CMSPosition & position)
{
    m_esaSymbols.Copy(position.m_esaSymbols);
    m_tkPosition = position.m_tkPosition;
}

CMSPosition::~CMSPosition()
{

}

CMSPosition & CMSPosition::operator =(const CMSPosition & position)
{
    m_esaSymbols.Copy(position.m_esaSymbols);
    m_tkPosition = position.m_tkPosition;
    return *this;
}
VMSRESULT CMSPosition::DoDefaultNotesSpacing(
    int iPositionX,
    int * lpiPositionX)
{
    CMSEvent *     lpEvent;
    CMSEventSymbol event;
    int iNextPositionX = iPositionX;
    for(int i = 0; i < m_esaSymbols.GetSize(); i++)
    {
        lpEvent = m_esaSymbols.ElementAt(i);
        event = *lpEvent;
        if(event.IsNote())
        {
            lpEvent->m_iPositionX = iPositionX;
            if(iNextPositionX < iPositionX + 12)
                iNextPositionX = iPositionX + 12;
        }
        else if(event.GetSymbol() == CMSEventSymbol::cushSymbolFirstHalfNotePoint)
        {
            lpEvent->m_iPositionX = iPositionX + 12;
            if(iNextPositionX < iPositionX + 24)
                iNextPositionX = iPositionX + 24;
        }
        else if(event.GetSymbol() == CMSEventSymbol::cushSymbolSecondHalfNotePoint)
        {
            lpEvent->m_iPositionX = iPositionX + 24;
            if(iNextPositionX < iPositionX + 26)
                iNextPositionX = iPositionX + 26;
        }
        else
        {
            lpEvent->m_iPositionX = iPositionX;
            if(iNextPositionX < iPositionX + 12)
                iNextPositionX = iPositionX + 12;
        }
    }
    *lpiPositionX = iNextPositionX;
    return VMSR_SUCCESS;

}
