// audWaveInListenerSet.h: interface for the audWaveInListenerSet class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


class audWaveIn;
class audWaveInListener;


class audWaveInListenerSet :
   public comparable_array <audWaveInListener *, audWaveInListener *>
{
public:


   audWaveInListenerSet();
   virtual ~audWaveInListenerSet();


   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);



};

