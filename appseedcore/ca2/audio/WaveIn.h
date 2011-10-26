#pragma once


#define WAVM_WAVE_PROC_DATA 1000

class audWaveIn;
class audWaveBuffer;

/*typedef struct CLASS_DECL_ca tagWaveProcDataMessage
{
   DWORD               m_msSampleTime;
   DWORD               m_dwBufferIndex;
   LPWAVEHDR         m_lpwavehdr;
   bool               m_bDelete;
   audWaveIn *         m_pwavein;
} WAVEPROCDATAMESSAGE, * LPWAVEPROCDATAMESSAGE;*/

class audWaveInListener;


#ifdef LINUX
#include <alsa/asoundlib.h>
#endif



class CLASS_DECL_ca audWaveIn :
   public ::radix::thread
{
public:


   enum  e_state
   {
      state_initial,
      StateOpened,
      StateRecording,
      state_stopping,
      StateStopped,
   };


   audio_decode::encoder *          m_pencoder;

   critical_section                 m_csHandle;
   bool                             m_bResetting;
   int                              m_iRefCount;
   int                              m_iBuffer;
   e_state                          m_estate;
   audWaveBuffer *                  m_pwavebuffer;

#ifdef WINDOWS
   HWAVEIN                          m_hWaveIn;
#else
   snd_pcm_t                        m_pcm;
   snd_pcm_hw_params_t              m_hwparams;
#endif

   WAVEFORMATEX                     m_waveFormatEx;


   audWaveInListenerSet             m_listenerset;

   event                            m_evInitialized;
   event                            m_eventExitInstance;
   event                            m_eventStopped;


   audWaveIn(::ca::application * papp);
   virtual ~audWaveIn();


   bool InitializeEncoder();

   MMRESULT AddBuffer(int iBuffer);
   MMRESULT AddBuffer(LPWAVEHDR lpwavehdr);
   void RemoveListener(audWaveInListener * plistener);
   void AddListener(audWaveInListener * plistener);
   // Attributes
   critical_section & GetHandleCriticalSection();
   bool IsOpened();
   bool IsRecording();
#ifdef WINDOWS
   HWAVEIN GetSafeHwavein();
#endif
   DWORD GetAnalysisMillis();
   bool IsResetting();

   UINT GetState();
   LPWAVEFORMATEX GetFormatEx();
   // Reference count
   int Release();
   int AddRef();


   audWaveBuffer & GetBuffer();

   // Operations
   MMRESULT open(int iBufferCount, int iBufferSampleCount);
   MMRESULT close();
   MMRESULT Stop();
   MMRESULT Start();
   MMRESULT Reset();

   // Event handlers
   virtual void TranslateWaveInMessage(gen::signal_object * pobj);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual void pre_translate_message(gen::signal_object * pobj);

#ifdef WINDOWS
   static void CALLBACK WaveInProc(HWAVEIN hwi, UINT uMsg,
      DWORD dwInstance,
      DWORD dwParam1,
      DWORD dwParam2);
#endif

};
