// _vmsriffdecFormatChunk.h: interface for the CFormatChunk class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSRIFFDECFORMATCHUNK_H__AEE209B8_6E56_40A8_9F73_149339321B3F__INCLUDED_)
#define AFX__VMSRIFFDECFORMATCHUNK_H__AEE209B8_6E56_40A8_9F73_149339321B3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace _vmsriffdec
{


class CFormatChunk  
{
public:
   WORD     m_wFormatTag;         // Format category
	WORD     m_wChannels;          // Number of channels
	DWORD    m_dwSamplesPerSec;    // Sampling rate
	DWORD    m_dwAvgBytesPerSec;   // For buffer estimation
	WORD     m_wBlockAlign;        // Data block size
public:
	CFormatChunk();
	~CFormatChunk();

};

///////////////////////////////////////
} // namespace _vmsriffdec
///////////////////////////////////////

#endif // !defined(AFX__VMSRIFFDECFORMATCHUNK_H__AEE209B8_6E56_40A8_9F73_149339321B3F__INCLUDED_)
