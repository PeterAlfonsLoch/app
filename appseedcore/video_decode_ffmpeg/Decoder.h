#pragma once




namespace video_decode_ffmpeg
{

   class CLASS_DECL_VIDDEC_FFMPEG_BRIDGE decoder :
      public video_decode::decoder
   {
   public:

      AVFormatContext *pFormatCtx;
      int             videoStream;
      AVCodecContext  *pCodecCtx;
      AVCodec         *pCodec;
      //AVFrame         *pFrame; 
      AVFrame         *m_pframe;
      int             numBytes;
      uint8_t         *buffer;
      bool           m_bPlay;

      AVPacket packet;
      int      bytesRemaining;
      uint8_t  *rawData;
      bool     fFirstTime;


      
	   void GuessParameters();
	   void DecoderStop();
	   void ReadFrame();

      
	   decoder(::ca::application * papp);
	   virtual ~decoder();

      bool GetNextFrame(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtx, 
         int videoStream, AVFrame *pframe);

      virtual bool DecoderNextFrame();


      virtual bool      DecoderInitialize(ex1::file *pfile);
      virtual bool      DecoderFinalize();


      virtual void      DecoderMoveNext();
      virtual bool      DecoderEOF();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual __int64   DecoderGetSampleCount();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual int       DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize);
      virtual void      DecoderSeekBegin();
      virtual bool      DecoderGetAttribute(video_decode::EAttribute eattribute, string & str);
      ID3_FrameID       GetAttributeId(video_decode::EAttribute eattribute);
      virtual bool      DecoderSetSeekable(bool bSet);
      virtual int       DecoderSetReadBlockSize(int iSize);
   };



} // namespace _vmsmpegdec

