#include "StdAfx.h"

audWaveCentralContainer::audWaveCentralContainer()
{
   m_pwavecentral = new audWaveCentral();
}

audWaveCentralContainer::~audWaveCentralContainer()
{
   delete m_pwavecentral;
}

audWaveCentral & audWaveCentralContainer::GetAudioWaveCentral()
{
   return *m_pwavecentral;
}



