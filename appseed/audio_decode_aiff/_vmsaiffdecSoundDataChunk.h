// _vmsaiffdecSoundDataChunk.h: interface for the CSoundDataChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECSOUNDDATACHUNK_H__811B2FA4_354D_4DF2_A4C9_8D7B4F530261__INCLUDED_)
#define AFX__VMSAIFFDECSOUNDDATACHUNK_H__811B2FA4_354D_4DF2_A4C9_8D7B4F530261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaiffdecChunk.h"


namespace _vmsaiffdec
{

class CSoundDataChunk 
   : 
   public CChunk
{
public:
   unsigned long     m_ulOffset;
   unsigned long     m_ulBlockSize;
public:
	bool Initialize();
	CSoundDataChunk();
	~CSoundDataChunk();
};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECSOUNDDATACHUNK_H__811B2FA4_354D_4DF2_A4C9_8D7B4F530261__INCLUDED_)

