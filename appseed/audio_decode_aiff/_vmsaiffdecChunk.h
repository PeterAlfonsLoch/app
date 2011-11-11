// _vmsaiffdecChunk.h: interface for the CChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECCHUNK_H__7EF85B3C_AF0D_40C6_8EC8_C0D7427D4D90__INCLUDED_)
#define AFX__VMSAIFFDECCHUNK_H__7EF85B3C_AF0D_40C6_8EC8_C0D7427D4D90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaiffdecChunkHeader.h"

namespace _vmsaiffdec
{


class CChunk  
{
public:
   CChunkHeader      m_chunkheader;
public:
	bool Initialize();
	DWORD GetSize();
	CChunk();
	~CChunk();

};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECCHUNK_H__7EF85B3C_AF0D_40C6_8EC8_C0D7427D4D90__INCLUDED_)
