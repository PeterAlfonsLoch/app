// _vmsriffdecRiffId.cpp: implementation of the CRiffId class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsriffdecRiffId.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace _vmsriffdec
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRiffId::CRiffId()
{

}

CRiffId::~CRiffId()
{

}

bool CRiffId::IsWAVE()
{
   return strncmp(m_szId, "WAVE", 4) == 0;
}

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

