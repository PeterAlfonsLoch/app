#include "StdAfx.h"
#include "vmssyncheditor.h"
#include "MidiTrackSelectViewUpdateHint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CMidiTrackSelectViewUpdateHint, base_object)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMidiTrackSelectViewUpdateHint::CMidiTrackSelectViewUpdateHint()
{

}

CMidiTrackSelectViewUpdateHint::~CMidiTrackSelectViewUpdateHint()
{

}

void CMidiTrackSelectViewUpdateHint::SetType(EType etype)
{
   m_etype = etype;
}

CMidiTrackSelectViewUpdateHint::EType CMidiTrackSelectViewUpdateHint::GetType()
{
   return m_etype;
}  
