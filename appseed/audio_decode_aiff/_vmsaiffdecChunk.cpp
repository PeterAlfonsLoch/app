// _vmsaiffdecChunk.cpp: implementation of the CChunk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecChunk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace _vmsaiffdec
{


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChunk::CChunk()
{

}

CChunk::~CChunk()
{

}

DWORD CChunk::GetSize()
{
   return m_chunkheader.GetSize();
}

bool CChunk::Initialize()
{
   m_chunkheader.Initialize();
   return true;
}


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////


