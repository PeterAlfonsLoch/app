// _vmsaiffdecExtended.cpp: implementation of the CExtended class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecExtended.h"
#include "ieeefloat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void SwapBytesInWords( short *loc, int words );

namespace _vmsaiffdec
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExtended::CExtended()
{

}

CExtended::~CExtended()
{

}

long double CExtended::GetValue()
{
   return ConvertFromIeeeExtended(m_szData);
}

void CExtended::SetValue(long double ld)
{
   ConvertToIeeeExtended(ld, m_szData);
}

bool CExtended::Initialize()
{
   SwapBytesInWords((short *) &m_szData, sizeof(m_szData));
   return true;
}

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////


