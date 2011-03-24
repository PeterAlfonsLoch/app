// AudioGen1.cpp : implementation file
//

#include "stdafx.h"

#include "math.h"

#include "_vmsaudioWaveOut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AudioGen

IMPLEMENT_DYNCREATE(AudioGen, CWinThread)

AudioGen::AudioGen()
{
   m_i = 0;
   m_iBufferSize = 16 * 44100;
   m_lpb = new BYTE[m_iBufferSize];

   m_dFreq = 440.;
   m_dTime =0.0;
   
   
}

AudioGen::~AudioGen()
{
}

BOOL AudioGen::InitInstance()
{
	// TODO:  perform and per-thread initialization here
   Gen();
	return TRUE;
}

int AudioGen::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(AudioGen, CWinThread)
	//{{AFX_MSG_MAP(AudioGen)
	ON_COMMAND(ID_EXECUTE_PLAY, OnExecutePlay)
	ON_COMMAND(ID_EXECUTE_STOP, OnExecuteStop)
	//}}AFX_MSG_MAP
   ON_THREAD_MESSAGE(_vmsaudio::WaveOut::MessageBufferRequest, OnWaveOutBufferRequest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AudioGen message handlers

void AudioGen::OnWaveOutBufferRequest(WPARAM wparam, LPARAM lparam)
{
   _vmsaudio::WaveOut * pwaveout = m_pwaveout;
   LPWAVEHDR lpwavehdr = (LPWAVEHDR) lparam;

   Buf((LPBYTE) lpwavehdr->lpData, lpwavehdr->dwBufferLength);
   pwaveout->BufferReady(lpwavehdr);

}

void AudioGen::Buf(LPBYTE lpdata, DWORD dwLen)
{
   while(dwLen > 0)
   {
      int i;
      if(m_i >= m_iBufferSize)
         m_i = 0;

      int iRemain = m_iBufferSize - m_i;
      int iCopy = min(dwLen, iRemain);
   
      memcpy(lpdata, &m_lpb[m_i], iCopy);
   
      dwLen -= iCopy;
      m_i += iCopy;
   }

}

void AudioGen::Gen(LPBYTE lpdata, DWORD dwLen)
{
   int i = 0;
   short * lpsh = (short *) lpdata;
   dwLen = dwLen / 2;
   double x;
   
   double pi = 3.141592654;
   double pi2 = pi * 2;
   double dSampleTime = 1.0 / 44100.0;
   m_dTime = 1.0;
   for(DWORD dw = 0; dw < dwLen; dw += 2)
   {
      m_dTime += dSampleTime;
      x = sin(pi2 * m_dTime * m_dFreq) * 16000;
      x += sin(2 * pi2 * m_dTime * m_dFreq) * 10000;
      x += sin(3 * pi2 * m_dTime * m_dFreq) * 5000;
      x += sin(4 * pi2 * m_dTime * m_dFreq) * 5000;
      x += sin(5 * pi2 * m_dTime * m_dFreq) * 5000;
      x += sin(6 * pi2 * m_dTime * m_dFreq) * 5000;
      x = x * pow(m_dTime, -3);
      lpsh[dw] = x;
      lpsh[dw + 1] = x;

      i++;
   }

}

void AudioGen::Gen()
{
   Gen(m_lpb, m_iBufferSize);
}

void AudioGen::OnExecutePlay() 
{
	m_pwaveout->Start();
}

void AudioGen::OnExecuteStop() 
{
   m_pwaveout->Stop();
}
