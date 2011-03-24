#include "StdAfx.h"


namespace video_decode_ffmpeg
{


   decoder::decoder(::ca::application * papp) :
      ::ca::ca(papp),
      video_decode::decoder(papp)
   {

   }

   decoder::~decoder()
   {
   }
   void decoder::DecoderMoveNext()
   {
   //   ReadNextFrame();
   }
   bool decoder::DecoderEOF()
   {
      return m_iLastDib >= 0 && m_iDib == m_iLastDib;
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
      return 0;
   }

   UINT decoder::DecoderGetChannelCount()
   {
      return 0;
   }
   UINT decoder::DecoderGetBitsPerSample()
   {
      return 16;
   }

   int decoder::DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      /*if(DecoderEOF())
         return 0;

//      LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer; 
      UINT uiRemain = uiBufferSize;
      UINT uiPointer = 0;
      UINT uiSize;
      
      while(uiRemain > 0)
      {
         if(m_bStop)
            return uiPointer;
         if(DecoderEOF())
            return 0;

         m_readframe._ReadFrame();

         uiSize = min(uiRemain, GetMemoryFile().get_size());

         GetMemoryFile().RemoveBegin(&((unsigned char *)lpvoidBuffer)[uiPointer], uiSize);

         uiRemain -= uiSize;
         uiPointer += uiSize;

         if(uiSize == 0 && m_readframe.IsEof())
            return 0;


      }
      
      /*if ( NativeByteOrder == order_littleEndian )
      {
         SwapBytesInWords( (short *) lpbBuffer, uiBufferSize / 2 );
      }*/
//      return uiPointer;
      return 0;
   }


   void decoder::ReadFrame()
   {

//      m_readframe._ReadFrame();
    
   }

   void decoder::DecoderStop()
   {
      //m_bStop = true;

   //   m_readframe.Stop();
   }

   void decoder::DecoderSeekBegin()
   {
      av_seek_frame(pFormatCtx, videoStream, 0, 0);
      m_iPlayDib = 0;
      m_iDib = 0;
      fFirstTime = true;
      bytesRemaining = 0;

      m_bPlay = true;
      m_iLastDib = -1;

      //m_bStop           = false;
      //m_iReadPointer    = 0;
      //m_memfile.Truncate(0);
   //   m_readframe.seek_begin();
      m_iLastDib = -1;
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
      return ((::ex1::file *) ph)->seek(off, i);
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

#define clip(x) min(255, max(0, x))
   bool decoder::DecoderNextFrame()
   {
      int iDibTop = m_iDib - 1;
      if(iDibTop < 0)
         iDibTop += m_diba.get_size();
      if(iDibTop == m_iPlayDib)
         return false;
      if(!GetNextFrame(pFormatCtx, pCodecCtx, videoStream, m_pframe))
      {
         m_iLastDib = m_iDib;
         return false;
      }

      

      ::ca::dib & dib = m_diba[m_iDib];

      if(pCodecCtx->width != dib.width() ||
         pCodecCtx->height != dib.height())
      {
         dib.create(pCodecCtx->width, pCodecCtx->height);
      }


      m_ptsa[m_iDib] = m_pframe->pts;


      /*COLORREF * pref = m_spdib.get_data();
      for(int i = 0; i < pCodecCtx->height; i++)
      {
      for(int j = 0; j < pCodecCtx->width; j++)
      {
      int C = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 0) - 16;
      int D = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 1) - 128;
      int E = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 2) - 128;
      int R = clip(( 298 * C           + 409 * E + 128) >> 8);
      int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
      int B = clip(( 298 * C + 516 * D           + 128) >> 8);
      *pref = RGB(R, G, B);
      pref++;
      }
      }*/

      AVFrame * pframe = m_pframe;
      if(pCodecCtx->pix_fmt == PIX_FMT_RGB555)
      {
         COLORREF * pref = dib.get_data();
         unsigned short * push = (unsigned short *) pframe->data[0];
         int w = pframe->linesize[0] / 2;
         for(int i = 0; i < pCodecCtx->height; i++)
         {
            for(int j = 0; j < pCodecCtx->width; j++)
            {
               int B = (((*(push+i*w + j) >> 10) & 0x1f)<< 3);
               int G = (((*(push+i*w + j) >> 5) & 0x1f)<< 3);
               int R = ((*(push+i*w + j) & 0x1f) << 3);
               *(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j) = RGB(R, G, B);
            }
         }
      }
      else if(pCodecCtx->pix_fmt == PIX_FMT_YUV420P)
      {
         COLORREF * pref = dib.get_data();
         for(int i = 0; i < pCodecCtx->height; i+=2)
         {
            for(int j = 0; j < pCodecCtx->width; j+=2)
            {
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j) = RGB(R, G, B);
                  *(pref + i * pCodecCtx->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j + 1) = RGB(R, G, B);
                  *(pref + i * pCodecCtx->width + j + 1) = RGB(R, G, B);

               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 2) * pCodecCtx->width + j) = RGB(R, G, B);
                  *(pref + (i + 1) * pCodecCtx->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 2) * pCodecCtx->width + (j + 1)) = RGB(R, G, B);
                  *(pref + (i + 1) * pCodecCtx->width + (j + 1)) = RGB(R, G, B);
               }
            }
         }
      }

      // Save the frame to disk
      //        if(++i<=5)
      //          SaveFrame(pframe, pCodecCtx->width, pCodecCtx->height, i);
   }


   bool decoder::GetNextFrame(AVFormatContext *pFormatCtx, AVCodecContext *pCodecCtx, 
      int videoStream, AVFrame *pframe)
   {
      int             bytesDecoded;
      int             frameFinished;

      // First time we're called, set packet.data to NULL to indicate it
      // doesn't have to be freed
      if(fFirstTime)
      {
         fFirstTime=false;
         packet.data=NULL;
      }

      // Decode packets until we have decoded a complete frame
      while(true)
      {
         // Work on the current packet until we have decoded all of it
         while(bytesRemaining > 0)
         {
            // Decode the next chunk of data
            bytesDecoded=avcodec_decode_video(pCodecCtx, pframe,
               &frameFinished, rawData, bytesRemaining);

            // Was there an error?
            if(bytesDecoded < 0)
            {
               fprintf(stderr, "Error while decoding frame\n");
               return false;
            }

            bytesRemaining-=bytesDecoded;
            rawData+=bytesDecoded;

            // Did we finish the current frame? Then we can return
            if(frameFinished)
               return true;
         }

         // read the next packet, skipping all packets that aren't for this
         // stream
         do
         {
            // Free old packet
            if(packet.data!=NULL)
               av_free_packet(&packet);

            // read new packet
            if(av_read_frame(pFormatCtx, &packet)<0)
               goto loop_exit;
         } while(packet.stream_index!=videoStream);

         bytesRemaining=packet.size;
         rawData=packet.data;
      }

loop_exit:

      // Decode the rest of the last frame
      bytesDecoded=avcodec_decode_video(pCodecCtx, pframe, &frameFinished, 
         rawData, bytesRemaining);

      // Free last packet
      if(packet.data!=NULL)
         av_free_packet(&packet);

      return frameFinished!=0;
   }

   bool decoder::DecoderInitialize(ex1::file *pfile)
   {
      m_iPlayDib = 0;
      m_iDib = 0;

      // open video file
      if(av_open_input_file(&pFormatCtx, pfile->GetFilePath(), NULL, 0, NULL)!=0)
         return false; // Couldn't open file

      // Retrieve stream information
      if(av_find_stream_info(pFormatCtx)<0)
         return false; // Couldn't find stream information

      // Dump information about file onto standard error
      //dump_format(pFormatCtx, 0, argv[1], false);

      // find the first video stream
      videoStream=-1;
      int i;
      for(i=0; i<pFormatCtx->nb_streams; i++)
         if(pFormatCtx->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)
         {
            videoStream=i;
            break;
         }
         if(videoStream==-1)
            return false; // Didn't find a video stream

         // get a pointer to the codec context for the video stream
         pCodecCtx=pFormatCtx->streams[videoStream]->codec;

         // find the decoder for the video stream
         pCodec=avcodec_find_decoder(pCodecCtx->codec_id);
         if(pCodec==NULL)
            return false; // Codec not found

         // Inform the codec that we can handle truncated bitstreams -- i.e.,
         // bitstreams where frame boundaries can fall in the middle of packets
         if(pCodec->capabilities & CODEC_CAP_TRUNCATED)
            pCodecCtx->flags|=CODEC_FLAG_TRUNCATED;

         // open codec
         if(avcodec_open(pCodecCtx, pCodec)<0)
            return false; // Could not open codec

         // Hack to correct wrong frame rates that seem to be generated by some 
         // codecs
         /*    if(pCodecCtx->frame_rate>1000 && pCodecCtx->frame_rate_base==1)
         pCodecCtx->frame_rate_base=1000;*/

         // allocate video frame
         //pframe=avcodec_alloc_frame();

         // allocate an AVFrame structure
         m_pframe = avcodec_alloc_frame();
         if(m_pframe == NULL)
            return false;

         // Determine required buffer size and allocate buffer
         numBytes=avpicture_get_size(PIX_FMT_RGB24, pCodecCtx->width,
            pCodecCtx->height);
         buffer=new uint8_t[numBytes];

         // Assign appropriate parts of buffer to image planes in pframe
         avpicture_fill((AVPicture *)m_pframe, buffer, PIX_FMT_RGB24,
            pCodecCtx->width, pCodecCtx->height);

         
         fFirstTime = true;
         bytesRemaining = 0;

         m_bPlay = true;
         m_iLastDib = -1;
   }

#define clip(x) min(255, max(0, x))


/*   bool decoder::DecoderNextFrame()
   {
      int iDibTop = m_iDib - 1;
      if(iDibTop < 0)
         iDibTop += m_diba.get_size();
      if(iDibTop == m_iPlayDib)
         return false;
      if(!GetNextFrame(pFormatCtx, pCodecCtx, videoStream, m_pframe))
      {
         // Free the RGB image
         delete [] buffer;
         av_free(m_pframe);

         // Free the YUV frame
//            av_free(pframe);

         // close the codec
         avcodec_close(pCodecCtx);

         // close the video file
         av_close_input_file(pFormatCtx);
         m_iLastDib = m_iDib;
         return false;
      }

      

      ::ca::dib & dib = m_diba[m_iDib];

      if(pCodecCtx->width != dib.width() ||
         pCodecCtx->height != dib.height())
      {
         dib.create(pCodecCtx->width, pCodecCtx->height);
      }


      m_ptsa[m_iDib] = m_pframe->pts;


      /*COLORREF * pref = m_spdib.get_data();
      for(int i = 0; i < pCodecCtx->height; i++)
      {
      for(int j = 0; j < pCodecCtx->width; j++)
      {
      int C = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 0) - 16;
      int D = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 1) - 128;
      int E = *(pframe->data[0]+i*pframe->linesize[0] + j * 3 + 2) - 128;
      int R = clip(( 298 * C           + 409 * E + 128) >> 8);
      int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
      int B = clip(( 298 * C + 516 * D           + 128) >> 8);
      *pref = RGB(R, G, B);
      pref++;
      }
      }*/

  /*    AVFrame * pframe = m_pframe;
      if(pCodecCtx->pix_fmt == PIX_FMT_RGB555)
      {
         COLORREF * pref = dib.get_data();
         unsigned short * push = (unsigned short *) pframe->data[0];
         int w = pframe->linesize[0] / 2;
         for(int i = 0; i < pCodecCtx->height; i++)
         {
            for(int j = 0; j < pCodecCtx->width; j++)
            {
               int B = (((*(push+i*w + j) >> 10) & 0x1f)<< 3);
               int G = (((*(push+i*w + j) >> 5) & 0x1f)<< 3);
               int R = ((*(push+i*w + j) & 0x1f) << 3);
               *(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j) = RGB(R, G, B);
            }
         }
      }
      else if(pCodecCtx->pix_fmt == PIX_FMT_YUV420P)
      {
         COLORREF * pref = dib.get_data();
         for(int i = 0; i < pCodecCtx->height; i+=2)
         {
            for(int j = 0; j < pCodecCtx->width; j+=2)
            {
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j) = RGB(R, G, B);
                  *(pref + i * pCodecCtx->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 0)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 1) * pCodecCtx->width + j + 1) = RGB(R, G, B);
                  *(pref + i * pCodecCtx->width + j + 1) = RGB(R, G, B);

               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 0) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 2) * pCodecCtx->width + j) = RGB(R, G, B);
                  *(pref + (i + 1) * pCodecCtx->width + j) = RGB(R, G, B);
               }
               {
                  int C = *(pframe->data[0]+(i + 1)*pframe->linesize[0] + j + 1) - 16;
                  int E = *(pframe->data[1]+(i / 2)*pframe->linesize[1] + j / 2) - 128;
                  int D = *(pframe->data[2]+(i / 2)*pframe->linesize[2] + j / 2) - 128;
                  int R = clip(( 298 * C           + 409 * E + 128) >> 8);
                  int G = clip(( 298 * C - 100 * D - 208 * E + 128) >> 8);
                  int B = clip(( 298 * C + 516 * D           + 128) >> 8);
                  //*(pref + (pCodecCtx->height - i - 2) * pCodecCtx->width + (j + 1)) = RGB(R, G, B);
                  *(pref + (i + 1) * pCodecCtx->width + (j + 1)) = RGB(R, G, B);
               }
            }
         }
      }
      m_iDib++;
      if(m_iDib >= m_diba.get_size())
         m_iDib = 0;

      // Save the frame to disk
      //        if(++i<=5)
      //          SaveFrame(pframe, pCodecCtx->width, pCodecCtx->height, i);
   }
   */


   bool decoder::DecoderFinalize()
   {

      // Free the RGB image
      delete [] buffer;
      av_free(m_pframe);

      // Free the YUV frame
//            av_free(pframe);

      // close the codec
      avcodec_close(pCodecCtx);

      // close the video file
      av_close_input_file(pFormatCtx);
      return true;

   }


} // namespace video_decode_ffmpeg









video_decode::decoder * __cdecl NewDecoderInterface(::ca::application * papp)
{
   return dynamic_cast < video_decode::decoder * > (new video_decode_ffmpeg::decoder(papp));
}

void __cdecl DeleteDecoderInterface(video_decode::decoder * pdecoder)
{
   delete dynamic_cast < video_decode_ffmpeg::decoder * > (pdecoder);
}

