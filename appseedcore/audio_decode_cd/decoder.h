#pragma once


namespace audio_decode_cd
{

   class CCommonChunk;
   class CFormChunkHeader;
   class CSoundDataChunk;

   class CLASS_DECL_VMSCDADEC decoder :
      public audio_decode::decoder
   {
   protected:
      bool                    m_bStop;
      ex1::file *             m_pfile;
      bool                    m_bEOF; // End Of File

      //LPBYTE                  m_lpbFrame;

      HCDROM                  m_hcdrom;
      UINT                    m_dwFrame;
      
      DWORD                   m_dwStartFrame;
      DWORD                   m_dwFrameCount;

      DWORD                   m_dwRemain;
      DWORD                   m_dwCurrentFrame;



      LPTRACKBUF              m_lptrackbuf;
      DWORD                   m_dwBufferSize;
      DWORD                   m_dwBufferFrameCount;
      UINT                    m_uiReadSync;

      gen::memory_file        m_fileFrame;          
      __int64              m_nSampleCount;
   public:


      decoder(::ca::application * papp);
	   virtual ~decoder();

      virtual bool      _DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderEOF();
      virtual int       _DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);

      virtual void      DecoderSeekBegin();
      virtual void      DecoderMoveNext();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual void      DecoderStop();
      virtual __int64   DecoderGetSampleCount();

	   void OnDecoderEOF();
	   void ReadFrame();

      static LPTRACKBUF NewTrackBuff(DWORD numFrames, DWORD & dwFrameSize);
   };

} // namespace _vmsaiffdec
