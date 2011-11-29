#include "StdAfx.h"
#include "WaveEffectCrescendo.h"

#include <math.h>

audWaveEffectCrescendo::audWaveEffectCrescendo()
{
   m_bSustain     = true;
   m_bTriggerEnd  = true;
   m_bEnd         = true;
}

audWaveEffectCrescendo::~audWaveEffectCrescendo()
{

}

void audWaveEffectCrescendo::SetLengthMillis(DWORD dwMillis, DWORD dwSamplesPerSec)
{
   m_iLength = dwSamplesPerSec * dwMillis / 1000;
}

void audWaveEffectCrescendo::SetFinalScale(short shMul, short shDiv)
{
   m_shFinalScaleDiv = shMul;
   m_shFinalScaleMul = shDiv;
}

int audWaveEffectCrescendo::Process16bits(short * pshStream, int iCountParam)
{
   ASSERT(iCountParam % 2 == 0);

   
   count iCount = (count) min(iCountParam, m_iLength - m_iStep);
   
   short * psh = pshStream;
   int i;
   for(i = 0; i < iCount; i++)
   {
      m_dCurrentRate *= m_dDifferentialRate;
      *psh++ = (short) (*psh * m_dCurrentRate);
      *psh++ = (short) (*psh * m_dCurrentRate);
      m_iStep++;
   }
   if(m_bSustain)
   {
      for(; i < iCountParam; i++)
      {
         *psh++ = (short) (*psh * m_dCurrentRate);
         *psh++ = (short) (*psh * m_dCurrentRate);
         m_iStep++;
      }
   }
   return iCount;
}

void audWaveEffectCrescendo::Initialize()
{
   m_iStep = 0;
   m_dDifferentialRate = 1.0 - (7.0 / (double) m_iLength);
   m_dCurrentRate = 1.0;
}

bool audWaveEffectCrescendo::IsEndOfEffect()
{
   if(m_bEnd)
   {
      if(m_iStep >= (int) (m_iLength - 1))
         return true;
   }
   return false;
}

