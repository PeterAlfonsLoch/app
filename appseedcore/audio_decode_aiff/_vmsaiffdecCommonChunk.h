// _vmsaiffdecCommonChunk.h: interface for the CCommonChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECCOMMONCHUNK_H__31668D2F_09BC_4BB1_B87D_425FF748F307__INCLUDED_)
#define AFX__VMSAIFFDECCOMMONCHUNK_H__31668D2F_09BC_4BB1_B87D_425FF748F307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaiffdecChunk.h"
#include "_vmsaiffdecExtended.h"

namespace _vmsaiffdec
{

class CCommonChunk
   :
   public CChunk
{
public:
   short             m_shChannelCount;
   unsigned long     m_ulSampleFrameCount;
   short             m_shSampleSize;
   CExtended         m_extSampleRate;
public:
	bool Initialize();
	CCommonChunk();
	~CCommonChunk();

};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECCOMMONCHUNK_H__31668D2F_09BC_4BB1_B87D_425FF748F307__INCLUDED_)
