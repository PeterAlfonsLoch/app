#include "StdAfx.h"
#include "iaudio/WaveStreamEffect.h"

#include "WaveEffectDevocalizer.h"

audWaveOut::audWaveOut(::ca::application * papp) :
   ca(papp),
   thread(papp)
{
   m_pwavebuffer = new audWaveBuffer(papp);
   if(m_pwavebuffer == NULL)
      throw new memory_exception;
   m_estate             = state_initial;
   m_pthreadCallback    = NULL;
   m_hwaveout           = NULL;
   m_iBufferInMMSys     = 0;
   m_mmr                = MMSYSERR_NOERROR;
   m_peffect            = NULL;
   m_dwLostSampleCount  = 0;
}

audWaveOut::~audWaveOut()
{

}

void audWaveOut::install_message_handling(::user::win::message::dispatch * pinterface)
{
   IGUI_WIN_MSG_LINK(MM_WOM_OPEN, pinterface, this, &audWaveOut::OnMultimediaOpen);
   IGUI_WIN_MSG_LINK(MM_WOM_DONE, pinterface, this, &audWaveOut::OnMultimediaDone);
   IGUI_WIN_MSG_LINK(MM_WOM_CLOSE, pinterface, this, &audWaveOut::OnMultimediaClose);
   IGUI_WIN_MSG_LINK(MessageBufferReady, pinterface, this, &audWaveOut::OnBufferReady);
   IGUI_WIN_MSG_LINK(MessageClose, pinterface, this, &audWaveOut::OnClose);
}


bool audWaveOut::initialize_instance()
{
   m_pprebuffer = (audWavePreBuffer *) new audWavePreBuffer(get_app());
   return true;
}

int audWaveOut::exit_instance()
{
   if(GetState() == StatePlaying)
   {
      Stop();
      m_eventStopped.wait(seconds(60));
   }
   if(GetSafeHandle() != NULL)
   {
      close();
   }
   for(int i = 0; i < m_evptraEnd.get_size(); i++)
   {
      m_evptraEnd[i]->SetEvent();
   }

   if(m_pwavebuffer != NULL)
   {
      delete m_pwavebuffer;
      m_pwavebuffer = NULL;
   }


   return thread::exit_instance();
}

MMRESULT audWaveOut::open(
   thread * pthreadCallback,
   int iBufferCount,
   int iBufferSampleCount)
{
   single_lock sLock(&m_csHandle, TRUE);
   if(m_hwaveout != NULL &&
      m_estate != state_initial)
      return MMSYSERR_NOERROR;
   m_pthreadCallback = pthreadCallback;
   MMRESULT mmr;
   ASSERT(m_hwaveout == NULL);
   ASSERT(m_estate == state_initial);

   m_waveformatex.wFormatTag = WAVE_FORMAT_PCM;
   m_waveformatex.nChannels = 2;
   m_waveformatex.nSamplesPerSec = 44100;
   m_waveformatex.wBitsPerSample = sizeof(WAVEBUFFERDATA) * 8;
   m_waveformatex.nBlockAlign = m_waveformatex.wBitsPerSample * m_waveformatex.nChannels / 8;
   m_waveformatex.nAvgBytesPerSec = m_waveformatex.nSamplesPerSec * m_waveformatex.nBlockAlign;
   m_waveformatex.cbSize = 0;
   audWaveCentral & wc = dynamic_cast < audWaveCentralContainer * > (get_app())->GetAudioWaveCentral();

   if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
      &m_hwaveout,
      wc.m_uiWaveInDevice,
      &m_waveformatex,
      get_os_int(),
      (DWORD) NULL,
      CALLBACK_THREAD)))
      goto Opened;
   m_waveformatex.nSamplesPerSec = 22050;
   m_waveformatex.nAvgBytesPerSec = m_waveformatex.nSamplesPerSec * m_waveformatex.nBlockAlign;
   if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
      &m_hwaveout,
      WAVE_MAPPER,
      &m_waveformatex,
      (DWORD) get_os_int(),
      (DWORD) NULL,
      CALLBACK_THREAD)))
      goto Opened;
   m_waveformatex.nSamplesPerSec = 11025;
   m_waveformatex.nAvgBytesPerSec = m_waveformatex.nSamplesPerSec * m_waveformatex.nBlockAlign;
   if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
      &m_hwaveout,
      WAVE_MAPPER,
      &m_waveformatex,
      (DWORD) get_os_int(),
      (DWORD) NULL,
      CALLBACK_THREAD)))
      goto Opened;

   if(mmr !=MMSYSERR_NOERROR)
   {
      if(mmr == MMSYSERR_ALLOCATED)
      {
         TRACE("Specified resource is already allocated.");
      }
      else if(mmr == MMSYSERR_BADDEVICEID)
      {
         TRACE("Specified device identifier is out of range.");
      }
      else if(mmr == WAVERR_BADFORMAT)
      {
         TRACE("Attempted to open with an unsupported waveform-audio format.");
      }
      TRACE("ERROR OPENING WAVE INPUT DEVICE");
      return mmr;
   }

Opened:
   unsigned int uiBufferSizeLog2;
   unsigned int uiBufferSize;
   unsigned int uiAnalysisSize;
   unsigned int uiAllocationSize;
   unsigned int uiInterestSize;
   unsigned int uiSkippedSamplesCount;
   UINT uiBufferCount = iBufferCount;

   if(m_waveformatex.nSamplesPerSec == 44100)
   {
      uiBufferSizeLog2 = 16;
      uiBufferSize = m_waveformatex.nChannels * 2 * iBufferSampleCount; // 512 kbytes
      uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
      if(iBufferCount > 0)
      {
         uiAllocationSize = iBufferCount * uiAnalysisSize;
      }
      else
      {
         uiAllocationSize = 8 * uiAnalysisSize;
      }
      uiInterestSize = 200;
      uiSkippedSamplesCount = 2;
   }
   else if(m_waveformatex.nSamplesPerSec == 22050)
   {
      uiBufferSizeLog2 = 10;
      uiBufferSize = 4 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 200;
      uiSkippedSamplesCount = 1;
   }
   else if(m_waveformatex.nSamplesPerSec == 11025)
   {
      uiBufferSizeLog2 = 10;
      uiBufferSize = 2 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 200;
      uiSkippedSamplesCount = 1;
   }
   GetBuffer().PCMOutOpen(
      uiBufferSize,
      uiBufferCount,
      &m_waveformatex,
      &m_waveformatex);

   m_pprebuffer->open(
      this, // callback thread (thread)
      m_waveformatex.nChannels, // channel count
      uiBufferCount, // group count
      iBufferSampleCount); // group sample count

   int i, iSize;
   iSize = GetBuffer().GetBufferCount();
   for(i = 0; i < iSize; i++)
   {
      if(MMSYSERR_NOERROR != (mmr =  waveOutPrepareHeader(
         m_hwaveout,
         GetBuffer().GetHdr(i),
         sizeof(WAVEHDR))))
      {
         TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
         return mmr;
      }
   }
   m_estate = StateOpened;
   return MMSYSERR_NOERROR;
}

MMRESULT audWaveOut::OpenEx(
   thread * pthreadCallback,
   int iBufferCount,
   int iBufferSampleCount,
   UINT uiSamplesPerSec,
   UINT uiChannelCount,
   UINT uiBitsPerSample)
{
   single_lock sLock(&m_csHandle, TRUE);
   if(m_hwaveout != NULL &&
       m_estate != state_initial)
      return MMSYSERR_NOERROR;
   m_pthreadCallback = pthreadCallback;
   MMRESULT mmr;
   ASSERT(m_hwaveout == NULL);
   ASSERT(m_estate == state_initial);

   m_waveformatex.wFormatTag        = WAVE_FORMAT_PCM;
   m_waveformatex.nChannels         = (WORD) uiChannelCount;
   m_waveformatex.nSamplesPerSec    = uiSamplesPerSec;
   m_waveformatex.wBitsPerSample    = (WORD) uiBitsPerSample;
   m_waveformatex.nBlockAlign       = m_waveformatex.wBitsPerSample * m_waveformatex.nChannels / 8;
   m_waveformatex.nAvgBytesPerSec   = m_waveformatex.nSamplesPerSec * m_waveformatex.nBlockAlign;
   m_waveformatex.cbSize            = 0;

   audWaveCentral & wc = dynamic_cast < audWaveCentralContainer * > (get_app())->GetAudioWaveCentral();

   try
   {
      if(MMSYSERR_NOERROR == (mmr = waveOutOpen(
         &m_hwaveout,
         wc.m_uiWaveInDevice,
         &m_waveformatex,
         get_os_int(),
         (DWORD) NULL,
         CALLBACK_THREAD)))
         goto Opened;
   }
   catch(const ::ca::exception &)
   {
      return MMSYSERR_ERROR;
   }
   catch(...)
   {
      return MMSYSERR_ERROR;
   }

   if(mmr != MMSYSERR_NOERROR)
   {
      if(mmr == MMSYSERR_ALLOCATED)
      {
         TRACE("Specified resource is already allocated.");
      }
      else if(mmr == MMSYSERR_BADDEVICEID)
      {
         TRACE("Specified device identifier is out of range.");
      }
      else if(mmr == WAVERR_BADFORMAT)
      {
         TRACE("Attempted to open with an unsupported waveform-audio format.");
      }
      TRACE("ERROR OPENING WAVE INPUT DEVICE");
      return mmr;
   }

Opened:
   unsigned int uiBufferSizeLog2;
   unsigned int uiBufferSize;
   unsigned int uiAnalysisSize;
   unsigned int uiAllocationSize;
   unsigned int uiInterestSize;
   unsigned int uiSkippedSamplesCount;
   UINT uiBufferCount = iBufferCount;

//   if(m_waveformatex.nSamplesPerSec == 44100)
   if(true)
   {
      uiBufferSizeLog2 = 16;
      uiBufferSize = m_waveformatex.nChannels * 2 * iBufferSampleCount; // 512 kbytes
      uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
      if(iBufferCount > 0)
      {
         uiAllocationSize = iBufferCount * uiAnalysisSize;
      }
      else
      {
         uiAllocationSize = 8 * uiAnalysisSize;
      }
      uiInterestSize = 200;
      uiSkippedSamplesCount = 2;
   }
   else if(m_waveformatex.nSamplesPerSec == 22050)
   {
      uiBufferSizeLog2 = 10;
      uiBufferSize = 4 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 200;
      uiSkippedSamplesCount = 1;
   }
   else if(m_waveformatex.nSamplesPerSec == 11025)
   {
      uiBufferSizeLog2 = 10;
      uiBufferSize = 2 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 2 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 200;
      uiSkippedSamplesCount = 1;
   }
   GetBuffer().PCMOutOpen(
      uiBufferSize,
      uiBufferCount,
      &m_waveformatex,
      &m_waveformatex);

   m_pprebuffer->open(
      this, // callback thread (thread)
      m_waveformatex.nChannels, // channel count
      uiBufferCount, // group count
      iBufferSampleCount); // group sample count

   int i, iSize;
   iSize = GetBuffer().GetBufferCount();
   for(i = 0; i < iSize; i++)
   {
      if(MMSYSERR_NOERROR != (mmr =  waveOutPrepareHeader(
         m_hwaveout,
         GetBuffer().GetHdr(i),
         sizeof(WAVEHDR))))
      {
         TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
         return mmr;
      }
   }
   m_pprebuffer->SetMinL1BufferCount(GetBuffer().GetBufferCount() + 4);
   m_estate = StateOpened;
   return MMSYSERR_NOERROR;
}

MMRESULT audWaveOut::Start(const imedia::position & position)
{
   single_lock sLock(&m_csHandle, TRUE);
   if(m_estate == StatePlaying)
      return MMSYSERR_NOERROR;
   ASSERT(m_estate == StateOpened || m_estate == StateStopped);
   m_estate = StatePlaying;
   m_pprebuffer->Reset();
   m_pprebuffer->Start(position);
   for(DWORD_PTR dw = 0; dw < GetBuffer().GetBufferCount(); dw++)
   {
      _Free(&GetBuffer().GetBuffer(dw).m_wavehdr);
   }
   return MMSYSERR_NOERROR;
}


MMRESULT audWaveOut::close()
{
   single_lock sLock(&m_csHandle, TRUE);
   if(m_estate == StatePlaying)
   {
      Stop();
   }
   MMRESULT mmr;
   if(m_estate != StateOpened)
      return MMSYSERR_NOERROR;

   int i, iSize;
   iSize = GetBuffer().GetBufferCount();
   for(i = 0; i < iSize; i++)
   {
      if(MMSYSERR_NOERROR != (mmr = waveOutUnprepareHeader(
         m_hwaveout,
         GetBuffer().GetHdr(i),
         sizeof(WAVEHDR))))
      {
         TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer =%d", mmr);
      }
   }

   mmr = waveOutClose(m_hwaveout);
   m_hwaveout = NULL;
   m_pprebuffer->Reset();
   m_estate = state_initial;
   return MMSYSERR_NOERROR;

}


void audWaveOut::OnMultimediaOpen(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}


void audWaveOut::OnMultimediaDone(gen::signal_object * pobj)
{
   SCAST_PTR(::user::win::message::base, pbase, pobj);
   m_iBufferInMMSys--;
   LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam;
   OutBufferDone(lpwavehdr);
}

void audWaveOut::OnMultimediaClose(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void audWaveOut::OnBufferReady(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void audWaveOut::BufferReady(LPWAVEHDR lpwavehdr)
{

   if(GetState() != StatePlaying)
   {
      TRACE("ERROR audWaveOut::BufferReady while GetState() != StatePlaying");
      return;
   }

   MMRESULT mmr;

   if(m_peffect != NULL)
   {
      m_peffect->Process16bits(
         (short *) lpwavehdr->lpData,
         lpwavehdr->dwBytesRecorded / 2);
   }

   single_lock sLock(&m_csHandle, TRUE);
   mmr = waveOutWrite(
         m_hwaveout,
         lpwavehdr,
         sizeof(WAVEHDR));
   VERIFY(MMSYSERR_NOERROR == mmr);
   if(mmr == MMSYSERR_NOERROR)
   {
      m_iBufferInMMSys++;
   }

}

bool audWaveOut::Stop()
{

   single_lock sLock(&m_csHandle, TRUE);

   if(m_estate != StatePlaying && m_estate != StatePaused)
      return false;

   m_eventStopped.ResetEvent();

   m_pprebuffer->Stop();

   m_estate = StateStopping;

   // waveOutReset
   // The waveOutReset function stops playback on the given
   // waveform-audio output device and resets the current position
   // to zero. All pending playback buffers are marked as done and
   // returned to the application.
   m_mmr = waveOutReset(m_hwaveout);



   if(m_mmr == MMSYSERR_NOERROR)
   {
      m_estate = StateOpened;
   }

   return m_mmr == MMSYSERR_NOERROR;

}

bool audWaveOut::Pause()
{
   single_lock sLock(&m_csHandle, TRUE);
   ASSERT(m_estate == StatePlaying);

   if(m_estate != StatePlaying)
      return false;



   // waveOutReset
   // The waveOutReset function stops playback on the given
   // waveform-audio output device and resets the current position
   // to zero. All pending playback buffers are marked as done and
   // returned to the application.
   m_mmr = waveOutPause(m_hwaveout);

   ASSERT(m_mmr == MMSYSERR_NOERROR);

   if(m_mmr == MMSYSERR_NOERROR)
   {
      m_estate = StatePaused;
   }

   return m_mmr == MMSYSERR_NOERROR;
}

bool audWaveOut::Restart()
{
   single_lock sLock(&m_csHandle, TRUE);
   ASSERT(m_estate == StatePaused);

   if(m_estate != StatePaused)
      return false;




   // waveOutReset
   // The waveOutReset function stops playback on the given
   // waveform-audio output device and resets the current position
   // to zero. All pending playback buffers are marked as done and
   // returned to the application.
   m_mmr = waveOutRestart(m_hwaveout);

   ASSERT(m_mmr == MMSYSERR_NOERROR);

   if(m_mmr == MMSYSERR_NOERROR)
   {
      m_estate = StatePlaying;
   }

   return m_mmr == MMSYSERR_NOERROR;
}


void audWaveOut::AttachEndEvent(event *pevent)
{
m_evptraEnd.add(pevent);
}

imedia::time audWaveOut::GetPositionMillisForSynch()
{
   int64_t dwMillis = GetPositionMillis();
   __int64 dwPosition = m_pprebuffer->m_position * 8;
   dwPosition /= m_waveformatex.wBitsPerSample;
   dwPosition *= 1000;
   dwPosition /= m_waveformatex.nChannels * m_waveformatex.nSamplesPerSec;
   if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
      return dwMillis + dwPosition - m_pprebuffer->m_pdecoder->DecoderGetLostMillis(dwMillis + dwPosition) - (((__int64) m_dwLostSampleCount) /  ((__int64) m_waveformatex.nSamplesPerSec));
   else
      return dwMillis + dwPosition - ((m_dwLostSampleCount) * 1000 / m_waveformatex.nSamplesPerSec);
}

imedia::time audWaveOut::GetPositionMillis()
{
   single_lock sLock(&m_csHandle, TRUE);
   MMRESULT                mmr;
   MMTIME                  mmt;

   mmt.wType = TIME_MS;

   if(m_hwaveout != NULL)
   {
      mmr = waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt));
      try
      {
         if (MMSYSERR_NOERROR != mmr)
         {
            TRACE( "waveOutGetPosition() returned %lu", (DWORD)mmr);
      //      return MCIERR_DEVICE_NOT_READY;
             return 0;
         }
      }
      catch(...)
      {
         //return MCIERR_DEVICE_NOT_READY;
         return 0;
      }
      if(mmt.wType == TIME_BYTES)
      {
         __int64 i = mmt.u.cb;
         i *= 8 * 1000;
         i /= m_waveformatex.wBitsPerSample * m_waveformatex.nChannels * m_waveformatex.nSamplesPerSec;
         return (DWORD) i;

      }
      else
      {
         //*pTicks += mmt.u.ticks;
         return mmt.u.ms;
      }
   }
   else
      return 0;

}

imedia::position audWaveOut::get_position_for_synch()
{
   imedia::position position = get_position();
   if(m_pprebuffer != NULL && m_pprebuffer->m_pdecoder != NULL)
      return m_pprebuffer->m_position + position - m_pprebuffer->m_pdecoder->DecoderGetLostPositionOffset(position) - m_dwLostSampleCount * m_waveformatex.wBitsPerSample * m_waveformatex.nChannels / 8;
   else
      return m_pprebuffer->m_position + position - m_dwLostSampleCount * m_waveformatex.wBitsPerSample * m_waveformatex.nChannels / 8;
}

imedia::position audWaveOut::get_position()
{
   single_lock sLock(&m_csHandle, TRUE);
   MMRESULT                mmr;
   MMTIME                  mmt;

   mmt.wType = TIME_BYTES;

   if(m_hwaveout != NULL)
   {
      mmr = waveOutGetPosition(m_hwaveout, &mmt, sizeof(mmt));
      try
      {
         if (MMSYSERR_NOERROR != mmr)
         {
            TRACE( "waveOutGetPosition() returned %lu", (DWORD)mmr);
            return 0;
         }
      }
      catch(...)
      {
         return 0;
      }
      if(mmt.wType == TIME_MS)
      {
         imedia::position position = mmt.u.ms;
         position *= m_waveformatex.wBitsPerSample * m_waveformatex.nChannels * m_waveformatex.nSamplesPerSec;
         position /= 8 * 1000;
         return position;
      }
      else
      {
         return mmt.u.cb;
      }
   }
   else
      return 0;

}

int audWaveOut::GetBufferInMMSystemCount()
{
   return m_iBufferInMMSys;
}

void audWaveOut::OnClose(gen::signal_object * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   VERIFY(close() == MMSYSERR_NOERROR);
}

void audWaveOut::PostClose()
{
   PostThreadMessage(MessageClose, 0, 0);
}

void * audWaveOut::GetBuffer(int iBuffer)
{
   return GetBuffer().PCMOutGetBuffer(iBuffer);
}

int audWaveOut::GetBufferSize()
{
   return GetBuffer().PCMOutGetInBufferSize();
}

MMRESULT audWaveOut::GetLastMMResult()
{
   return m_mmr;
}

void audWaveOut::SetWaveStreamEffect(iaudio::WaveStreamEffect * peffect)
{
   m_peffect = peffect;
}

audWaveOut * audWaveOut::BeginThread(::ca::application * papp)
{
   audWaveOut * pwaveout = new audWaveOut(papp);
   pwaveout->Begin(THREAD_PRIORITY_HIGHEST);
   return pwaveout;
}

int audWaveOut::GetBufferInMMSysCount()
{
   return m_iBufferInMMSys;
}

audio_decode::decoder * audWaveOut::SetDecoder(audio_decode::decoder * pdecoder)
{
   m_pprebuffer->SetDecoder(pdecoder);
   return pdecoder;
}

void audWaveOut::OutBufferDone(LPWAVEHDR lpwavehdr)
{

   single_lock sl(&m_csOut, TRUE);
   if(m_pprebuffer->IsEOF() || GetState() == StateStopping)
   {
      if(GetBufferInMMSystemCount() <= 0)
      {
         OnPlaybackEnd();
      }
   }
   else
   {
      _Free(lpwavehdr);
   }

}


void audWaveOut::OnPreBufferDone(int iId)
{
   UNREFERENCED_PARAMETER(iId);
   single_lock sl(&m_csPreBuffer, TRUE);
}


void audWaveOut::_Free(LPWAVEHDR lpwavehdr)
{
   m_lphdraFree.add(lpwavehdr);
   if(!m_pprebuffer->IdFree(lpwavehdr->dwUser))
      return;

   memcpy(
      lpwavehdr->lpData,
      m_pprebuffer->GetOutBufferId(lpwavehdr->dwUser),
      m_pprebuffer->GetChunkByteCount());

   BufferReady(lpwavehdr);
}

void audWaveOut::OnPlaybackEnd()
{
   Stop();

   if(m_pprebuffer->m_pstreameffectOut != NULL)
   {
      iaudio::WaveStreamEffect * peffect = m_pprebuffer->m_pstreameffectOut;
      m_pprebuffer->m_pstreameffectOut = NULL;
      delete peffect;
   }

   m_eventStopped.SetEvent();

   m_pplayer->OnEvent(audWavePlayer::EventPlaybackEnd);

}



HWAVEOUT audWaveOut::GetSafeHandle()
{
   return m_hwaveout;
}

audWaveBuffer & audWaveOut::GetBuffer()
{
   return *m_pwavebuffer;
}

audWaveOut::e_state audWaveOut::GetState()
{
   return m_estate;
}
