#include "StdAfx.h"
#include "mpg123.h"
#include "id3.h"

#define   SYNC_WORD         (long) 0xfff
#define   SYNC_WORD_LNGTH   12

#define   MUTE              0




namespace audio_decode_libmpg123
{


   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp),
      audio_decode::decoder(papp),
      m_memfile(papp)
   {
      m_readframe.m_bSeekable = true;
      m_readframe.m_pdecoder = this;
      m_iBufferSize = 512 * 1024;
   }

   decoder::~decoder()
   {
      DecoderStop();
   }

   bool decoder::_DecoderInitialize(ex1::file *pfile)
   {
      m_bStop = false;
      GetMemoryFile().Truncate(0);

      if(m_spfile.is_set())
      {
         gen::release(m_spfile.m_p);
      }

      m_spfile(new ::ex1::buffered_file(get_app(), pfile, m_iBufferSize));

      try
      {

         m_bStop = false;
         m_iReadPointer = 0;
         m_spfile->seek_to_begin();

         if(!m_readframe.Initialize(m_spfile, &GetMemoryFile()))
            return false;
         int err;
         if(m_readframe.m_bSeekable)
         {
            err = mpg123_scan(m_readframe.m_phandle);
            m_nSampleCount = mpg123_length(m_readframe.m_phandle);
         }
         else
         {
            m_nSampleCount = 0;
         }

         GuessParameters();

         /*struct mpg123_frameinfo mi;
         memset(&mi, 0, sizeof(mi));
         int iRet = mpg123_info(m_readframe.m_phandle, &mi);
         if(iRet == MPG123_ERR || iRet > 0)
         {
            return false;
         }*/
         if(m_nSampleCount < 0)
            return false;

         if(m_readframe.m_bSeekable)
         {
            uint64_t dwPos = m_spfile->get_position();
            m_spfile->seek_to_begin();
            m_id3tag.clear();
            m_id3reader.m_pfile = m_spfile;
            m_id3tag.Link(m_id3reader);
            m_spfile->seek(dwPos, ex1::seek_begin);
         }

         if(m_readframe.m_bSeekable)
         {
            if(mpg123_seek(m_readframe.m_phandle, 0, SEEK_SET) < 0)
               return false;
         }

      }
      catch(...)
      {
         return false;
      }

      return true;
      
   }


   bool decoder::_DecoderFinalize()
   {
      m_readframe.Finalize();
      m_memfile.close();
      gen::release(m_spfile.m_p);
      return true;
   }


   void decoder::DecoderMoveNext()
   {
   //   ReadNextFrame();
   }
   bool decoder::_DecoderEOF()
   {
      return m_readframe.IsEof() && GetMemoryFile().get_size() == 0;
   }
   LPBYTE decoder::DecoderGetBuffer()
   {
      return GetMemoryFile().get_data();
   }
   int decoder::DecoderGetBufferSize()
   {
      return(int)  GetMemoryFile().get_size();
   }

   void decoder::DecoderRun()
   {
   }

   UINT decoder::DecoderGetSamplesPerSecond()
   {
      return m_readframe.m_lSamplesPerSecond;
   }

   UINT decoder::DecoderGetChannelCount()
   {
      return m_readframe.m_iChannels;
   }
   UINT decoder::DecoderGetBitsPerSample()
   {
      return 16;
   }

   ::primitive::memory_size decoder::_DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize)
   {
      if(_DecoderEOF())
         return 0;

//      LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer; 
      ::primitive::memory_size uiRemain = uiBufferSize;
      ::primitive::memory_size uiPointer = 0;
      ::primitive::memory_size uiSize;
      
      while(uiRemain > 0)
      {
         if(m_bStop)
            return uiPointer;
         if(_DecoderEOF())
            return 0;

         m_readframe._ReadFrame();

         uiSize = min(uiRemain, GetMemoryFile().get_size());

         uiSize = GetMemoryFile().remove_begin(&((unsigned char *)lpvoidBuffer)[uiPointer], uiSize);

         uiRemain -= uiSize;
         uiPointer += uiSize;

         if(uiSize <= 0)
            break;

      }
      
      /*if ( NativeByteOrder == order_littleEndian )
      {
         SwapBytesInWords( (short *) lpbBuffer, uiBufferSize / 2 );
      }*/

      return uiPointer;
   }


   void decoder::ReadFrame()
   {

      m_readframe._ReadFrame();
    
   }

   void decoder::DecoderStop()
   {
      m_bStop = true;

   //   m_readframe.Stop();
   }

   void decoder::DecoderSeekBegin()
   {
      m_bStop           = false;
      m_iReadPointer    = 0;
      m_memfile.Truncate(0);
      if(m_readframe.m_bSeekable)
      {
         mpg123_seek(m_readframe.m_phandle, 0, SEEK_SET);
      }
      else
      {
         m_readframe.m_pfileIn->seek_to_begin();
         m_readframe.Initialize(m_readframe.m_pfileIn, &GetMemoryFile());
         GuessParameters();
      }
   }

   void decoder::GuessParameters()
   {

      synch_lock lock(m_readframe.m_pfileIn);

      int  err  = MPG123_OK;
      /* Peek into track and get first output format. */
      if(mpg123_getformat(m_readframe.m_phandle, &m_readframe.m_lSamplesPerSecond, &m_readframe.m_iChannels, &m_readframe.m_iEncoding) != MPG123_OK )
      {
         fprintf( stderr, "Trouble with mpg123: %s\n",
         m_readframe.m_phandle==NULL ? mpg123_plain_strerror(err) : mpg123_strerror(m_readframe.m_phandle) );
        // cleanup(m_readframe.m_phandle);
         return;
      }

      if(m_readframe.m_iEncoding != MPG123_ENC_SIGNED_16)
      { 
         /* Signed 16 is the default output format anyways; it would actually by only different if we forced it.
         So this check is here just for this explanation. */
         //cleanup(m_phandle);
         fprintf(stderr, "Bad encoding: 0x%x!\n", m_readframe.m_iEncoding);
         return;
      }
      /* Ensure that this output format will not change (it could, when we allow it). */
      mpg123_format_none(m_readframe.m_phandle);
      mpg123_format(m_readframe.m_phandle, m_readframe.m_lSamplesPerSecond, m_readframe.m_iChannels, m_readframe.m_iEncoding);



   }

   bool decoder::DecoderGetAttribute(audio_decode::EAttribute eattribute, string & str)
   {

      if(!m_readframe.m_bSeekable)
         return false;
      synch_lock lock(m_readframe.m_pfileIn);
      ID3_FrameID eid = GetAttributeId(eattribute);



      if(eid  == ID3FID_NOFRAME)



         return false;

//      DWORD dw = m_readframe.m_pfileIn->get_position();
      
      ID3_Frame * pframe;

      if (pframe = m_id3tag.Find ( eid ))
      {

         str = pframe->GetField (ID3FN_TEXT).GetRawText();

         //m_readframe.m_pfileIn->seek(dw, ::ex1::seek_begin);
         
      }
      else
      {
         //m_readframe.m_pfileIn->seek(dw, ::ex1::seek_begin);
         return false;
      }
      return true;
   }

   ID3_FrameID decoder::GetAttributeId(audio_decode::EAttribute eattribute)
   {
      switch(eattribute)
      {
      case audio_decode::AttributeTitle:
         return ID3FID_TITLE;
      case audio_decode::AttributeAlbum:
         return ID3FID_ALBUM;
      case audio_decode::AttributeOriginalAlbum:
         return ID3FID_ORIGALBUM;
      case audio_decode::AttributeComposer:
         return ID3FID_COMPOSER;
      case audio_decode::AttributeArtist:
         return ID3FID_LEADARTIST;
      case audio_decode::AttributeYear:
         return ID3FID_YEAR;
      default:
         return ID3FID_NOFRAME;
      }
   }

   decoder::ReadFrame::ReadFrame()
   {
      m_phandle   = NULL;  
      m_memoryIn.allocate(1024 * 128);
      m_memoryOut.allocate(1024 * 128 * 8);
      
   }

   ssize_t ex1_file_read(void * ph, void * buf, size_t size)
   {
      return ((::ex1::file *) ph)->read(buf, size);
   }

   off_t ex1_file_seek(void * ph, off_t off, int i)
   {
      return throw_cast < long > (((::ex1::file *) ph)->seek(off, (::ex1::e_seek) i));
   }

   void ex1_file_close(void * ph)
   {
	   UNREFERENCED_PARAMETER(ph);
   }

   bool decoder::ReadFrame::Initialize(ex1::file * pfileIn, ex1::file * pfileOut)
   {
      m_bFileInEof = false;
      if(m_phandle != NULL)
      {
         mpg123_delete(m_phandle);
         m_phandle = NULL;
      }
      
      int err  = MPG123_OK;
      m_phandle = mpg123_new(NULL, &err);

      if(m_bSeekable)
      {
         //mpg123_param(m_phandle, MPG123_ADD_FLAGS, MPG123_SKIP_ID3V2, 0);
         mpg123_replace_reader_handle(m_phandle, &ex1_file_read, &ex1_file_seek, &ex1_file_close);
         err = mpg123_open_handle(m_phandle, (void *)(::ex1::file *) pfileIn);
         if(err != MPG123_OK)
            return false;
      }
      else
      {
         err = mpg123_open_feed(m_phandle);
         if(err != MPG123_OK)
            return false;
      }

      m_bDecEof      = false;
      m_pfileIn      = pfileIn;
      m_pfileOut     = pfileOut;
      m_dwPos        = 0;
      m_bInit        = false;

      _ReadFrame();

      if(m_iRet != MPG123_OK
      && m_iRet != MPG123_NEW_FORMAT
      && m_iRet != MPG123_NEED_MORE)
         return false;

      return true;
   }

   bool decoder::ReadFrame::Finalize()
   {
      gen::release(m_pfileIn.m_p);
      gen::release(m_pfileOut.m_p);
      return true;
   }

   __int64 decoder::DecoderGetSampleCount()
   {
      return m_nSampleCount;
   }

   bool decoder::ReadFrame::_ReadFrame()
   {
      if(m_bSeekable)
      {
         return _seekable_read_frame();
      }
      else
      {
         return _non_seekable_read_frame();
      }
   }

   bool decoder::ReadFrame::_seekable_read_frame()
   {
      ASSERT(m_bSeekable);
      synch_lock lockOut(m_pfileOut);
      synch_lock lockIn(m_pfileIn);
      size_t done;
      int iRet;

      if(!m_bFileInEof)
      {
         while(m_pfileOut->get_length() < (m_memoryIn.get_size() * 8))
         {
            done = 0;
            iRet = MPG123_ERR;
            try
            {
               iRet = mpg123_read(
                  m_phandle, 
                  (unsigned char *) m_memoryOut.get_data(),
                  m_memoryOut.get_size(), 
                  &done);
            }
            catch(...)
            {
            }
            m_iRet = iRet;
            if(done > 0)
            {
               m_pfileOut->write(m_memoryOut.get_data(), done);
            }
            if(iRet == MPG123_NEW_FORMAT)
            {
            }
            else if(iRet == MPG123_DONE)
            {
               m_bFileInEof = true;
               m_bDecEof = true;
               break;
            }
         }
      }

      return true;
   }

   bool decoder::ReadFrame::_non_seekable_read_frame()
   {
      ASSERT(!m_bSeekable);
      synch_lock lockOut(m_pfileOut);
      synch_lock lockIn(m_pfileIn);
      size_t done;
      int iRet;
      int iRead = 0;
      int iTotalRead = 0;
      int iMaxCount = 1024 * 64;

      if(!m_bFileInEof)
      {
         while(iTotalRead < iMaxCount)
         {
            done = 0;
            iRet = MPG123_ERR;
            try
            {
               iRet = mpg123_decode(m_phandle, m_memoryIn, iRead, m_memoryOut, m_memoryOut.get_size(), &done);
               iTotalRead += iRead;
               iRead = 0;
            }
            catch(...)
            {
            }
            m_iRet = iRet;
            if(done > 0)
            {
               m_pfileOut->write(m_memoryOut.get_data(), done);
            }
            if(iRet == MPG123_NEW_FORMAT)
            {
            }
            else if(iRet == MPG123_DONE)
            {
            }
            else if(iRet == MPG123_ERR)
            {
               return false;
            }
            else if(iRet == MPG123_NEED_MORE)
            {
               if(m_pfileOut->get_length() >= m_memoryIn.get_size() * 8)
                  break;
               ::primitive::memory_size uiSize = m_memoryIn.get_size();
               if(m_pfileIn->get_length() != 0 && m_pfileIn->get_length() != ((uint64_t) -1)
                  && m_pfileIn->get_length() != ((uint64_t) -2))
               {
                  uiSize = min(uiSize, (::primitive::memory_size) (m_pfileIn->get_length() - m_pfileIn->get_position()));
               }
               iRead = m_pfileIn->read(m_memoryIn, uiSize);
               if(iRead <= 0)
               {
                  m_bFileInEof = true;
                  m_bDecEof = true;
                  break;
               }
            }
         }
      }

      if(iTotalRead >= iMaxCount)
      {
         m_bFileInEof = true;
         m_bDecEof = true;
      }

      return true;
   }

   decoder::ReadFrame::~ReadFrame()
   {
      if(m_phandle != NULL)
      {
         mpg123_delete(m_phandle);
         m_phandle = NULL;
      }
   }



   bool decoder::ReadFrame::IsEof()
   {
      return m_bFileInEof && m_bDecEof;
   }

   bool decoder::DecoderSetSeekable(bool bSet)
   {
      return m_readframe.m_bSeekable = bSet;
   }

   bool decoder::DecoderGetSeekable()
   {
      return m_readframe.m_bSeekable;
   }

   int decoder::DecoderSetReadBlockSize(int iSize)
   {
      if(iSize > 0)
      {
         m_readframe.m_memoryIn.allocate(iSize);
         m_iBufferSize = iSize;
      }
      return m_readframe.m_memoryIn.get_size();
   }

/*   inline CBitStream & decoder::GetBitStream()
   {
      return *m_pbitstream;
   }

   inline CHBitStream & decoder::GetHBitStream()
   {
      return *m_phbitstream;
   }*/

   gen::memory_file & decoder::GetMemoryFile()
   {
      return m_memfile;
   }



} // namespace audio_decode_libmpg123









audio_decode::decoder * __cdecl NewDecoderInterface(::ca::application * papp)
{
   return dynamic_cast < audio_decode::decoder * > (new audio_decode_libmpg123::decoder(papp));
}

void __cdecl DeleteDecoderInterface(audio_decode::decoder * pdecoder)
{
   delete dynamic_cast < audio_decode_libmpg123::decoder * > (pdecoder);
}

