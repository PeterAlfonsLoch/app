#pragma once


class audWaveIn;


#if !defined(WINDOWS)
typedef struct tag_WAVEHDR
{
   LPBYTE   lpbyte;
   UINT     uiCount;
} WAVEHDR, * LPWAVEHDR;
#endif


class CLASS_DECL_ca audWaveInListener
{
public:


   comparable_array < audWaveIn *, audWaveIn * > m_waveinptra;


   audWaveInListener();
   virtual ~audWaveInListener();

   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);

   void HookWaveIn(audWaveIn * pwavein);
   void UnhookWaveIn(audWaveIn * pwavein);


};


