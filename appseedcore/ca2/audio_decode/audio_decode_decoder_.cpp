#include "StdAfx.h"

namespace audio_decode
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      thread(papp)
   {
      m_dwDecodeLength              = (DWORD_PTR) -1;
      m_pmemory                     = new primitive::memory;
      m_pmemory->set_app(papp);
      m_pmemoryfileIn               = new gen::memory_file(papp, *m_pmemory);
      m_pmemoryfileOut              = new gen::memory_file(papp, *m_pmemory);
      m_pmemoryfileIn->m_bSynch     = true;
      m_pmemoryfileOut->m_bSynch    = true;
      ::ca::thread_sp::m_p->m_bAutoDelete    = false;
      ::ca::thread_sp::m_p->m_ulFlags        &= ~ca::flag_auto_clean;
      m_bInitialized                = false;
   }

   decoder::~decoder()
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
      UNREFERENCED_PARAMETER(iSize);
      return -1;
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
         return m_pmemoryfileOut->GetPosition() >= m_dwDecodeLength;
   }

   int decoder::DecoderFillBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      ::ca::lock lock(this);
      int iRead = 0;
      if(!m_bInitialized)
         iRead = 0;
      else
         iRead = m_pmemoryfileOut->read(lpvoidBuffer, uiBufferSize);
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
            memset(&((byte *)lpvoidBuffer)[iRead], 0, uiBufferSize - iRead);
            m_iaLostPosition.add(m_iReadExpanded + iRead);
            m_iaLostCount.add(uiBufferSize - iRead);
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

      ::ca::lock lock(this);
      m_iaLostPosition.remove_all();
      m_iaLostCount.remove_all();
      m_iRead = 0;
      m_iReadExpanded = 0;
      lock.Unlock();

      Begin();

      Sleep(984);

      return true;
   }

   int decoder::run()
   {
      primitive::memory memory;
      // 5 seconds of primitive::memory buffering per reading
      memory.allocate(DecoderGetSamplesPerSecond() * DecoderGetChannelCount() * DecoderGetBitsPerSample() * 5 / 8);

      // millis tutchi dummy implementation:
      // it is easy:
      // to keep the last memory and start decoding the next
      while(m_pmemoryfileIn->get_length() > memory.get_size())
      {
         m_pmemoryfileIn->RemoveBegin(memory, min(m_pmemoryfileIn->get_length() - memory.get_size(), memory.get_size()));
      }
      m_pmemoryfileIn->seek_to_end();
      m_pmemoryfileOut->seek_to_end();
      m_dwDecodeLength = (DWORD_PTR) -1;
      m_bInitialized = false;
      m_bAutoDelete                 = false;
      m_ulFlags                    &= ~ca::flag_auto_clean;
      DecoderSeekBegin();
      int i = 0;
      while(!_DecoderEOF())
      {
         try
         {
            int iRead = _DecoderFillBuffer(memory, memory.get_size());
            m_pmemoryfileIn->write(memory, iRead);
         }
         catch(...)
         {
         }
         if(!m_bInitialized)
            m_bInitialized = true;
         i++;
         if(i % 2 == 1)
         {
//            Sleep(1984);
         }
      }
      m_dwDecodeLength = m_pmemory->get_size();
      return 0;
   }

   DWORD decoder::DecoderGetLostMillis(DWORD dwExpandedMillis)
   {
      ::ca::lock lock(this);
      imedia::position position;
      position.m_i = ((__int64) dwExpandedMillis * DecoderGetSamplesPerSecond() * DecoderGetChannelCount()  * DecoderGetBitsPerSample()) / ((__int64) 8 * 1000);
      return ((__int64) DecoderGetLostPositionOffset(position) * 8 * 1000) / ((__int64) DecoderGetSamplesPerSecond() * DecoderGetChannelCount()  * DecoderGetBitsPerSample());
   }

   imedia::position decoder::DecoderGetLostPositionOffset(imedia::position positionExpanded)
   {
      ::ca::lock lock(this);
      imedia::position position = positionExpanded;
      imedia::position iTotalLostCount = 0;
      for(int i = 0; i < m_iaLostPosition.get_size(); i++)
      {
         int iLostPosition = m_iaLostPosition[i];
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



} // namespace auddev