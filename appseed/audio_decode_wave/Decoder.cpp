#include "StdAfx.h"


#define   SYNC_WORD         (long) 0xfff
#define   SYNC_WORD_LNGTH   12

#define   MUTE              0


audio_decode::decoder * __cdecl NewDecoderInterface(::ca::application * papp)
{
   return dynamic_cast < audio_decode::decoder * > (new audio_decode_wave::decoder(papp));
}

void __cdecl DeleteDecoderInterface(audio_decode::decoder * pdecoder)
{
   delete dynamic_cast < audio_decode_wave::decoder * > (pdecoder);
}


namespace audio_decode_wave
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp),
      ::audio_decode::decoder(papp),
      m_memfile(papp)
   {
      m_bEof = false;
      m_bNonStopOnEof = false;
   }

   decoder::~decoder()
   {
   }

   bool decoder::_DecoderInitialize(ex1::file *pfile)
   {
      m_bStop = false;
      GetMemoryFile().Truncate(0);
      m_iReadPointer = 0;
      m_bEof = false;

      pfile->seek(0, ex1::seek_begin);
      
      try
      {
         m_inputfile.open(pfile);
      }
      catch(const char * lpsz)
      {
         TRACE("%s", lpsz);
         return false;
      }

      return true;
   }

   bool decoder::_DecoderFinalize()
   {
      gen::release(m_inputfile.m_pfile.m_p);
      return true;
   }

   void decoder::DecoderMoveNext()
   {
   //   ReadNextFrame();
   }
   bool decoder::_DecoderEOF()
   {
      if(m_bNonStopOnEof)
         return false;
      return m_bEof
         && GetMemoryFile().get_size() == 0;
   }
   LPBYTE decoder::DecoderGetBuffer()
   {
      return GetMemoryFile().get_data();
   }
   int decoder::DecoderGetBufferSize()
   {
      return GetMemoryFile().get_size();
   }

   void decoder::DecoderRun()
   {
   }

   UINT decoder::DecoderGetSamplesPerSecond()
   {
      return m_inputfile.m_fmtheader.wavFormat.dwSamplesPerSec;
   }

   UINT decoder::DecoderGetChannelCount()
   {
      return m_inputfile.m_fmtheader.wavFormat.wChannels;
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
      UINT uiRemain = uiBufferSize;
      UINT uiPointer = 0;
      UINT uiSize ;


      
      while(uiRemain > 0)
      {
         if(m_bStop)
            return uiPointer;
         if(_DecoderEOF())
            return uiPointer;

         ReadFrame();

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
      UINT uiRead;
      uiRead = m_inputfile.m_pfile->read(m_buf, sizeof(m_buf));
      if(uiRead == 0)
         m_bEof = true;
      GetMemoryFile().write(m_buf, uiRead);
   }

   void decoder::DecoderStop()
   {
      m_bStop = true;

   //   m_readframe.Stop();
   }

   void decoder::DecoderSeekBegin()
   {
      m_bStop           = false;
      m_bEof   = false;
      m_iReadPointer    = 0;
      m_memfile.Truncate(0);
   //   m_readframe.seek_begin();

   }

   void decoder::DecoderSeekEnd()
   {
      m_bStop           = false;
      m_bEof            = false;
      m_iReadPointer    = 0;
      m_memfile.Truncate(0);
      file_size iLength = m_inputfile.m_pfile->get_length();
      int iSampleSize = DecoderGetBitsPerSample() * DecoderGetChannelCount() / 8;
      m_inputfile.m_pfile->seek(
         m_inputfile.m_iStartOfData + 
         (iLength - m_inputfile.m_iStartOfData) - ((iLength - m_inputfile.m_iStartOfData) % iSampleSize),  ::ex1::seek_begin);
   //   m_readframe.seek_begin();

   }

   bool decoder::DecoderGetAttribute(audio_decode::EAttribute eattribute, string & str)
   {
      UNREFERENCED_PARAMETER(eattribute);
      UNREFERENCED_PARAMETER(str);
      return false;
   }

   __int64 decoder::DecoderGetSampleCount()
   {
      return m_nSampleCount;
   }

   bool decoder::DecoderSetNonStopOnEofMode(bool bSet)
   {
      m_bNonStopOnEof = bSet;
      return m_bNonStopOnEof;
   }

   gen::memory_file & decoder::GetMemoryFile()
   {
      return m_memfile;
   }


} // namespace _vmsmpegdec
