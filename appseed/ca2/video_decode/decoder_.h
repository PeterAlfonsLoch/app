#pragma once


namespace video
{


   class player;


} // namespace video


namespace video_decode
{
   enum EAttribute
   {
      AttributeNone,
      AttributeTitle,
      AttributeAuthor,
      AttributeAlbum,
      AttributeOriginalAlbum,
      AttributeComposer,
      AttributeArtist,
      AttributeYear,
   };

   class CLASS_DECL_ca decoder :
      virtual public ::radix::object
   {
   public:


      bool                                      m_bStop;
      int                                       m_iDib;
      gen::memory_file                          m_memfileAudio;
      gen::memory_file                          m_memfileAudioBuffer;
      ::ex2::transfer_file                      m_transferfileAudio;
      bool                                      m_bDraw;
      DWORD                                     m_dwStartTime;
      int                                       m_iFrameDelayTolerance;
      ::video::player *                         m_pplayer;
      bool                                      m_bEmpty;
      bool                                      m_bFull;
      manual_reset_event                        m_evFull;
      bool                                      m_bDecoding;
      bool                                      m_bScaling;





      decoder(::ca::application * papp);
      virtual ~decoder();


      virtual bool decode();
      virtual bool step();

      
      virtual bool      DecoderInitialize(ex1::file *pfile) = 0;
      virtual void      DecoderFinalize() = 0;


      virtual bool      DecoderNextFrame() = 0;
      virtual bool      DecoderEOF() = 0;
      //virtual LPBYTE    DecoderGetBuffer() = 0;
      //virtual int       DecoderGetBufferSize() = 0;
      //virtual void      DecoderRun() = 0;
      virtual UINT      DecoderGetSamplesPerSecond() = 0;
      virtual UINT      DecoderGetChannelCount() = 0;
      virtual UINT      DecoderGetBitsPerSample() = 0;
      virtual void      DecoderSeekBegin() = 0;
      virtual void      DecoderSeekEnd();
      virtual bool      DecoderSetNonStopOnEofMode(bool bSet = true);
      virtual bool      DecoderGetAttribute(EAttribute attribute, string & str);

      // low level adjustments that may be not supported by the decoder in
      // which case the decoder client may not be able to use the decoder
      // if such adjustments cannot take effect;
      virtual bool      DecoderSetSeekable(bool bSet = true);
      virtual int       DecoderSetReadBlockSize(int iSize);
   
      // return number of bytes written
      //virtual ::primitive::memory_size       DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize) = 0;

      virtual __int64   DecoderGetSampleCount() = 0;
      virtual __int64   DecoderGetMillisLength();


      virtual ::ca::dib * decoder_get_frame(int iFrame);

      //virtual void      DecoderStop() = 0;

   };

} // namespace audio_decode

