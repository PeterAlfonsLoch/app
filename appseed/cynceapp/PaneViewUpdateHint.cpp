// PaneViewUpdateHint.cpp: implementation of the PaneViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PaneViewUpdateHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(PaneViewUpdateHint, CObject)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PaneViewUpdateHint::PaneViewUpdateHint()
{

}

PaneViewUpdateHint::~PaneViewUpdateHint()
{

}

bool PaneViewUpdateHint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}

void PaneViewUpdateHint::SetType(EType etype)
{
   m_etype = etype;
}
