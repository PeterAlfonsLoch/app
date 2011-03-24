#include "StdAfx.h"

audWaveIn::audWaveIn(::ca::application * papp) :
   ca(papp),
   thread(papp)
{
   m_pencoder = NULL;
   m_hWaveIn = NULL;
   m_estate = state_initial;
   m_bResetting = false;
   //m_pthreadCallback = NULL;
   m_iRefCount = 0;
   m_pwavebuffer = new audWaveBuffer(papp);
   if(m_pwavebuffer == NULL)
      throw new memory_exception;
}

audWaveIn::~audWaveIn()
{
   ASSERT(m_iRefCount == 0);
   if(m_pwavebuffer != NULL)
   {
      delete m_pwavebuffer;
   }
}

bool audWaveIn::initialize_instance()
{
   TRACE("audWaveIn::initialize_instance %X\n", get_os_int());
   SetMainWnd(NULL);
   ASSERT(GetMainWnd() == NULL);
   SetThreadPriority(THREAD_PRIORITY_HIGHEST);
   m_evInitialized.SetEvent();
   return true;
}

int audWaveIn::exit_instance()
{
   m_eventExitInstance.SetEvent();
   return thread::exit_instance();
}

void audWaveIn::pre_translate_message(gen::signal_object * pobj) 
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   ASSERT(GetMainWnd() == NULL);
   if(pbase->m_uiMessage == MM_WIM_OPEN ||
      pbase->m_uiMessage == MM_WIM_CLOSE ||
      pbase->m_uiMessage == MM_WIM_DATA)
   {
      TranslateWaveInMessage(pbase);
      if(pbase->m_bRet)
         return;
   }
   return thread::pre_translate_message(pbase);
}

MMRESULT audWaveIn::open(
   int iBufferCount,
   int iBufferSampleCount)
{
   if(m_hWaveIn != NULL && m_estate != state_initial)
   {
      InitializeEncoder();
      return MMSYSERR_NOERROR;
   }
   
   CSingleLock sLock(&m_csHandle, TRUE);
   MMRESULT mmr;
   ASSERT(m_hWaveIn == NULL);
   ASSERT(m_estate == state_initial);

   m_waveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
   m_waveFormatEx.nChannels = 2;
   m_waveFormatEx.nSamplesPerSec = 44100;
   m_waveFormatEx.wBitsPerSample = sizeof(WAVEBUFFERDATA) * 8;
   m_waveFormatEx.nBlockAlign = m_waveFormatEx.wBitsPerSample * m_waveFormatEx.nChannels / 8;
   m_waveFormatEx.nAvgBytesPerSec = m_waveFormatEx.nSamplesPerSec * m_waveFormatEx.nBlockAlign;
   m_waveFormatEx.cbSize = 0;
   audWaveCentral & wc = dynamic_cast < audWaveCentralContainer * > (get_app())->GetAudioWaveCentral();
   m_iBuffer = 0;
    
   if(MMSYSERR_NOERROR == (mmr = waveInOpen(
      &m_hWaveIn,            
      wc.m_uiWaveInDevice,            
      &m_waveFormatEx,  
      get_os_int(),
      (DWORD) NULL,
      CALLBACK_THREAD)))
      goto Opened;
   m_waveFormatEx.nSamplesPerSec = 22050;
   m_waveFormatEx.nAvgBytesPerSec = m_waveFormatEx.nSamplesPerSec * m_waveFormatEx.nBlockAlign;
   if(MMSYSERR_NOERROR == (mmr = waveInOpen(
      &m_hWaveIn,            
      WAVE_MAPPER,            
      &m_waveFormatEx,  
      (DWORD) get_os_int(),
      (DWORD) NULL,
      CALLBACK_THREAD)))
      goto Opened;
   m_waveFormatEx.nSamplesPerSec = 11025;
   m_waveFormatEx.nAvgBytesPerSec = m_waveFormatEx.nSamplesPerSec * m_waveFormatEx.nBlockAlign;
   if(MMSYSERR_NOERROR == (mmr = waveInOpen(
      &m_hWaveIn,            
      WAVE_MAPPER,            
      &m_waveFormatEx,  
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

   if(m_waveFormatEx.nSamplesPerSec == 44100)
   {
      uiBufferSizeLog2 = 16;
      uiBufferSize = m_waveFormatEx.nChannels * 2 * iBufferSampleCount; // 512 kbytes
      uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
      if(iBufferCount > 0)
      {
         uiAllocationSize = iBufferCount * uiBufferSize;
      }
      else
      {
         uiAllocationSize = 8 * uiAnalysisSize;
      }
      uiInterestSize = 200;
      uiSkippedSamplesCount = 2;
   }
   else if(m_waveFormatEx.nSamplesPerSec == 22050)
   {
      uiBufferSizeLog2 = 9;
      uiBufferSize = 4 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 600;
      uiSkippedSamplesCount = 1;
   }
   else if(m_waveFormatEx.nSamplesPerSec == 11025)
   {
      uiBufferSizeLog2 = 9;
      uiBufferSize = 2 * 1 << uiBufferSizeLog2;
      uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
      uiAllocationSize = 4 * uiAnalysisSize;
      uiInterestSize = 600;
      uiSkippedSamplesCount = 1;
   }
   GetBuffer().FFTOpen(
      uiAllocationSize,
      uiBufferSize,
      uiAnalysisSize,
      uiInterestSize,
      uiSkippedSamplesCount);
   int i, iSize;
   iSize = GetBuffer().GetBufferCount();
   for(i = 0; i < iSize; i++)
   {
      if(MMSYSERR_NOERROR != (mmr =  waveInPrepareHeader(
         m_hWaveIn,  
         &GetBuffer().get_item(i)->m_wavehdr,
         sizeof(WAVEHDR))))
      {
         TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
         return mmr;
      }
      AddBuffer(i);
   }
   if(m_pencoder != NULL && !InitializeEncoder())
   {
      m_estate = StateOpened;
      close();
      return (MMRESULT) -1;
   }
   m_estate = StateOpened;
   return MMSYSERR_NOERROR;
}

audWaveBuffer & audWaveIn::GetBuffer()
{
   return *m_pwavebuffer;
}

MMRESULT audWaveIn::close()
{
   CSingleLock sLock(&m_csHandle, TRUE);

   MMRESULT mmr;

   if(m_estate != StateOpened && m_estate != StateStopped)
      return MMSYSERR_NOERROR;

   mmr = Reset();

   int i, iSize;
   iSize = GetBuffer().GetBufferCount();
   for(i = 0; i < iSize; i++)
   {
      if(MMSYSERR_NOERROR != (mmr = waveInUnprepareHeader(
         m_hWaveIn,  
         GetBuffer().GetHdr(i),
         sizeof(WAVEHDR))))
      {
         TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
         //return mmr;
      }
   }

   mmr = waveInClose(m_hWaveIn);
   m_hWaveIn = NULL;
   m_estate = state_initial;
   return MMSYSERR_NOERROR;

}

MMRESULT audWaveIn::Start()
{
   CSingleLock sLock(&m_csHandle, TRUE);
   if(m_estate == StateRecording)
      return MMSYSERR_NOERROR;
   //ASSERT(m_estate == StateOpened || m_estate == StateStopped);
   if(m_estate != StateOpened &&
      m_estate != StateStopped)
      return MMSYSERR_NOERROR;
   MMRESULT mmr;
     if(MMSYSERR_NOERROR != (mmr = waveInStart(
      m_hWaveIn)))
   {
      TRACE("ERROR starting INPUT DEVICE ");
      return mmr;
   }
   m_estate = StateRecording;
   return MMSYSERR_NOERROR;

}

MMRESULT audWaveIn::Stop()
{
   CSingleLock sLock(&m_csHandle, TRUE);
   ASSERT(m_estate == StateRecording);
   MMRESULT mmr;
   m_estate = state_stopping;
   try
   {
        if(MMSYSERR_NOERROR != (mmr = waveInStop(
         m_hWaveIn)))
      {
         TRACE("audWaveIn::Stop : ERROR OPENING stopping INPUT DEVICE ");
      }
   }
   catch(...)
   {
      TRACE("audWaveIn::Stop : Exception OPENING stopping INPUT DEVICE ");
   }
   m_estate = StateStopped;
   m_eventStopped.SetEvent();
   return MMSYSERR_NOERROR;
}

void CALLBACK audWaveIn::WaveInProc(
   HWAVEIN  hwi,       
   UINT     uMsg,         
   DWORD    dwInstance,  
   DWORD    dwParam1,    
   DWORD    dwParam2)
{
   UNREFERENCED_PARAMETER(hwi);
   UNREFERENCED_PARAMETER(dwInstance);
   UNREFERENCED_PARAMETER(dwParam1);
   UNREFERENCED_PARAMETER(dwParam2);
   if(uMsg == WIM_DATA)
   {
      ASSERT(FALSE);
/*      DWORD msSampleTime = timeGetTime();
      thread * pthread = (thread *) dwInstance;
      ASSERT(pthread != NULL);
      LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
      LPWAVEPROCDATAMESSAGE lpxfwm = new WAVEPROCDATAMESSAGE;
      lpxfwm->bDelete = TRUE;
      lpxfwm->msSampleTime = msSampleTime;
//      lpxfwm->tkSamplePosition = tkPosition;
      lpxfwm->lpWaveHdr = lpWaveHdr;
      pthread->PostThreadMessage(
         WM_USER,
         (WPARAM) WAVM_WAVE_PROC_DATA,
         (LPARAM) lpxfwm);
//      i++;
//      if( i > 2)
//         i = 0;*/
   }
}


LPWAVEFORMATEX audWaveIn::GetFormatEx()
{
   return &m_waveFormatEx;
}

UINT audWaveIn::GetState()
{
   return m_estate;
}

MMRESULT audWaveIn::Reset()
{
   CSingleLock sLock(&m_csHandle, TRUE);
   m_bResetting = true;
   
   MMRESULT mmr;
   if(m_estate == StateRecording)
   {
      if(MMSYSERR_NOERROR != (mmr = Stop()))
      {
         TRACE("audWaveIn::Reset error stopping input device");
         return mmr;
      }
   }
   try
   {
        if(MMSYSERR_NOERROR != (mmr = waveInReset(
         m_hWaveIn)))
      {
         TRACE("audWaveIn::Reset error resetting input device");
         return mmr;
      }
   }
   catch(...)
   {
   }
   m_estate = StateOpened;
   m_bResetting = false;
   return MMSYSERR_NOERROR;
}

bool audWaveIn::IsResetting()
{
   return m_bResetting;
}


DWORD audWaveIn::GetAnalysisMillis()
{
   return (DWORD) ((double) GetBuffer().m_uiAnalysisSize * GetBuffer().m_uiSkippedSamplesCount * 1000.0 / m_waveFormatEx.nSamplesPerSec);
}

HWAVEIN audWaveIn::GetSafeHwavein()
{
   return m_hWaveIn;
}

void audWaveIn::TranslateWaveInMessage(gen::signal_object * pobj)
{
   SCAST_PTR(user::win::message::base, pbase, pobj);
   ASSERT(
      pbase->m_uiMessage == MM_WIM_OPEN ||
      pbase->m_uiMessage == MM_WIM_CLOSE ||
      pbase->m_uiMessage == MM_WIM_DATA);

   if(pbase->m_uiMessage == MM_WIM_DATA)
   {
      m_iBuffer--;
      DWORD msSampleTime = timeGetTime();
      LPWAVEHDR lpwavehdr = (LPWAVEHDR) pbase->m_lparam;
      GetBuffer().GetBuffer(lpwavehdr->dwUser).OnMultimediaDone();
      m_listenerset.WaveInDataProc(
         this,
         msSampleTime,
         lpwavehdr);

      if(m_pencoder != NULL)
      {
         m_pencoder->EncoderWriteBuffer(lpwavehdr->lpData, lpwavehdr->dwBytesRecorded);
      }

      if(!IsResetting() && IsRecording())
      {
         AddBuffer(lpwavehdr);
      }

   }
   pbase->m_bRet = true;
}

bool audWaveIn::IsRecording()
{
   return m_estate == StateRecording;
}

bool audWaveIn::IsOpened()
{
   return m_estate == StateOpened;
}

critical_section & audWaveIn::GetHandleCriticalSection()
{
    return m_csHandle;
}

int audWaveIn::AddRef()
{
   int iCount = ++m_iRefCount;
   return iCount;
}

int audWaveIn::Release()
{
   int iCount = --m_iRefCount;
   if(iCount == 0)
   {
      if(IsRecording())
      {
         Reset();
      }
      if(IsOpened())
      {
         close();
      }
   }
   return iCount;
}

void audWaveIn::AddListener(audWaveInListener *plistener)
{
   m_listenerset.add_unique(plistener);
   plistener->HookWaveIn(this);
}

void audWaveIn::RemoveListener(audWaveInListener *plistener)
{
   m_listenerset.remove(plistener);
}

MMRESULT audWaveIn::AddBuffer(int iBuffer)
{
   return AddBuffer(GetBuffer().GetHdr(iBuffer));
}

MMRESULT audWaveIn::AddBuffer(LPWAVEHDR lpwavehdr)
{
   MMRESULT mmr;
     if(MMSYSERR_NOERROR != (mmr = waveInAddBuffer(
      GetSafeHwavein(),  
      lpwavehdr,
      sizeof(WAVEHDR))))
   {
      TRACE("ERROR OPENING Adding INPUT DEVICE buffer");
   }
   m_iBuffer++;
   return mmr;
}

bool audWaveIn::InitializeEncoder()
{
   if(m_pencoder == NULL)
      return false;
   m_pencoder->EncoderSetSamplesPerSec(m_waveFormatEx.nSamplesPerSec);
   m_pencoder->EncoderSetBitsPerSample(m_waveFormatEx.wBitsPerSample);
   m_pencoder->EncoderSetChannelCount(m_waveFormatEx.nChannels);
   m_pencoder->EncoderInitialize();
   return true;
}




