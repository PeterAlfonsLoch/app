#pragma once


#include "WaveBuffer.h"

#if !defined(WINDOWS)

typedef void * HWAVEOUT;
typedef int MMRESULT;

#endif

namespace iaudio
{
   class WaveStreamEffect;
}

class audWaveOut;
class audWavePlayer;

typedef struct CLASS_DECL_ca tagWaveProcDataMessage
{
   DWORD         m_dwBufferIndex;
   LPWAVEHDR   m_lpwavehdr;
   bool         m_bDelete;
   audWaveOut *   m_pwaveout;
} WAVEOUTDATAMESSAGE, * LPWAVEOUTDATAMESSAGE;

class audWaveBuffer;

class CLASS_DECL_ca audWaveOut :
   public ::radix::thread,
   public audWavePreBufferCallback
{
public:

   enum e_message
   {
      MessageBufferRequest = WM_APP + 101,
      MessageBufferReady = WM_APP + 102,
      MessageClose = WM_APP + 103,
   };

   enum  e_state
   {
      state_initial,
      StateOpened,
      StatePlaying,
      StateStopping,
      StateStopped,
      StatePaused,
   };

   audWavePreBuffer *                  m_pprebuffer;
   critical_section                    m_csOut;
   base_array < LPWAVEHDR, LPWAVEHDR > m_lphdraFree;
   audWavePlayer *                     m_pplayer;

   critical_section                    m_csPreBuffer;
   int                                 m_iLastBufferId;

   base_array < event *, event * >   m_evptraEnd;
   critical_section                    m_csHandle;
   ::radix::thread *                   m_pthreadCallback;
   HWAVEOUT                            m_hwaveout;
   WAVEFORMATEX                        m_waveformatex;
   audWaveBuffer *                     m_pwavebuffer;
   e_state                             m_estate;
   MMRESULT                            m_mmr;
   int                                 m_iBufferInMMSys;
   iaudio::WaveStreamEffect *          m_peffect;
   DWORD                               m_dwLostSampleCount;
   event                              m_eventStopped;


   audWaveOut(::ca::application * papp);
   virtual ~audWaveOut();


   audio_decode::decoder * SetDecoder(audio_decode::decoder * pdecoder);

   void install_message_handling(::user::win::message::dispatch * pinterface);

   int GetBufferInMMSystemCount();
   imedia::time GetPositionMillis();
   imedia::time GetPositionMillisForSynch();
   imedia::position get_position();
   imedia::position get_position_for_synch();
   void AttachEndEvent(event * pevent);
   bool Stop();
   e_state GetState();
   void BufferReady(LPWAVEHDR lpwavehdr);
   MMRESULT Start(const imedia::position & position);
   audWaveBuffer & GetBuffer();
   MMRESULT open(::radix::thread * pthreadCallback, int iBufferCount, int iBufferSampleCount);
   MMRESULT OpenEx(::radix::thread * pthreadCallback, int iBufferCount, int iBufferSampleCount, UINT uiSamplesPerSec, UINT uiChannelCount, UINT uiBitsPerSample);
   MMRESULT close();

   int GetBufferInMMSysCount();
   static audWaveOut * BeginThread(::ca::application * papp);
   void SetWaveStreamEffect(iaudio::WaveStreamEffect * peffect);
   bool Pause();
   bool Restart();
   MMRESULT GetLastMMResult();
   int GetBufferSize();
   void * GetBuffer(int iBuffer);
   HWAVEOUT GetSafeHandle();
   void PostClose();

   void OnPlaybackEnd();
   void _Free(LPWAVEHDR lpwavehdr);

   virtual bool initialize_instance();
   virtual int exit_instance();

   DECL_GEN_SIGNAL(OnMultimediaOpen)
   DECL_GEN_SIGNAL(OnMultimediaDone)
   DECL_GEN_SIGNAL(OnMultimediaClose)
   DECL_GEN_SIGNAL(OnBufferReady)
   DECL_GEN_SIGNAL(OnClose)

   void OutBufferDone(LPWAVEHDR lpwavehdr);
   virtual void OnPreBufferDone(int iId);

};

