#pragma once

class stream;

namespace audio_decode_window_media
{

   class CLASS_DECL_NOTSAD_WM decoder  :
      public audio_decode::decoder
   {
   protected:
      bool                    m_bStop;
      ex1::file *             m_pfile;
      bool                    m_bEOF; 

      WORD                    m_wStreamNum;

      DWORD                   m_dwFrameCount;

      DWORD                   m_dwRemain;
      DWORD                   m_dwCurrentFrame;



      DWORD                   m_dwBufferSize;
      DWORD                   m_dwBufferFrameCount;
      UINT                    m_uiReadSync;

      gen::memory_file        m_fileFrame; 
      
      stream *                m_pwmstream;
      IWMSyncReader *         m_psyncreader;
      IWMOutputMediaProps *   m_poutputmediaprops;
      WM_MEDIA_TYPE *         m_pmediatype;

      UINT                    m_uiSamplesPerSec;

      __int64              m_nSampleCount;
      
   public:
      decoder(::ca::application * papp);
	   virtual ~decoder();

      virtual bool      _DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderFinalize();
      virtual bool      _DecoderEOF();
      virtual ::primitive::memory_size  _DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize);

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

      bool              DecoderGetAttribute(audio_decode::EAttribute attribute, string & str);

      string GetAttributeName(audio_decode::EAttribute attribute);

	   void OnDecoderEOF();
	   void ReadFrame();
   };

} // namespace audio_decode_window_media
