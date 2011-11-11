// _vmsaiffdecFormChunk.h: interface for the CFormChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECFORMCHUNK_H__8508FFC8_8820_4062_B6F0_1FB8FCE64117__INCLUDED_)
#define AFX__VMSAIFFDECFORMCHUNK_H__8508FFC8_8820_4062_B6F0_1FB8FCE64117__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaiffdecID.h"
#include "_vmsaiffdecChunkHeader.h"

namespace _vmsaiffdec
{


class CFormChunkHeader
{
public:
   CChunkHeader   m_chunkheader;
   CID            m_idType;
public:
	bool Initialize();
	CFormChunkHeader();
	~CFormChunkHeader();

};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECFORMCHUNK_H__8508FFC8_8820_4062_B6F0_1FB8FCE64117__INCLUDED_)
