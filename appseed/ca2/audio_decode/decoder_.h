#pragma once


namespace audio_decode
{


   class decoder_plugin;


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


      primitive::memory_size                 m_dwDecodeLength;
      sp(primitive::memory)                  m_spmemory;
      sp(gen::memory_file)                   m_spmemoryfileOut;
      sp(gen::memory_file)                   m_spmemoryfileIn;
      int64_array                            m_iaLostPosition;
      int_array                              m_iaLostCount;
      __int64                                m_iReadExpanded;
      __int64                                m_iRead;
      bool                                   m_bInitialized;
      bool                                   m_bRunning;
      int                                    m_iBufferSize;
      int                                    m_iReadBlockSize;


      decoder_plugin *                       m_pplugin;


      decoder(::ca::application * papp);
      virtual ~decoder();

      virtual int       run();

      virtual bool      DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderInitialize(ex1::file *pfile) = 0;

      virtual void      DecoderFinalize();
      virtual bool      _DecoderFinalize() = 0;

      virtual void      DecoderStop();


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
      
      virtual bool      DecoderSetExpectedParams(UINT uiSamplesPerSec, UINT uiChannelCount, UINT uiBitCount, UINT uiEncodedAvgBitRate);
      virtual UINT      DecoderGetRawBitRate();
      virtual UINT      DecoderGetAverageBitRate();
      virtual UINT      DecoderGetRawSize(UINT uiEncodeSize);

      virtual void      DecoderSeekEnd();
      virtual bool      DecoderSetNonStopOnEofMode(bool bSet = true);
      virtual bool      DecoderGetAttribute(EAttribute attribute, string & str);


      virtual imedia::time       DecoderGetLostMillis(imedia::time dwExpandedMillis);
      virtual imedia::position   DecoderGetLostPositionOffset(imedia::position position);

      // low level adjustments that may be not supported by the decoder in
      // which case the decoder client may not be able to use the decoder
      // if such adjustments cannot take effect;
      virtual bool      DecoderSetSeekable(bool bSet = true);
      virtual bool      DecoderGetSeekable();
      virtual int       DecoderSetReadBlockSize(int iSize);

      // return number of bytes written
      virtual ::primitive::memory_size       DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize);

      virtual ::primitive::memory_size       _DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize) = 0;

      virtual __int64   DecoderGetSampleCount() = 0;
      virtual __int64   DecoderGetMillisLength();


      virtual void delete_this();

      //virtual void      DecoderStop() = 0;

   };

} // namespace audio_decode

