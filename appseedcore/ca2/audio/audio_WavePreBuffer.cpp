#include "StdAfx.h"
#include "WaveEffectDevocalizer.h"

audWavePreBuffer::audWavePreBuffer(::ca::application * papp) :
   ca(papp),
   m_thread(papp)
{
   m_thread.SetPreBuffer(this);
   m_iChunkCount        = 0;
   m_iChunkSampleCount  = 0;
   m_pstreameffectOut   = NULL;
   m_iOutCount          = 0;
   m_iMinFreeBuffer     = 0;
   m_pdecoder           = NULL;
   m_position           = 0;
}

audWavePreBuffer::~audWavePreBuffer()
{

}


bool audWavePreBuffer::open(audWavePreBufferCallback * pcallback, int iChannelCount, int iChunkCount, int iChunkSampleCount)
{
   if(!_UpdateBuffer(iChannelCount, iChunkCount, iChunkSampleCount, m_iMinFreeBuffer))
   {
      return false;
   }

   m_iChannelCount = iChannelCount;
   m_iChunkCount = iChunkCount;
   m_iChunkSampleCount = iChunkSampleCount;
   m_pcallback = pcallback;

   // no m_speffect by default, removed devocalizer during memory usage optimization 16:35 2011-04-05
   //m_spdevocalizer.destroy();
   //m_spdevocalizer(new audWaveEffectDevocalizer(get_app(), false, iChunkSampleCount, 44100, 2, 2));
   return true;
}

bool audWavePreBuffer::SetMinL1BufferCount(int iMinL1BufferCount)
{
   if(!_UpdateBuffer(m_iChannelCount, m_iChunkCount, m_iChunkSampleCount, iMinL1BufferCount))
   {
      return false;
   }

   m_iMinFreeBuffer = iMinL1BufferCount;
   return true;
}

void audWavePreBuffer::SetDecoder(audio_decode::decoder * pinterface)
{
   pha(audio_decode::decoder)::add(pinterface);
   m_pdecoder = pinterface;
}


short * audWavePreBuffer::GetInBuffer(int iChunk)
{
   return m_chunkaL1[iChunk].m_psh;
}

short * audWavePreBuffer::GetOutBufferId(int iId)
{
   return &m_shaL2[_IdToChunk(iId) * m_iChunkSampleCount * m_iChannelCount];
}

int audWavePreBuffer::GetChunkByteCount()
{
   return m_iChunkSampleCount * 2 * m_iChannelCount;
}

bool audWavePreBuffer::IdFree(int iId)
{
   return _FreeId(iId);
}


bool audWavePreBuffer::_FreeId(int iId)
{
   single_lock sl(&m_cs, TRUE);

   m_iOutCount--;

   if(m_iOutCount < 0)
      m_iOutCount = 0;

   Chunk * pchunk1 = m_chunkaL1.GetChunkById(iId);
   Chunk * pchunk2 = m_chunkaL2.GetChunkById(iId);

   if(m_pdecoder->DecoderEOF())
      return false;

   ::primitive::memory_size iBytesRecorded = m_pdecoder->DecoderFillBuffer(pchunk1->m_psh, GetChunkByteCount());

   int64_t iRemain = GetChunkByteCount() - iBytesRecorded;
   if(iRemain > 0)
   {
      LPBYTE lpb = (LPBYTE) pchunk1->m_psh;
      memset(&lpb[iBytesRecorded], 0, (size_t) iRemain);
   }

   memcpy(pchunk2->m_psh, pchunk1->m_psh, GetChunkByteCount());
   /*if(m_speffect != NULL && !m_speffect->Process16bits(pchunk1->m_psh, pchunk2->m_psh))
   {
      return false;
   }*/

   if(!_PreOutputId(pchunk2))
   {
      return false;
   }

   m_iOutCount++;

   m_pcallback->OnPreBufferDone(iId);
   return true;
}

bool audWavePreBuffer::_DeferKick()
{
   return false;
   /*
   single_lock sl(&m_cs, TRUE);
   if(m_iaFree.get_size() == 0)
      return false;
   int iId = m_iaFree[0];
   if(IsEOF())
      return false;
   if(m_iLastId >= 0)
      return false;
   Chunk * pchunk1 = m_chunkaL1.GetChunkById(iId);
   Chunk * pchunk2 = m_chunkaL2.GetChunkById(iId);
   if(!m_pdecoder->DecoderEOF())
   {
      int iBytesRecorded = m_pdecoder->DecoderFillBuffer(
         pchunk1->m_psh,
         GetChunkByteCount());

      if(m_pdecoder->DecoderEOF())
      {
         m_iLastId = iId;
      }

      int iRemain = GetChunkByteCount() - iBytesRecorded;
      if(iRemain > 0)
      {
         LPBYTE lpb = (LPBYTE) pchunk1->m_psh;
         memset(&lpb[iBytesRecorded], 0, iRemain);
      }

      if(!m_pdevocalizer->Process(pchunk1->m_psh, pchunk2->m_psh))
      {
         return false;
      }

      if(!_PreOutputId(pchunk2))
      {
         return false;
      }

      m_iOutCount++;
      m_iaFree.remove_first(iId);

      m_pcallback->OnPreBufferDone(iId);
      return true;
   }
   else
   {
      return false;
   }*/
}

bool audWavePreBuffer::_PreOutputId(Chunk * pchunk)
{
   if(m_pstreameffectOut != NULL)
   {
      m_pstreameffectOut->Process16bits(pchunk->m_psh, m_iChunkSampleCount);
      if(m_pstreameffectOut->IsEndOfEffect())
      {
         if(!m_pstreameffectOut->m_bEnd)
         {
            delete m_pstreameffectOut;
            m_pstreameffectOut = NULL;
         }
      }
   }
   return true;
}


void audWavePreBuffer::_Kick()
{
   single_lock sl(&m_cs, TRUE);

   while(_DeferKick() && m_bPlay);
}

bool audWavePreBuffer::IsDevocalized()
{
   return m_speffect != NULL; // && m_speffect->IsEnabled();
}

void audWavePreBuffer::Devocalize(bool bSet)
{
   UNREFERENCED_PARAMETER(bSet);
   if(m_speffect == NULL)
      return;
   //m_speffect->Enable(bSet);
}

bool audWavePreBuffer::IsEOF()
{
   return m_pdecoder->DecoderEOF() ||
      (m_pstreameffectOut != NULL && m_pstreameffectOut->IsEndOfEffect());
}

void audWavePreBuffer::ClearBuffer()
{
//   single_lock sl(&m_cs, TRUE);

/*
   for(int iId = m_iNextId; iId < iOldNextId; iId++)
   {
      int iChunk = _IdToChunk(iId);
      m_chunkaL2[iChunk].m_iId  = -1;
   }*/
   if(m_iOutCount < 0)
      m_iOutCount = 0;
   m_thread.Step();
}





void audWavePreBuffer::Reset()
{
   single_lock sl(&m_cs, TRUE);
   m_iOutCount = 0;
   m_chunkaL1.Reset();
   m_chunkaL2.Reset();
}

audWavePreBuffer::Chunk::Chunk()
{
   m_iId = -1;
}


bool audWavePreBuffer::_UpdateBuffer(int iChannelCount, int iChunkCount, int iChunkSampleCount, int iMinL1BufferCount)
{
   int iChunk;

   int iTotalChunkCount = (iChunkCount + iMinL1BufferCount);

   m_shaL1.set_size(iTotalChunkCount * iChannelCount * iChunkSampleCount);
   m_shaL2.set_size(iTotalChunkCount * iChannelCount * iChunkSampleCount);

   m_chunkaL1.set_size(iTotalChunkCount);
   for(iChunk = 0; iChunk < iTotalChunkCount; iChunk++)
   {
      m_chunkaL1[iChunk].m_psh = &m_shaL1[iChunk * iChannelCount * iChunkSampleCount];
   }

   m_chunkaL2.set_size(iTotalChunkCount);
   for(iChunk = 0; iChunk < iTotalChunkCount; iChunk++)
   {
      m_chunkaL2[iChunk].m_psh = &m_shaL2[iChunk * iChannelCount * iChunkSampleCount];
   }

   return true;
}

int audWavePreBuffer::GetTotalChunkCount()
{
   return m_iChunkCount + m_iMinFreeBuffer;

}

int audWavePreBuffer::_IdToChunk(int iId)
{
   return iId % GetTotalChunkCount();
}

void audWavePreBuffer::ChunkArray::Reset()
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).Reset();
   }
}

void audWavePreBuffer::Chunk::Reset()
{
   m_iId = -1;
}

audWavePreBuffer::Chunk * audWavePreBuffer::ChunkArray::GetChunkById(int iId)
{
   return &this->element_at(iId % this->get_size());
}

audWavePreBuffer::Thread::Thread(::ca::application * papp) :
   ca(papp),
   thread(papp),
   simple_thread(papp)
{
   m_estate = state_initial;
}

audWavePreBuffer::Thread::~Thread()
{
   if(GetState() != state_initial)
   {
      Stop();
   }
}


int audWavePreBuffer::Thread::run()
{
   audWavePreBuffer * pprebuffer = m_pprebuffer;
   m_evStep.wait();
   m_estate = StateRunning;
   while(GetState() == StateRunning)
   {
      pprebuffer->_Kick();
      m_evStep.ResetEvent();
      m_evStep.wait(millis(100));
   }
   m_estate = state_initial;
   return 0;
}

void audWavePreBuffer::Thread::SetPreBuffer(audWavePreBuffer * pprebuffer)
{
   m_pprebuffer = pprebuffer;
}

void audWavePreBuffer::Thread::Step(void)
{
   m_evStep.SetEvent();
}

void audWavePreBuffer::Thread::Start(void)
{
   m_estate = StateStarting;
   Begin(THREAD_PRIORITY_HIGHEST);
}

void audWavePreBuffer::Thread::Stop(void)
{
   m_estate = StateStopping;
   m_evStep.SetEvent();
}

void audWavePreBuffer::Start(const imedia::position & position)
{
   m_bPlay        = true;
   m_position     = position;
   if(m_position > 0)
   {
      primitive::memory mem;
      mem.allocate(1024 * 128);
      imedia::position positionSkip = position;
      ::primitive::memory_size iBytesRecorded;
      while(positionSkip > 0)
      {
         if(positionSkip > mem.get_size())
         {
            iBytesRecorded = m_pdecoder->DecoderFillBuffer(mem.get_data(), mem.get_size());
         }
         else
         {
            iBytesRecorded = m_pdecoder->DecoderFillBuffer(mem.get_data(), (::primitive::memory_size) positionSkip);
         }
         positionSkip -= iBytesRecorded;
      }
   }
}

void audWavePreBuffer::Stop(void)
{
   m_bPlay = false;
   //m_thread.Stop();
}






__int64 audWavePreBuffer::GetMillisLength()
{
   if(m_pdecoder != NULL)
      return m_pdecoder->DecoderGetMillisLength();
   else
      return 0;
}

void audWavePreBuffer::on_delete(::ca::ca * pdecoder)
{
   UNREFERENCED_PARAMETER(pdecoder);
}
