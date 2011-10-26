#include "StdAfx.h"

enum byte_order { order_unknown, order_bigEndian, order_littleEndian };

enum byte_order NativeByteOrder = order_unknown;

enum byte_order DetermineByteOrder()
{
    char s[ sizeof(long) + 1 ];
    union
    {
        long longval;
        char charval[ sizeof(long) ];
    } probe;
    probe.longval = 0x41424344L;  /* ABCD in ASCII */
    strncpy( s, probe.charval, sizeof(long) );
    s[ sizeof(long) ] = '\0';
    /* fprintf( stderr, "byte order is %s\n", s ); */
    if ( strcmp(s, "ABCD") == 0 )
        return order_bigEndian;
    else
        if ( strcmp(s, "DCBA") == 0 )
            return order_littleEndian;
        else
            return order_unknown;
}

void SwapBytesInWords( short *loc, int words )
{
    int i;
    short thisval;
    char *dst, *src;
    src = (char *) &thisval;
    for ( i = 0; i < words; i++ )
    {
        thisval = *loc;
        dst = (char *) loc++;
        dst[0] = src[1];
        dst[1] = src[0];
    }
}


namespace audio_decode_cd
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp),
      ::audio_decode::decoder(papp),
      m_fileFrame(papp)
   {
      if(NativeByteOrder == order_unknown)
      {
         NativeByteOrder = DetermineByteOrder();
      }
      m_hcdrom    = NULL;
      m_bEOF      = false;
      m_dwBufferFrameCount = 26;
      m_lptrackbuf = NewTrackBuff(m_dwBufferFrameCount, m_dwBufferSize);
   }

   #define _DELETE___(ptr)       \
            if(ptr != NULL)      \
            {                    \
               delete ptr;       \
               ptr = NULL;       \
            }

   decoder::~decoder()
   {
      free(m_lptrackbuf);

   }

   typedef DWORD FOURCC;


   struct CDAUDIO
   {
      FOURCC            m_fourccRiff;
      DWORD             m_dwRiffLen;
      FOURCC            m_fourccCdda;
      FOURCC            m_fourccFmt;
      DWORD             m_dwFmtLen;
      unsigned short    m_ushVersion;
      unsigned short    m_ushTrack;
      DWORD             m_ushSerial;
   };

   HCDROM GetFirstCDHandle( void )
   {
     CDLIST cdlist;
     GETCDHAND cdh;

     ZeroMemory( &cdlist, sizeof(cdlist) );
     GetCDList( &cdlist );

     if ( cdlist.num == 0 )
       return NULL;

     ZeroMemory( &cdh, sizeof(cdh) );
     cdh.size     = sizeof(GETCDHAND);
     cdh.ver      = 1;
     cdh.ha       = cdlist.cd[0].ha;
     cdh.tgt      = cdlist.cd[0].tgt;
     cdh.lun      = cdlist.cd[0].lun;
     cdh.readType  = CDR_ANY;      // set for autodetect

     return GetCDHandle( &cdh );
   }

   LPTRACKBUF decoder::NewTrackBuff(DWORD numFrames, DWORD & dwFrameSize)
   {
     LPTRACKBUF t;

     dwFrameSize = (((int)numFrames)*2352);
     int numAlloc = dwFrameSize + TRACKBUFEXTRA;

     

     t = (LPTRACKBUF) malloc(numAlloc);

     if ( !t )
       return NULL;

     t->startFrame = 0;
     t->numFrames = 0;
     t->maxLen = numFrames * 2352;
     t->len = 0;
     t->status = 0;
     t->startOffset = 0;

     return t;
   }

   void MSB2DWORD( DWORD *d, BYTE *b )
   {
     DWORD retVal;

     retVal = (DWORD)b[0];
     retVal = (retVal<<8) + (DWORD)b[1];
     retVal = (retVal<<8) + (DWORD)b[2];
     retVal = (retVal<<8) + (DWORD)b[3];

     *d = retVal;
   }

   bool decoder::_DecoderInitialize(ex1::file *pfile)
   {
      m_uiReadSync = 0;
      m_pfile = pfile;
      m_bStop = false;
      m_bEOF = false;

      string strFilePath = pfile->GetFilePath();

      if(::GetDriveType(strFilePath.Left(3)) != DRIVE_CDROM)
      {
         return false;
      }

      CDAUDIO cdaudio;
      
      pfile->seek_to_begin();
      if(sizeof(CDAUDIO) !=
         pfile->read(&cdaudio, sizeof(CDAUDIO)))
      {
         return false;
      }

      if(cdaudio.m_fourccRiff != 0x46464952)
      {
         return false;
      }

      if(cdaudio.m_dwRiffLen != 0x24)
      {
         return false;
      }

      if(cdaudio.m_fourccCdda != 0x41444443)
      {
         return false;
      }

      if(cdaudio.m_fourccFmt != 0x20746D66)
      {
         return false;
      }

      if(cdaudio.m_dwFmtLen != 0x18)
      {
         return false;
      }

      if(cdaudio.m_ushVersion != 1)
      {
         return false;
      }

      int iTrack = cdaudio.m_ushTrack;


      if(m_hcdrom == NULL)
      {
         m_hcdrom = GetFirstCDHandle();
      }


      TOC toc;

      ZeroMemory( &toc, sizeof(TOC) );
      ModifyCDParms( m_hcdrom, CDP_MSF, FALSE );
      if ( ReadTOC( m_hcdrom, &toc ) != SS_COMP )
      {
         TRACE( "Error reading TOC\n" );
         return false;
      }

      MSB2DWORD( &m_dwStartFrame, toc.tracks[iTrack - 1].addr );
      MSB2DWORD( &m_dwFrameCount, toc.tracks[iTrack].addr );
      m_dwFrameCount -= m_dwStartFrame;

      m_dwCurrentFrame = m_dwStartFrame;
      m_dwRemain = m_dwFrameCount;
      m_nSampleCount = ((__int64) m_dwFrameCount * 2352 * 8) / ((__int64) DecoderGetBitsPerSample() * DecoderGetChannelCount());

      return true;
   }

   bool decoder::_DecoderFinalize()
   {
      return true;
   }

   void decoder::DecoderMoveNext()
   {
   }

   bool decoder::_DecoderEOF()
   {
      return m_bEOF;
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
      return (UINT) 44100;
   }
   UINT decoder::DecoderGetChannelCount()
   {
      return 2;
   }
   UINT decoder::DecoderGetBitsPerSample()
   {
      return 16;
   }

   __int64 decoder::DecoderGetSampleCount()
   {
      return m_nSampleCount;
   }

   ::primitive::memory_size decoder::_DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize)
   {
      LPBYTE lpbBuffer = (LPBYTE) lpvoidBuffer;
      UINT uiRemain = uiBufferSize;
      UINT uiPointer = 0;
      UINT uiSize;
      
      while(uiRemain > 0)
      {
         if(m_bStop)
            return uiPointer;

         if(m_fileFrame.get_size() <= 0)
         {
            ReadFrame();
         }
         if(m_fileFrame.get_size() <= 0)
         {
            m_bEOF = true;
            return uiPointer;
         }

         uiSize = m_fileFrame.remove_begin(&lpbBuffer[uiPointer], uiRemain);

         uiRemain -= uiSize;
         uiPointer += uiSize;

         if(uiSize <= 0)
            break;

      }
      return uiPointer;
   }

   void decoder::DecoderStop()
   {
      m_bStop = true;
   }

   void decoder::DecoderSeekBegin()
   {
      m_fileFrame.Truncate(0);
      m_dwCurrentFrame = m_dwStartFrame;
      m_dwRemain = m_dwFrameCount;
      m_bStop = false;
   }

   void decoder::ReadFrame()
   {
      if(!(m_dwFrame++ % 5))
	      TRACE( "%d: %d\n", m_dwCurrentFrame, m_dwRemain );

      int num2rip;

      if(m_dwRemain < m_dwBufferFrameCount)
	      num2rip = m_dwRemain;
      else
         num2rip = m_dwBufferFrameCount;

      int retries = 3;
      DWORD dwStatus = SS_ERR;

      while ( retries-- && (dwStatus != SS_COMP) )
	   {
	      m_lptrackbuf->numFrames = num2rip;
	      m_lptrackbuf->startOffset = 0;
	      m_lptrackbuf->len = 0;
	      m_lptrackbuf->startFrame = m_dwCurrentFrame;
	      dwStatus = ReadCDAudioLBA(m_hcdrom, m_lptrackbuf);
	   }
      m_fileFrame.write(m_lptrackbuf->buf, num2rip * 2352);
      
      m_dwCurrentFrame += num2rip;
      m_dwRemain -= num2rip;
      
   }

   void decoder::OnDecoderEOF()
   {
      CloseCDHandle(m_hcdrom);
   }


} // namespace _vmsaiffdec


audio_decode::decoder *  __cdecl NewDecoderInterface(::ca::application * papp)
{
   return new audio_decode_cd::decoder(papp);
}

void  DeleteDecoderInterface(audio_decode::decoder * pdecoder)
{
   delete (audio_decode_cd::decoder *) pdecoder;
}
