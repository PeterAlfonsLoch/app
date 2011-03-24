// _vmsaiffdecDecoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSAIFFDECDECODER_H__C5581E3F_984D_4BB2_BEC9_ABFADC94A861__INCLUDED_)
#define AFX__VMSAIFFDECDECODER_H__C5581E3F_984D_4BB2_BEC9_ABFADC94A861__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaudioiDecoderInterface.h"
#include "MemoryFile.h"

namespace _vmsaiffdec
{

   class CCommonChunk;
   class CFormChunkHeader;
   class CSoundDataChunk;
class CLASS_DECL_VMSAIFFDEC CDecoder  
   :
   public _vmsaudioi::DecoderInterface
{
protected:
   bool                    m_bStop;
   CFile *                 m_pfile;
   CFormChunkHeader *      m_pformchunkhdr;
   CCommonChunk *          m_pcommonchunk;
   CSoundDataChunk *       m_psounddatachunk;
   bool                    m_bEOD; // End Of Decoding

   LPBYTE                  m_lpbFrame;
   UINT                    m_uiFrameSize;
   UINT                    m_uiReadSync;

   CMemoryFile             m_fileFrame;          
   
public:
	void ReadFrame();
	CDecoder();
	virtual ~CDecoder();

   virtual void      DecoderSeekBegin();
   virtual bool      DecoderInitialize(CFile * pfile);
   virtual void      DecoderMoveNext();
   virtual bool      DecoderEOF();
   virtual LPBYTE    DecoderGetBuffer();
   virtual int       DecoderGetBufferSize();
   virtual void      DecoderRun();
   virtual UINT      DecoderGetSamplesPerSec();
   virtual UINT      DecoderGetChannelCount();
   virtual UINT      DecoderGetBitsPerSample();
   virtual int       DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);
   virtual void      DecoderStop();
};

/////////////////////////////////////////////////////////////
} // namespace _vmsaiffdec
/////////////////////////////////////////////////////////////

#endif // !defined(AFX__VMSAIFFDECDECODER_H__C5581E3F_984D_4BB2_BEC9_ABFADC94A861__INCLUDED_)
