#pragma once


namespace audio_decode
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
      virtual public ::radix::thread
   {
   public:


      DWORD_PTR                              m_dwDecodeLength;
      pointer_object < primitive::memory >   m_pmemory;
      pointer_object < gen::memory_file >    m_pmemoryfileOut;
      pointer_object < gen::memory_file >    m_pmemoryfileIn;
      int64_array                            m_iaLostPosition;
      int_array                              m_iaLostCount;
      __int64                                m_iReadExpanded;
      __int64                                m_iRead;
      bool                                   m_bInitialized;


      decoder(::ca::application * papp);
      virtual ~decoder();

      virtual int       run();
      virtual bool      DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderInitialize(ex1::file *pfile) = 0;
      virtual void      DecoderMoveNext() = 0;
      virtual bool      DecoderEOF();
      virtual bool      _DecoderEOF() = 0;
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


      virtual DWORD              DecoderGetLostMillis(DWORD dwExpandedMillis);
      virtual imedia::position   DecoderGetLostPositionOffset(imedia::position position);

      // low level adjustments that may be not supported by the decoder in
      // which case the decoder client may not be able to use the decoder
      // if such adjustments cannot take effect;
      virtual bool      DecoderSetSeekable(bool bSet = true);
      virtual bool      DecoderGetSeekable();
      virtual int       DecoderSetReadBlockSize(int iSize);

      // return number of bytes written
      virtual int       DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);

      virtual int       _DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize) = 0;

      virtual __int64   DecoderGetSampleCount() = 0;
      virtual __int64   DecoderGetMillisLength();

      //virtual void      DecoderStop() = 0;

   };

} // namespace audio_decode

