#include "StdAfx.h"

audWaveInListener::audWaveInListener()
{

}

audWaveInListener::~audWaveInListener()
{
   for(int i = 0; i < m_waveinptra.get_size(); i++)
   {
      m_waveinptra[i]->RemoveListener(this);
   }
}

void audWaveInListener::WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr)
{
   UNREFERENCED_PARAMETER(pwavein);
   UNREFERENCED_PARAMETER(dwSampleTime);
   UNREFERENCED_PARAMETER(lpwavehdr);
}

void audWaveInListener::HookWaveIn(audWaveIn * pwavein)
{
   m_waveinptra.add_unique(pwavein);
}

void audWaveInListener::UnhookWaveIn(audWaveIn * pwavein)
{
   m_waveinptra.remove(pwavein);
}

