#include "StdAfx.h"
#include "WaveEffectDevocalizer.h"

audWaveCentral::audWaveCentral()
{
   m_uiWaveInDevice = WAVE_MAPPER; 
   m_pwavein = NULL;
}

audWaveCentral::~audWaveCentral()
{
   Finalize();
}


audWaveIn * audWaveCentral::GetWaveIn()
{
    return m_pwavein;
}

bool audWaveCentral::Initialize(::ca::application * papp)
{

   if(m_pwavein != NULL)
      return true;

   set_app(papp);
   
   System.factory().creatable_small < audWaveEffectDevocalizer::Group >();
   System.factory().creatable_small < audWaveEffectDevocalizer::Group::Channel >();

   m_pwavein = AfxBeginThread < audWaveIn > (papp);
   if(m_pwavein != NULL)
   {
      m_pwavein->m_evInitialized.wait();
   }
  
   return m_pwavein != NULL;
}

bool audWaveCentral::Finalize()
{
    //if(m_pwavein != NULL)
    //{
      // delete m_pwavein;
      //m_pwavein = NULL;
    //}
   return true;
}

void audWaveCentral::close()
{
   if(m_pwavein != NULL)
   {
      m_pwavein->Stop();
      m_pwavein->Reset();
      m_pwavein->close();
      m_pwavein->PostThreadMessage(WM_QUIT, 0, 0);
   }
}

