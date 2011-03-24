// _vmsaiffdecCommonChunk.cpp: implementation of the CCommonChunk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecCommonChunk.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void SwapBytesInWords( short *loc, int words );
extern void SwapBytesInDWords( LPDWORD loc, int dwords );

namespace _vmsaiffdec
{

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommonChunk::CCommonChunk()
{

}

CCommonChunk::~CCommonChunk()
{

}

bool CCommonChunk::Initialize()
{
   CChunk::Initialize();
   SwapBytesInWords(&m_shChannelCount, 1);
   SwapBytesInDWords((LPDWORD) &m_ulSampleFrameCount, 2);
   SwapBytesInWords(&m_shSampleSize, 1);
   m_extSampleRate.Initialize();
   return true;
}


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

