// OptionsViewUpdateHint.cpp: implementation of the OptionsViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OptionsViewUpdateHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(OptionsViewUpdateHint, base_object)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OptionsViewUpdateHint::OptionsViewUpdateHint()
{

}

OptionsViewUpdateHint::~OptionsViewUpdateHint()
{

}

bool OptionsViewUpdateHint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}

void OptionsViewUpdateHint::SetType(EType etype)
{
   m_etype = etype;
}
