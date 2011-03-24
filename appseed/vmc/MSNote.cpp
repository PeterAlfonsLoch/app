// MSNotes.cpp: implementation of the CMSNote class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "VMSApp.h"
#include "MSNotes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMSNote::CMSNote()
{

}

CMSNote::CMSNote(CMSNote &note)
{
    *this = note;
}



CMSNote::~CMSNote()
{

}

DWORD CMSNote::GetDuration(DWORD tkQuarterNote)
{
    
    return 0;
}

/*void CMSNote::AddUnit(int iUnit)
{
    CMSNoteUnit nu;
    nu.SetSymbol(iUnit);
    nu.TranslateToShSymbol();
    Add(nu);
}*/

void CMSNote::AddUnit(int iUnit, short shSymbolDelta, short shPositionY)
{
    CMSNoteUnit nu;
    nu.SetSymbol(iUnit);
    nu.SetSymbolDelta(shSymbolDelta);
    nu.SetPositionY(shPositionY);
    nu.TranslateToShSymbol();
    Add(nu);
}

void CMSNote::Clear()
{
    RemoveAll(false);

}

CMSNote & CMSNote::operator =(const CMSNote &note)
{
    Clear();
    Append(note);
    m_iAccidental = note.m_iAccidental;
    m_iNote = note.m_iNote;
    return *this;
}
