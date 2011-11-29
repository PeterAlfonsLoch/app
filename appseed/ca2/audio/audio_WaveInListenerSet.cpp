#include "StdAfx.h"

audWaveInListenerSet::audWaveInListenerSet()
{

}

audWaveInListenerSet::~audWaveInListenerSet()
{

}

void audWaveInListenerSet::WaveInDataProc(audWaveIn *pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr)
{
   for(int i = 0; i < this->get_size(); i++)
   {
      this->element_at(i)->WaveInDataProc(
         pwavein,
         dwSampleTime,
         lpwavehdr);
   }
}

