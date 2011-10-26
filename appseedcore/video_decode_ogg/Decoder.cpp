#include "StdAfx.h"


#define clip(x) min(255, max(0, x))


namespace video_decode_ffmpeg
{


   decoder::decoder(::ca::application * papp) :
      ::ca::ca(papp),
      video_decode::decoder(papp),
      m_memfileVideo(papp),
      thread(papp),
      audio_decode_vorbis::decoder(papp),
      m_packetthread(papp),
      m_videodecodethread(papp),
      m_videoscalethread(papp),
      m_audiodecodethread(papp)
   {
      
//      av_register_all();

      m_memAudio.allocate(1024 * 1024);

      m_iBufferSize = 1024;

      m_pplayer = NULL;

   }


   decoder::~decoder()
   {
   }


   void decoder::DecoderMoveNext()
   {
   }


   bool decoder::DecoderEOF()
   {
      return m_pplayer->m_iLastDib >= 0 && m_iDib == m_pplayer->m_iLastDib;
   }



   LPBYTE decoder::DecoderGetBuffer()
   {
      return NULL;
   }


   int decoder::DecoderGetBufferSize()
   {
      return 0;
   }


   void decoder::DecoderRun()
   {
   }


   UINT decoder::DecoderGetSamplesPerSecond()
   {
//      return m_pcodecAudio->sample_rate;
      return 44100;
   }


   UINT decoder::DecoderGetChannelCount()
   {
      /*if(m_pcodecAudio->channels == 1)
         return 1;
      else*/
         return 2;
   }


   UINT decoder::DecoderGetBitsPerSample()
   {
      return 16;
   }


   ::primitive::memory_size decoder::_DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize)
   {

      if(_DecoderEOF())
         return 0;

      return m_transferfileAudio.read(lpvoidBuffer, uiBufferSize);
      
   }


   void decoder::ReadFrame()
   {
   }


   void decoder::DecoderStop()
   {
   }


   void decoder::DecoderSeekBegin()
   {
      
      //av_seek_frame(m_pformat, m_iVideoStreamIndex, 0, 0);


   }


   void decoder::GuessParameters()
   {
   }


   bool decoder::DecoderGetAttribute(video_decode::EAttribute eattribute, string & str)
   {
      return false;
   }


   ID3_FrameID decoder::GetAttributeId(video_decode::EAttribute eattribute)
   {

      switch(eattribute)
      {
      case video_decode::AttributeTitle:
         return ID3FID_TITLE;
      case video_decode::AttributeAlbum:
         return ID3FID_ALBUM;
      case video_decode::AttributeOriginalAlbum:
         return ID3FID_ORIGALBUM;
      case video_decode::AttributeComposer:
         return ID3FID_COMPOSER;
      case video_decode::AttributeArtist:
         return ID3FID_LEADARTIST;
      case video_decode::AttributeYear:
         return ID3FID_YEAR;
      default:
         return ID3FID_NOFRAME;
      }

   }


   ssize_t ex1_file_read(void * ph, void * buf, size_t size)
   {
      return ((::ex1::file *) ph)->read(buf, size);
   }


   off_t ex1_file_seek(void * ph, off_t off, int i)
   {
      return ((::ex1::file *) ph)->seek(off, (::ex1::e_seek) i);
   }


   void ex1_file_close(void * ph)
   {
	   UNREFERENCED_PARAMETER(ph);
   }


   __int64 decoder::DecoderGetSampleCount()
   {
      return 0;
   }


   bool decoder::DecoderSetSeekable(bool bSet)
   {
      return false;
   }


   int decoder::DecoderSetReadBlockSize(int iSize)
   {
      return 0;
   }


   bool decoder::DecoderNextFrame()
   {

      Sleep(84);

      return true;


   }


/*   int decoder::GetNextFrame(AVFormatContext * pformat, AVCodecContext *pcodecVideo, AVCodecContext *pcodecAudio, AVCodecContext *pcodecTitle, int iVideoStreamIndex, int iAudioStreamIndex, int iTitleStreamIndex, AVFrame *pframeVideo, AVFrame *pframeAudio, AVFrame *pframeTitle)
   {

      return 0;

   }*/

   bool decoder::DecoderInitialize(ex1::file *pfile)
   {

      return false;

      m_iDib = 0;

      /*m_pformat = NULL;

      AVInputFormat * pinputformat = NULL;
      AVProbeData probe_data;
      int iSize = 1024;
      probe_data.filename = "";
      {
         while(iSize < 1024 * 1024 )
         {
            m_memProbe.allocate(iSize + AVPROBE_PADDING_SIZE);
            probe_data.buf_size = iSize; 
            probe_data.buf = (unsigned char *) av_malloc(iSize + AVPROBE_PADDING_SIZE);
            memset(probe_data.buf, 0, iSize + AVPROBE_PADDING_SIZE);
            pfile->seek_to_begin();
            probe_data.buf_size = pfile->read(probe_data.buf, probe_data.buf_size);
            pinputformat = av_probe_input_format(&probe_data, 1);
            if(pinputformat != NULL)
               break;
            av_free(probe_data.buf);
            iSize = iSize * 2;
         }
      }

      pfile->seek_to_begin();
      pinputformat->flags |= AVFMT_NOFILE; 

      m_pio = m_fileavio.alloc_context(pfile, 0);

      // open video file
      if(av_open_input_stream(&m_pformat, m_pio, "", pinputformat, NULL) != 0)
         return false; // Couldn't open file

      // Retrieve stream information
      if(av_find_stream_info(m_pformat) < 0)
         return false; // Couldn't find stream information

      // find the first video stream
      m_iVideoStreamIndex = -1;
      int i;
      int video_len = -1;
      int video_max_len = -1;
      int audio_len = -1;
      int audio_max_len = -1;
      int title_len = -1;
      int title_max_len = -1;
      for(i=0; i<m_pformat->nb_streams; i++)
      {
         if(m_pformat->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)
         {
            video_len = m_pformat->streams[i]->duration;
            if(video_len > video_max_len)
            {
               m_iVideoStreamIndex=i;
               video_max_len = video_len;
            }
         }
         else if(m_pformat->streams[i]->codec->codec_type==CODEC_TYPE_AUDIO)
         {
            audio_len = m_pformat->streams[i]->duration;
            if(audio_len > audio_max_len)
            {
               m_iAudioStreamIndex=i;
               audio_max_len = audio_len;
            }
         }
         else if(m_pformat->streams[i]->codec->codec_type==CODEC_TYPE_SUBTITLE)
         {
            title_len = m_pformat->streams[i]->duration;
            if(title_len > title_max_len)
            {
               m_iTitleStreamIndex=i;
               title_max_len = title_len;
            }
         }
      }

      if(m_iVideoStreamIndex == -1)
         return false; // Didn't find a video stream

      // get a pointer to the codec context for the video stream
      m_pcodecVideo=m_pformat->streams[m_iVideoStreamIndex]->codec;

      // find the decoder for the video stream
      m_pdecoderVideo=avcodec_find_decoder(m_pcodecVideo->codec_id);
      if(m_pdecoderVideo==NULL)
         return false; // Codec not found

      // Inform the codec that we can handle truncated bitstreams -- i.e.,
      // bitstreams where frame boundaries can fall in the middle of packets
      if(m_pdecoderVideo->capabilities & CODEC_CAP_TRUNCATED)
         m_pcodecVideo->flags|=CODEC_FLAG_TRUNCATED;

      // open codec
      if(avcodec_open(m_pcodecVideo, m_pdecoderVideo)<0)
         return false; // Could not open codec

      // Hack to correct wrong frame rates that seem to be generated by some 
      // codecs
      if(m_pcodecVideo->time_base.num>1000 && m_pcodecVideo->time_base.den==1)
		   m_pcodecVideo->time_base.den=1000;
      // allocate video frame
      //pframe=avcodec_alloc_frame();

      // allocate an AVFrame structure
      for(int i = 0; i < m_videodecodethread.m_frameptra.get_size(); i++)
      {
         AVFrame * pframe = avcodec_alloc_frame();
         if(pframe  == NULL)
            return false;
         pframe->opaque = this;
         m_videodecodethread.m_frameptra[i] = pframe;
         // Determine required buffer size and allocate buffer
         m_videodecodethread.m_mema[i].allocate(avpicture_get_size(PIX_FMT_RGB24, m_pcodecVideo->width, m_pcodecVideo->height) + 32);
         // Assign appropriate parts of buffer to image planes in pframe
         avpicture_fill((AVPicture *)pframe, (uint8_t *) (((UINT_PTR)((byte *)m_videodecodethread.m_mema[i].get_data()) + 15) & ~15), PIX_FMT_RGB24, m_pcodecVideo->width, m_pcodecVideo->height);
      }

         
      m_bFirstTime = true;
      m_iRemainingBytes = 0;

      m_bPlay = true;

      if(m_iAudioStreamIndex >= 0)
      {

         // get a pointer to the codec context for the video stream
         m_pcodecAudio=m_pformat->streams[m_iAudioStreamIndex]->codec;

         // find the decoder for the video stream
         m_pdecoderAudio=avcodec_find_decoder(m_pcodecAudio->codec_id);
         if(m_pdecoderAudio==NULL)
            return false; // Codec not found

         // Inform the codec that we can handle truncated bitstreams -- i.e.,
         // bitstreams where frame boundaries can fall in the middle of packets
         if(m_pdecoderAudio->capabilities & CODEC_CAP_TRUNCATED)
            m_pcodecAudio->flags|=CODEC_FLAG_TRUNCATED;

         // open codec
         if(avcodec_open(m_pcodecAudio, m_pdecoderAudio)<0)
            return false; // Could not open codec

         // Hack to correct wrong frame rates that seem to be generated by some 
         // codecs
         if(m_pcodecAudio->time_base.num>1000 && m_pcodecAudio->time_base.den==1)
		      m_pcodecAudio->time_base.den=1000;

      }

      m_packetthread.m_pdecoder = this;
      m_videodecodethread.m_pdecoder = this;
      m_videoscalethread.m_pdecoder = this;
      m_audiodecodethread.m_pdecoder = this;


      // DecoderSeekBegin
      {

      //av_seek_frame(m_pformat, 0, 0, 0);

      //m_pplayer->m_iPlayDib           = 0;
      m_iDib               = 0;
      m_bFirstTime         = true;
      m_iRemainingBytes    = 0;

      //m_pplayer->m_iLastDib           = -1;

      //m_pplayer->m_iPlayDib           = m_pplayer->m_diba.get_upper_bound();
      }

      m_packetthread.Begin();
      m_videodecodethread.Begin();
      m_videoscalethread.Begin();
      m_audiodecodethread.Begin();
        */ 

return true;
   }




   decoder::packet_thread::packet_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_iFreeVideo  = 0;
      m_iFreeAudio  = 0;
      /*m_packetaVideo.set_size(284);
      m_packetaAudio.set_size(284);*/
/*      m_readyaVideo.set_size(m_packetaVideo.get_size());
      m_readyaAudio.set_size(m_packetaAudio.get_size());*/
   }


   int decoder::packet_thread::run()
   {
      /*AVPacket packet;
      AVPacket packetx;
      av_init_packet(&packet);
      av_seek_frame(m_pdecoder->m_pformat, m_pdecoder->m_iVideoStreamIndex, 0, 0);
      while(true)
      {
         while(m_packetaVideo[m_iFreeVideo].data == NULL && m_packetaAudio[m_iFreeAudio].data == NULL && !m_readyaVideo[m_iFreeVideo] && !m_readyaAudio[m_iFreeAudio])
         {
            if(av_read_frame(m_pdecoder->m_pformat, &packet) < 0)
               return 0;
            packetx = packet;
            packet.destruct = NULL;
            if(packet.stream_index == m_pdecoder->m_iVideoStreamIndex)
            {
               AVPacket * ppacketNew = &m_packetaVideo[m_iFreeVideo];
               *ppacketNew = packet;
               av_dup_packet(ppacketNew);
               m_readyaVideo[m_iFreeVideo] = true;
               m_iFreeVideo++;
               if(m_iFreeVideo >= m_packetaVideo.get_size())
                  m_iFreeVideo = 0;
            }
            else if(packet.stream_index == m_pdecoder->m_iAudioStreamIndex)
            {
               AVPacket * ppacketNew = &m_packetaAudio[m_iFreeAudio];
               *ppacketNew = packet;
               av_dup_packet(ppacketNew);
               m_readyaAudio[m_iFreeAudio] = true;
               m_iFreeAudio++;
               if(m_iFreeAudio >= m_packetaAudio.get_size())
                  m_iFreeAudio = 0;
            }
            packet = packetx;
            av_free_packet(&packet);
         }
         Sleep(84);
      }*/
      return true;

   }

   decoder::video_decode_thread::video_decode_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
//      m_frameptra.set_size(84);
//      m_mema.set_size(m_frameptra.get_size());
      m_iaFrameFinished.set_size(m_mema.get_size());
      m_ptsa.set_size(m_iaFrameFinished.get_size());
      m_iFree = 0;
      m_iRead = 0;
   }

   int decoder::video_decode_thread::run()
   {
      double dRate;
      /*dRate = av_q2d(m_pdecoder->m_pcodecVideo->time_base) * 1000.0;
      int frameFinished;
      uint64_t ptsFirst = AV_NOPTS_VALUE;
      int64_t iFrame = 0;
      while(true)
      {
         while(m_iaFrameFinished[m_iFree] == 0 && m_pdecoder->m_packetthread.m_packetaVideo[m_iRead].data != NULL && m_pdecoder->m_packetthread.m_readyaVideo[m_iRead])
         {
            AVFrame * pframe = m_frameptra[m_iFree];
            AVPacket * ppacket = &m_pdecoder->m_packetthread.m_packetaVideo[m_iRead];
            avcodec_decode_video2(m_pdecoder->m_pcodecVideo, pframe, &frameFinished, ppacket);
            if(frameFinished)
            {
               if(pframe->pts == AV_NOPTS_VALUE)
               {
                  m_ptsa[m_iFree] = pframe->pkt_pts;
               }
               else
               {
                  if(pframe->pts == 0)
                  {
                     m_ptsa[m_iFree] = pframe->pkt_pts;
                  }
                  else if(ptsFirst == AV_NOPTS_VALUE)
                  {
                     ptsFirst = pframe->pkt_pts;
                     m_ptsa[m_iFree] = 0;
                  }
                  else
                  {
                     m_ptsa[m_iFree] = (pframe->pkt_pts - ptsFirst) * dRate;
                  }
               }
               m_iaFrameFinished[m_iFree] = 1;
               m_iFree++;
               if(m_iFree >= m_frameptra.get_size())
                  m_iFree = 0;
            }
            av_free_packet(&m_pdecoder->m_packetthread.m_packetaVideo[m_iRead]);
            m_pdecoder->m_packetthread.m_readyaVideo[m_iRead] = false;
            m_iRead++;
            if(m_iRead >= m_pdecoder->m_packetthread.m_packetaVideo.get_size())
            {
               m_iRead = 0;
            }
         }
         Sleep(84);
      }*/


      return 0;
   }

   decoder::video_scale_thread::video_scale_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_iFree = 0;
      m_iRead = 0;
   }


   int decoder::video_scale_thread::run()
   {

/*      AVCodecContext * pcodec = m_pdecoder->m_pcodecVideo;

      while(true)
      {
       
         while(m_pdecoder->m_pplayer != NULL && (!m_pdecoder->m_pplayer->m_scaleda[m_iFree] || m_pdecoder->m_pplayer->m_ptsa[m_iFree] < m_pdecoder->m_pplayer->get_pts())
            && m_pdecoder->m_videodecodethread.m_iaFrameFinished[m_iRead])
         {

            m_pdecoder->m_pplayer->m_scaleda[m_iFree] = false;

            AVFrame * pframe = m_pdecoder->m_videodecodethread.m_frameptra[m_iRead];

            ::ca::dib & dib = m_pdecoder->m_pplayer->m_diba[m_iFree];

            scale(dib, pcodec, pframe);

            m_pdecoder->m_pplayer->m_ptsa[m_iFree] = m_pdecoder->m_videodecodethread.m_ptsa[m_iRead];
            
            m_pdecoder->m_videodecodethread.m_iaFrameFinished[m_iRead] = 0;

            m_pdecoder->m_pplayer->m_scaleda[m_iFree] = true;

            m_iFree++;

            if(m_iFree >= m_pdecoder->m_pplayer->m_scaleda.get_size())
               m_iFree = 0;

            m_iRead++;

            if(m_iRead >= m_pdecoder->m_videodecodethread.m_iaFrameFinished.get_size())
               m_iRead = 0;

         }
         Sleep(84);
      }*/
      return 0;
   }




   decoder::audio_decode_thread::audio_decode_thread(::ca::application * papp) :
      ca(papp),
      thread(papp),
      simple_thread(papp)
   {
      m_iRead = 0;
   }


   int decoder::audio_decode_thread::run()
   {
      int iRet;
      gen::memory_file fIn(get_app());
/*      AVPacket p;
      bool bFirst = true;
      double dRate;
      dRate = av_q2d(m_pdecoder->m_pcodecAudio->time_base);
      if(dRate == 0.0)
         dRate = 1.0;
      while(true)
      {
         while(m_pdecoder->m_packetthread.m_packetaAudio[m_iRead].data != NULL && m_pdecoder->m_packetthread.m_readyaAudio[m_iRead])
         {
            AVPacket * ppacket = &m_pdecoder->m_packetthread.m_packetaAudio[m_iRead];
            int size = m_pdecoder->m_memAudio.get_size();
            unsigned char *buffer = (unsigned char *)(((int)m_pdecoder->m_memAudio.get_data()+15) &~15); 
            size -= buffer - (unsigned char *)m_pdecoder->m_memAudio.get_data();
            memset(m_pdecoder->m_memAudio, 0, size);
            CodecID id = m_pdecoder->m_pcodecAudio->codec_id;
            try
            {
               iRet = avcodec_decode_audio3(m_pdecoder->m_pcodecAudio, (int16_t *) buffer, &size, ppacket);
            }
            catch(...)
            {
               size = 0;
            }
            if(size > 0)
            {
               if(bFirst)
               {
                  bFirst = false;
                  if(m_pdecoder->m_pformat->streams[m_pdecoder->m_iAudioStreamIndex]->start_time > 0)
                  {
                     const int iCount = 512;
                     int16_t * pshBuf = new int16_t[iCount];
                     memset(pshBuf, 0, sizeof(int16_t) * iCount);
                     int iWrite = m_pdecoder->m_pformat->streams[m_pdecoder->m_iAudioStreamIndex]->start_time * m_pdecoder->DecoderGetSamplesPerSecond() * m_pdecoder->DecoderGetChannelCount() * m_pdecoder->DecoderGetBitsPerSample() / 16000;

                     while(iWrite > 0)
                     {
                        int iRead = min(iWrite, sizeof(int16_t) * iCount);
                        m_pdecoder->m_memfileAudio.write(buffer, iRead);
                        iWrite -= iRead;
                     }

                     delete pshBuf;
                  }
               }
               int16_t * pdata = (int16_t *) buffer;
               if(m_pdecoder->m_pcodecAudio->channels == 6)
               {
                  write_6_channel(pdata, size) ;
               }
               else if(m_pdecoder->m_pcodecAudio->channels == 2)
               {
                  write_2_channel(pdata, size);
               }
               else if(m_pdecoder->m_pcodecAudio->channels == 1)
               {
                  write_1_channel(pdata, size);
               }
               else
               {
                  m_pdecoder->m_memfileAudio.write(buffer, size);
               }
            }
            av_free_packet(ppacket);
            m_pdecoder->m_packetthread.m_readyaAudio[m_iRead] = false;
            m_iRead++;
            if(m_iRead >= m_pdecoder->m_packetthread.m_packetaAudio.get_size())
            {
               m_iRead = 0;
            }
         }
         /*single_lock slAudioBuffer(&m_pdecoder->m_memfileAudioBuffer.m_spmutex, true);
         single_lock slAudio(&m_pdecoder->m_memfileAudio.m_spmutex, true);
         m_pdecoder->m_memfileAudio.write(m_pdecoder->m_memfileAudioBuffer.get_data(), m_pdecoder->m_memfileAudioBuffer.get_size());
         m_pdecoder->m_memfileAudioBuffer.Truncate(0);*/
         /*Sleep(84);
      }*/

      return 0;
   }

   void decoder::audio_decode_thread::write_6_channel(int16_t * pdata, int size)
   {
      for(int i = 0; i < size; i += 6)
      {
         pdata[i / 3 + 0]  =  pdata[i + 1];
         pdata[i / 3 + 1]  =  pdata[i + 2];
      }
      m_pdecoder->m_memfileAudio.write(pdata, size / 3);
   }

   void decoder::audio_decode_thread::write_2_channel(int16_t * pdata, int size)
   {
      m_pdecoder->m_memfileAudio.write(pdata, size);
   }

   void decoder::audio_decode_thread::write_1_channel(int16_t * pdata, int size)
   {
      m_pdecoder->m_memfileAudio.write(pdata, size);
   }

   void decoder::DecoderFinalize()
   {

      // close the codec
/*      avcodec_close(m_pcodecVideo);

      // close the video file
      av_close_input_file(m_pformat);*/

   }


   bool decoder::_DecoderInitialize(ex1::file *pfile)
   {
      return true;
   }


   bool decoder::_DecoderFinalize()
   {
      return true;
   }
   

   bool decoder::_DecoderEOF()
   {
      return false;
   }


   bool decoder::DecoderGetSeekable()
   {
      return false;
   }

//   void decoder::video_scale_thread::scale(::ca::dib & dib, AVCodecContext * pcodec, AVFrame * pframe)
  // {
      /*if(pcodec->width != dib.width() || pcodec->height != dib.height())
      {
         dib.create(pcodec->width, pcodec->height);
      }

      if(pcodec->pix_fmt == PIX_FMT_RGB555)
      {
         COLORREF * pref = dib.get_data();
         unsigned short * push = (unsigned short *) pframe->data[0];
         int w = pframe->linesize[0] / 2;
         for(int i = 0; i < pcodec->height; i++)
         {
            for(int j = 0; j < pcodec->width; j++)
            {
               int B = (((*(push+i*w + j) >> 10) & 0x1f)<< 3);
               int G = (((*(push+i*w + j) >> 5) & 0x1f)<< 3);
               int R = ((*(push+i*w + j) & 0x1f) << 3);
               *(pref + (pcodec->height - i - 1) * pcodec->width + j) = RGB(R, G, B);
            }
         }
      }
      else if(pcodec->pix_fmt == PIX_FMT_YUV420P)
      {
         COLORREF * pref = dib.get_data();
         for(int i = 0; i < pcodec->height; i+=2)
         {
            for(int j = 0; j < pcodec->width; j+=2)
            {
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  *(pref + i * pcodec->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  *(pref + i * pcodec->width + j + 1) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  *(pref + (i + 1) * pcodec->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  *(pref + (i + 1) * pcodec->width + (j + 1)) = RGB(R, G, B);
               }
            }
         }
      }*/
//   }


} // namespace video_decode_ffmpeg









video_decode::decoder * __cdecl video_decode_new_decoder(::ca::application * papp)
{
   return dynamic_cast < video_decode::decoder * > (new video_decode_ffmpeg::decoder(papp));
}


void __cdecl video_decode_delete_decoder(video_decode::decoder * pdecoder)
{
   delete dynamic_cast < video_decode_ffmpeg::decoder * > (pdecoder);
}


