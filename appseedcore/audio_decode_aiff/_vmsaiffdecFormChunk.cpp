// _vmsaiffdeCFormChunkHeader.cpp: implementation of the CFormChunkHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdeCFormChunk.h"

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

CFormChunkHeader::CFormChunkHeader()
{

}

CFormChunkHeader::~CFormChunkHeader()
{

}

bool CFormChunkHeader::Initialize()
{
   m_chunkheader.Initialize();
   m_idType.Initialize();
   return true;
}

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

