// _vmsriffdecRiffHeader.cpp: implementation of the CRiffHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsriffdecRiffHeader.h"

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

CRiffHeader::CRiffHeader()
{

}

CRiffHeader::~CRiffHeader()
{

}

bool CRiffHeader::IsRIFF()
{
   return strncmp(m_szId, "RIFF", 4) == 0;
}

DWORD CRiffHeader::GetLength()
{
   return m_dwLength;
}



///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////



