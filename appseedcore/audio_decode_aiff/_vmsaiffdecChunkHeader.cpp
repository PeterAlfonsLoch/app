// _vmsaiffdecChunkHeader.cpp: implementation of the CChunkHeader class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecChunkHeader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern void SwapBytesInWords( short *loc, int words );

 void SwapBytesInDWords( LPDWORD loc, int dwords )
 {
    int i;
    DWORD thisval;
    char *dst, *src;
    src = (char *) &thisval;
    for ( i = 0; i < dwords; i++ )
    {
        thisval = *loc;
        dst = (char *) loc++;
        dst[0] = src[3];
        dst[1] = src[2];
        dst[2] = src[1];
        dst[3] = src[0];
    }

 }

namespace _vmsaiffdec
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

DWORD CChunkHeader::GetSize()
{
   return m_lSize;
}

bool CChunkHeader::Initialize()
{
   m_id.Initialize();
   SwapBytesInDWords((LPDWORD) &m_lSize, 1);
   return true;
}



/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////


