#pragma once

#include "iaudio/WaveStreamEffect.h"

class audWaveEffectCrescendo :
   public iaudio::WaveStreamEffect
{
public:
   virtual bool IsEndOfEffect();
   virtual int Process16bits(short * pshStream, int iCount);

   void SetFinalScale(short shMul, short shDiv);
   
   void SetLengthMillis(DWORD dwMillis, DWORD dwSamplesPerSec);
   void Initialize();

   audWaveEffectCrescendo();
   virtual ~audWaveEffectCrescendo();

   int      m_iLength; // in samples
   bool     m_bSustain;
   short    m_shFinalScaleMul;
   short    m_shFinalScaleDiv;
   bool     m_bTriggerEnd;
   int      m_iStep;
   double   m_dDifferentialRate;
   double   m_dCurrentRate;

};
