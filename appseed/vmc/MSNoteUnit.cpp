// MSNote.cpp: implementation of the CMSNoteUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSNote.h"

#include "MSMusic.h"
#include "MSEventSymbol.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSNoteUnit::CMSNoteUnit()
{
    m_ushPositionX = 12;
}

CMSNoteUnit::~CMSNoteUnit()
{

}

void CMSNoteUnit::SetSymbol(int iSymbol)
{
    m_iSymbol = iSymbol;
   
}

void CMSNoteUnit::TranslateToShSymbol()
{
    unsigned short ushSymbol;
    int iSymbol = m_iSymbol;
    if(iSymbol == CMSMusic::ciBreve)
    {
        ushSymbol = CMSEventSymbol::cushSymbolBreve;
    }
    else if(iSymbol == CMSMusic::ciSemibreve)
    {
        ushSymbol = CMSEventSymbol::cushSymbolSemibreve;
    }
    else if(iSymbol == CMSMusic::ciHalfNote)
    {
        ushSymbol = CMSEventSymbol::cushSymbolHalfNoteUp;
    }
    else if(iSymbol == CMSMusic::ciQuarterNote)
    {
        ushSymbol = CMSEventSymbol::cushSymbolQuarterNoteUp;
    }
    else if(iSymbol == CMSMusic::ciEighthNote)
    {
        ushSymbol = CMSEventSymbol::cushSymbolEighthNoteUp;
    }
    else if(iSymbol == CMSMusic::ciSixteenthNote)
    {
        ushSymbol = CMSEventSymbol::cushSymbolSixteenthNoteUp;
    }
    else if(iSymbol == CMSMusic::ciSixtyFourthNote)
    {
        ushSymbol = CMSEventSymbol::cushSymbolSixtyFourthNoteUp;
    }
    else if(iSymbol == CMSMusic::ciFlat )
    {
        ushSymbol = CMSEventSymbol::cushSymbolFlat;
    }
    else if(iSymbol == CMSMusic::ciNatural)
    {
        ushSymbol = CMSEventSymbol::cushSymbolNatural;
    }
    else if(iSymbol == CMSMusic::ciSharp)
    {
        ushSymbol = CMSEventSymbol::cushSymbolSharp;
    }
    else if(iSymbol == CMSMusic::ciHalfNotePoint)
    {
        ushSymbol = CMSEventSymbol::cushSymbolFirstHalfNotePoint;
    }
    else
    {
//        ASSERT(FALSE);
    }
    m_ushSymbol = ushSymbol;
}
