/////////////////////////////////////////////////////////////////////////////////////////
// file name: decoder.h
// module: audio_decode_wave::decoder
// module Long name: notSAD Audio decoder MPEG Library decoder
// Purpose: Provide not sad interface for mpglib decoder.
//    
/////////////////////////////////////////////////////////////////////////////////////////
// 2006-02-22  Adaptation from the original veriwell Musical Player sources   |   1|cst 
//             to audio_decode library project                                      |    |
/////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "InputFile.h"

namespace audio_decode_wave
{

   class decoder :
      public audio_decode::decoder
   {
   protected:
      int                  m_iSamMul;
      int                  m_iSamDiv;

      int                  m_iReadPointer;
      gen::memory_file   m_memfile;
      bool                 m_bStop;
      bool                 m_bEof;
      char                 m_buf[1024 * 8];
      __int64              m_nSampleCount;
      bool m_bNonStopOnEof;

   public:

      inline gen::memory_file & GetMemoryFile();

      void DecoderSeekEnd();


      InputFile         m_inputfile;

	   void DecoderStop();
	   void ReadFrame();

      
      decoder(::ca::application * papp);
	   virtual ~decoder();

      

      virtual bool      _DecoderInitialize(ex1::file * pfile);
      virtual bool      _DecoderFinalize();
      virtual bool      _DecoderEOF();
      virtual ::primitive::memory_size  _DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize);

      virtual void      DecoderMoveNext();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual __int64   DecoderGetSampleCount();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual void      DecoderSeekBegin();
      virtual bool      DecoderGetAttribute(audio_decode::EAttribute eattribute, string & str);
      virtual bool      DecoderSetNonStopOnEofMode(bool bSet);
   };


} // namespace _vmsmpegdec
