// VmpLightViewUpdateHint.cpp: implementation of the CVmpLightViewUpdateHint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VmpLightViewUpdateHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CVmpLightViewUpdateHint, base_object)


CVmpLightViewUpdateHint::CVmpLightViewUpdateHint()
{
   m_etype = TypeNone;
   m_pmidiplayer = NULL;
}

CVmpLightViewUpdateHint::~CVmpLightViewUpdateHint()
{

}

void CVmpLightViewUpdateHint::SetType(EType etype)
{
   m_etype = etype;
}

bool CVmpLightViewUpdateHint::IsTypeOf(EType etype)
{
   return m_etype == etype;
}
