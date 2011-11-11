// _vmsaiffdecSoundDataChunk.cpp: implementation of the CSoundDataChunk class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "_vmsaiffdecSoundDataChunk.h"

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

CSoundDataChunk::CSoundDataChunk()
{

}

CSoundDataChunk::~CSoundDataChunk()
{

}

bool CSoundDataChunk::Initialize()
{
   CChunk::Initialize();
   return true;
}


/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

