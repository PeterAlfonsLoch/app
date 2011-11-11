#pragma once

namespace audio_decode_rtp
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

   public:


      void DecoderStop();
      void ReadFrame();

      
      decoder(::ca::application * papp);
      virtual ~decoder();

      

      virtual bool      DecoderInitialize(ex1::file * pfile);
      virtual void      DecoderMoveNext();
      virtual bool      DecoderEOF();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual __int64   DecoderGetSampleCount();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual ::primitive::memory_size  DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize);
      virtual void      DecoderSeekBegin();
      virtual bool      DecoderGetAttribute(audio_decode::EAttribute eattribute, LPTSTR lpsz, int iSize);
   };

   inline gen::memory_file & decoder::GetMemoryFile()
   {
      return m_memfile;
   }

} // namespace audio_decode_rtp
