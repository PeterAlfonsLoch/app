// _vmsriffdecChunkHeader.cpp: implementation of the CChunkHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsriffdecChunkHeader.h"

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

CChunkHeader::CChunkHeader()
{

}

CChunkHeader::~CChunkHeader()
{

}

DWORD CChunkHeader::GetLength()
{
   if(Is_fmt())
   {
      return m_dwLength3;
   }
   else
   {
      return m_dwLength4;
   }
}

bool CChunkHeader::Is_fmt()
{
   return strncmp(m_szId3, "fmt", 3) == 0;
}

bool CChunkHeader::Is_data()
{
   return strncmp(m_szId4, "data", 4) == 0;
}

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////



