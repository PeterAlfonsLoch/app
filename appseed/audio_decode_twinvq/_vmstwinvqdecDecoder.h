// _vmstwinvqdecDecoder.h: interface for the CDecoder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSTWINVQDECDECODER_H__6EEEF832_9F07_41AA_8A88_6C0BCEEA68E4__INCLUDED_)
#define AFX__VMSTWINVQDECDECODER_H__6EEEF832_9F07_41AA_8A88_6C0BCEEA68E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "_vmsaudioiDecoderInterface.h"
#include "MemoryFile.h"
#include "bfile.h"
#include "twinvq.h"
#include "_vmstwinvqdecTwinVQ.h"

namespace _vmstwinvqdec
{

class CLASS_DECL_VMSTWINVQDEC CDecoder  
:
public _vmsaudioi::DecoderInterface
{
   bool m_bStop;
   int fileType ;
   int m_iReadPointer;
	headerInfo setupInfo;               // setup information
	INDEX index;                        // quantization indexes
	int        frameSize, numChannels;  // frame configuration parameters
	float      *out;                    // decoder output data array
	short      *bufout;                 // file output buffer
   BFILE	*bfp_cw;
   bool m_bEOF;
	int wout_flag;             // Decoder wave output flag
	int flgRewind;
   int flgFF;  // FF and REW status
	int play_count;            // skip control parameters when FF and REW mode
      CMemoryFile       m_memfile;
   //CTwinVQ m_tvq;
public:
	virtual void DecoderStop();
	CDecoder();
	virtual ~CDecoder();
      CMemoryFile & GetMemoryFile();
   void ReadFrame();


   virtual bool      DecoderInitialize(CFile * pfile);
   virtual void      DecoderSeekBegin();
   virtual void      DecoderMoveNext();
   virtual bool      DecoderEOF();
   virtual LPBYTE    DecoderGetBuffer();
   virtual int       DecoderGetBufferSize();
   virtual void      DecoderRun();
   virtual UINT      DecoderGetSamplesPerSec();
   virtual UINT      DecoderGetChannelCount();
   virtual UINT      DecoderGetBitsPerSample();
   virtual int       DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);

};

   inline CMemoryFile & CDecoder::GetMemoryFile()
   {
      return m_memfile;
   }

} // namespace _vmstwinvqdec

#endif // !defined(AFX__VMSTWINVQDECDECODER_H__6EEEF832_9F07_41AA_8A88_6C0BCEEA68E4__INCLUDED_)
