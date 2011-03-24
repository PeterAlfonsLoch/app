#pragma once


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

      int m_iPlayDib;
      int m_iDib;
      int m_iLastDib;
      array_app_alloc < ::ca::dib, ::ca::dib > m_diba;
      base_array < int, int > m_ptsa;



      decoder(::ca::application * papp);
      virtual ~decoder();


      virtual bool decode();
      virtual bool step();

      
      virtual bool      DecoderInitialize(ex1::file *pfile) = 0;
      virtual bool      DecoderFinalize() = 0;


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
      virtual int       DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize) = 0;

      virtual __int64   DecoderGetSampleCount() = 0;
      virtual __int64   DecoderGetMillisLength();

      //virtual void      DecoderStop() = 0;

   };

} // namespace audio_decode

