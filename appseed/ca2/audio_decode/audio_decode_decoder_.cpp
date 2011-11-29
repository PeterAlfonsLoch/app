#include "StdAfx.h"


namespace audio_decode
{


   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {

      m_dwDecodeLength                       = (DWORD_PTR) -1;
      m_spmemory(new primitive::memory(NULL, 16 * 1024 * 1024, 0));
      m_spmemory->set_app(papp);
      m_spmemoryfileIn(new gen::memory_file(papp, m_spmemory));
      m_spmemoryfileOut(new gen::memory_file(papp, m_spmemory));
      m_spmemoryfileIn->m_bSynch             = true;
      m_spmemoryfileOut->m_bSynch            = true;

      ::ca::thread_sp::m_p->m_bAutoDelete    = false;
      ::ca::thread_sp::m_p->m_ulFlags        &= ~ca::flag_auto_clean;
      m_bAutoDelete                          = false;
      m_ulFlags                              &= ~ca::flag_auto_clean;

      m_bInitialized                         = false;

      m_iReadBlockSize                       = -1;

   }

   decoder::~decoder()
   {
   }

   void decoder::DecoderFinalize()
   {
      DecoderStop();
   }

   void decoder::DecoderStop()
   {
   }

   bool decoder::DecoderGetAttribute(EAttribute eattribute, string & str)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(eattribute);
      return false;
   }

   __int64 decoder::DecoderGetMillisLength()
   {
      UINT uiRate = DecoderGetSamplesPerSecond();
      if(uiRate != 0)
         return DecoderGetSampleCount() * 1000 / uiRate;
      else
         return 0;
   }

   bool decoder::DecoderSetSeekable(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return true;
   }

   bool decoder::DecoderGetSeekable()
   {
      return true;
   }

   int decoder::DecoderSetReadBlockSize(int iSize)
   {

      m_iReadBlockSize = iSize;

      return m_iReadBlockSize;

   }

   void decoder::DecoderSeekEnd()
   {
   }

   bool decoder::DecoderSetNonStopOnEofMode(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return false;
   }

   bool decoder::DecoderEOF()
   {
      if(m_dwDecodeLength == ((DWORD_PTR) -1))
         return false;
      else
         return m_spmemoryfileOut->get_position() >= m_dwDecodeLength;
   }

   ::primitive::memory_size decoder::DecoderFillBuffer(LPVOID lpvoidBuffer, ::primitive::memory_size uiBufferSize)
   {
      synch_lock lock(this);
      ::primitive::memory_size iRead = 0;
      if(!m_bInitialized)
         iRead = 0;
      else
         iRead = m_spmemoryfileOut->read(lpvoidBuffer, uiBufferSize);
      m_iRead += iRead;
      if(iRead < uiBufferSize)
      {
         if(DecoderEOF())
         {
            m_iReadExpanded += iRead;
            return iRead;
         }
         else
         {
            for(int i = iRead / 2; i < uiBufferSize / 2; i++)
            {
               ((unsigned short *)lpvoidBuffer)[i] = 0x7fff;
            }
            m_iaLostPosition.add(m_iReadExpanded + iRead);
            m_iaLostCount.add((index) (uiBufferSize - iRead));
            m_iReadExpanded += uiBufferSize;
            return uiBufferSize;
         }
      }
      else
      {
         m_iReadExpanded += iRead;
      }
      return iRead;
   }

   bool decoder::DecoderInitialize(ex1::file *pfile)
   {


      m_bInitialized = false;
      m_dwDecodeLength = (DWORD_PTR) -1;


      int iCount = 11;
      while(iCount >= 0)
      {
         if(_DecoderInitialize(pfile))
            break;
         if(DecoderGetSeekable())
            return false;
         Sleep(1984);
         iCount--;
      }

      if(iCount < 0)
         return false;

      if(_DecoderEOF())
         return false;

      synch_lock lock(this);
      m_iaLostPosition.remove_all();
      m_iaLostCount.remove_all();
      m_iRead = 0;
      m_iReadExpanded = 0;
      lock.unlock();

      Begin();

      Sleep(984);

      return true;
   }

   int decoder::run()
   {
      m_bRunning = true;
      primitive::memory memory;
      // 5 seconds of primitive::memory buffering per reading

      if(DecoderGetSeekable())
      {
         memory.allocate(DecoderGetSamplesPerSecond() * DecoderGetChannelCount() * DecoderGetBitsPerSample()  / (8 * 8));
      }
      else
      {
         if(m_iReadBlockSize > 0)
         {
            memory.allocate(DecoderGetRawSize(m_iReadBlockSize));
         }
         else
         {
            memory.allocate(((__int64) m_iBufferSize * DecoderGetSamplesPerSecond() * DecoderGetBitsPerSample() * DecoderGetChannelCount()) / (__int64)(128 * 1000));
         }
      }

      // millis tutchi dummy implementation:
      // it is easy:
      // to keep the last memory and start decoding the next
      while(m_spmemoryfileIn->get_length() > memory.get_size())
      {
         m_spmemoryfileIn->remove_begin(memory, (::primitive::memory_size) min(m_spmemoryfileIn->get_length() - memory.get_size(), memory.get_size()));
      }
      m_spmemoryfileIn->seek_to_end();
      m_spmemoryfileOut->seek_to_end();
      m_dwDecodeLength = (DWORD_PTR) -1;
      m_bInitialized = false;
      m_bAutoDelete                 = false;
      m_ulFlags                    &= ~ca::flag_auto_clean;
      DecoderSeekBegin();
      int i = 0;
      try
      {
         while(!_DecoderEOF() &&  m_bRun)
         {
            bool bAppRun = Application.m_bRun;
            if(!bAppRun)
               break;
            bool bSysRun = System.m_bRun;
            if(!bSysRun)
               break;
            try
            {
               ::primitive::memory_size uiRead = _DecoderFillBuffer(memory, memory.get_size());
               m_spmemoryfileIn->write(memory, uiRead);
            }
            catch(...)
            {
               break;
            }
            if(!m_bInitialized)
               m_bInitialized = true;
            i++;
            if(i % 2 == 1)
            {
   //            Sleep(1984);
            }
         }
      }
      catch(...)
      {
      }
      m_dwDecodeLength = m_spmemory->get_size();
      m_bRunning = false;
      _DecoderFinalize();
      return 0;
   }

   imedia::time decoder::DecoderGetLostMillis(imedia::time dwExpandedMillis)
   {
      synch_lock lock(this);
      imedia::position position;
      position = ((__int64) dwExpandedMillis * DecoderGetSamplesPerSecond() * DecoderGetChannelCount()  * DecoderGetBitsPerSample()) / ((__int64) 8 * 1000);
      return ((__int64) DecoderGetLostPositionOffset(position) * 8 * 1000) / ((__int64) DecoderGetSamplesPerSecond() * DecoderGetChannelCount()  * DecoderGetBitsPerSample());
   }

   imedia::position decoder::DecoderGetLostPositionOffset(imedia::position positionExpanded)
   {
      synch_lock lock(this);
      imedia::position position = positionExpanded;
      imedia::position iTotalLostCount = 0;
      for(int i = 0; i < m_iaLostPosition.get_size(); i++)
      {
         int64_t iLostPosition = m_iaLostPosition[i];
         int iLostCount    = m_iaLostCount[i];
         if(position > (iLostPosition + iLostCount))
         {
            iTotalLostCount += iLostCount;
         }
         else if(position >= iLostPosition)
         {
            iTotalLostCount += min(position - iLostPosition, iLostCount);
            break;
         }
         else
         {
            break;
         }
      }
      return iTotalLostCount;
   }

   void decoder::delete_this()
   {
      if(m_pplugin != NULL)
      {
         m_pplugin->DeleteDecoder(this);
      }
   }

   bool decoder::DecoderSetExpectedParams(UINT uiSamplesPerSec, UINT uiChannelCount, UINT uiBitCount, UINT uiEncodedAvgBitRate)
   {
      return false;
   }

   UINT decoder::DecoderGetAverageBitRate()
   {
      return DecoderGetRawBitRate(); // pre calculates a default optimistic worst case
   }

   UINT decoder::DecoderGetRawBitRate()
   {
      return DecoderGetSamplesPerSecond() * DecoderGetBitsPerSample();
   }

   UINT decoder::DecoderGetRawSize(UINT uiEncodeSize)
   {
      return (uint64_t) uiEncodeSize * (uint64_t) DecoderGetRawBitRate() /  (uint64_t) DecoderGetAverageBitRate();
   }


} // namespace auddev


