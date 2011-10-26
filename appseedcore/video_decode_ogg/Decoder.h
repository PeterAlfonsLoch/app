#pragma once


namespace video_decode_ffmpeg
{


   class CLASS_DECL_VIDDEC_OGG decoder :
      public video_decode::decoder,
      public audio_decode_vorbis::decoder
   {
   public:

      class CLASS_DECL_VIDDEC_OGG packet_thread :
         virtual public simple_thread
      {
      public:


         decoder *                        m_pdecoder;
         //raw_array < AVPacket >           m_packetaVideo;
         //raw_array < AVPacket >           m_packetaAudio;
         bool_array                       m_readyaVideo;
         bool_array                       m_readyaAudio;
         int                              m_iFreeVideo;
         int                              m_iFreeAudio;


         packet_thread(::ca::application * papp);


         virtual int run();


      };


      class CLASS_DECL_VIDDEC_OGG video_decode_thread :
         virtual public simple_thread
      {
      public:


         decoder *                              m_pdecoder;
//         raw_array < AVFrame * >                m_frameptra;
         base_array < primitive::memory >       m_mema;
         base_array < uint64_t, uint64_t >      m_ptsa;
         int_array                              m_iaFrameFinished;
         int                                    m_iFree;
         int                                    m_iRead;


         video_decode_thread(::ca::application * papp);


         virtual int run();


      };

      class CLASS_DECL_VIDDEC_OGG video_scale_thread :
         virtual public simple_thread
      {
      public:


         decoder *   m_pdecoder;
         int         m_iFree;
         int         m_iRead;

         video_scale_thread(::ca::application * papp);


         virtual int run();


         //virtual void scale(::ca::dib & dib, AVCodecContext * pcodec, AVFrame * pframe);


      };


      class CLASS_DECL_VIDDEC_OGG audio_decode_thread :
         virtual public simple_thread
      {
      public:


         decoder *         m_pdecoder;
         int               m_iRead;
         int               m_iFree;


         audio_decode_thread(::ca::application * papp);


         virtual int run();


         void write_6_channel(int16_t * pdata, int iSize);
         void write_2_channel(int16_t * pdata, int iSize);
         void write_1_channel(int16_t * pdata, int iSize);


      };


      /*AVInputFormat *      m_pinputformat;
      AVFormatContext *    m_pformat;
      AVIOContext *        m_pio;*/
      int                  m_iVideoStreamIndex;
      int                  m_iAudioStreamIndex;
      int                  m_iTitleStreamIndex;
/*      AVCodecContext *     m_pcodecVideo;
      AVCodecContext *     m_pcodecAudio;
      AVCodecContext *     m_pcodecTitle;
      AVCodec *            m_pdecoderVideo;
      AVCodec *            m_pdecoderAudio;
      AVCodec *            m_pdecoderTitle;*/
      bool                 m_bPlay;

      gen::memory_file     m_memfileVideo;
      //raw_array < AVSubtitle * >    m_titleptra;
      primitive::memory    m_memProbe;
      primitive::memory    m_memAudio;

      int                  m_iRemainingBytes;
      byte *               m_puchRawData;
      bool                 m_bFirstTime;
      file_avio            m_fileavio;


      packet_thread        m_packetthread;
      video_decode_thread  m_videodecodethread;
      video_scale_thread   m_videoscalethread;
      audio_decode_thread  m_audiodecodethread;


	   decoder(::ca::application * papp);
	   virtual ~decoder();



	   void GuessParameters();
	   void DecoderStop();
	   void ReadFrame();


//      int GetNextFrame(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtxVideo, AVCodecContext *pCodecCtxAudio, AVCodecContext *pCodecCtxTitle, int videoStream,  int audioStream, int titleStream, AVFrame * pframeVideo, AVFrame * pframeAudio, AVFrame * pframeTitle);

      virtual bool DecoderNextFrame();


      virtual bool      DecoderInitialize(ex1::file *pfile);
      virtual void      DecoderFinalize();


      virtual void      DecoderMoveNext();
      virtual bool      DecoderEOF();
      virtual LPBYTE    DecoderGetBuffer();
      virtual int       DecoderGetBufferSize();
      virtual void      DecoderRun();
      virtual __int64   DecoderGetSampleCount();
      virtual UINT      DecoderGetSamplesPerSecond();
      virtual UINT      DecoderGetChannelCount();
      virtual UINT      DecoderGetBitsPerSample();
      virtual ::primitive::memory_size  _DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize);
      virtual void      DecoderSeekBegin();
      virtual bool      DecoderGetAttribute(video_decode::EAttribute eattribute, string & str);
      ID3_FrameID       GetAttributeId(video_decode::EAttribute eattribute);
      virtual bool      DecoderSetSeekable(bool bSet);
      virtual int       DecoderSetReadBlockSize(int iSize);


      virtual bool      _DecoderInitialize(ex1::file *pfile);
      virtual bool      _DecoderFinalize();
      virtual bool      _DecoderEOF();
      virtual bool      DecoderGetSeekable();


   };



} // namespace _vmsmpegdec

