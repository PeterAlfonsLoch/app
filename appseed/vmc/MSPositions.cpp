// MSPositions.cpp: implementation of the CMSPositions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSPositions.h"

#include "VMS_.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSPositions::CMSPositions()
{
    m_iPositionX = 0;
}

CMSPositions::~CMSPositions()
{

}

VMSRESULT CMSPositions::AddPosition(CMSEvent *lpEventSymbol, DWORD tkPosition)
{
   int i;
    for(i = 0; i < GetSize(); i++)
    {
        if(ElementAt(i).m_tkPosition == tkPosition)
        {
            ElementAt(i).m_esaSymbols.Add(lpEventSymbol);
            return VMSR_SUCCESS;
        }
    }
    for(i = 0; i < GetSize(); i++)
    {
        if(ElementAt(i).m_tkPosition > tkPosition)
            break;
    }
    CMSPosition position;
    position.m_esaSymbols.Add(lpEventSymbol);
    position.m_tkPosition = tkPosition;
    InsertAt(i, position);

    return VMSR_SUCCESS;
}

VMSRESULT CMSPositions::DoDefaultNotesSpacing(DWORD tkPosition)
{
    CMSPosition *lpPosition;
    for(int i = 0; i < GetSize();)
    {
        lpPosition = &ElementAt(i);
        if(lpPosition->m_tkPosition <= tkPosition)
        {
            lpPosition->DoDefaultNotesSpacing(m_iPositionX, &m_iPositionX);
            RemoveAt(i);
            continue;
        }
        i++;
    }
    return VMSR_SUCCESS;
}
