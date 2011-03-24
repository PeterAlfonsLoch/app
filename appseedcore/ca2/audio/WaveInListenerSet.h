// audWaveInListenerSet.h: interface for the audWaveInListenerSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAVEINLISTENERSET_H__EAE90D35_0F63_4FD7_B6AB_05E2C9E1BD0F__INCLUDED_)
#define AFX_WAVEINLISTENERSET_H__EAE90D35_0F63_4FD7_B6AB_05E2C9E1BD0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class audWaveIn;

   class audWaveInListener;

class audWaveInListenerSet :
   public comparable_array <audWaveInListener *, audWaveInListener *>
{
   friend class audWaveIn;
public:
   audWaveInListenerSet();
   virtual ~audWaveInListenerSet();

protected:
   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);
};


#endif // !defined(AFX_WAVEINLISTENERSET_H__EAE90D35_0F63_4FD7_B6AB_05E2C9E1BD0F__INCLUDED_)
