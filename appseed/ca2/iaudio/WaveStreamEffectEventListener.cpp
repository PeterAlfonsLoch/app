#include "StdAfx.h"
#include "WaveStreamEffectEventListener.h"

namespace iaudio
{

   WaveStreamEffectEventListener::WaveStreamEffectEventListener()
   {

   }

   WaveStreamEffectEventListener::~WaveStreamEffectEventListener()
   {

   }

   void WaveStreamEffectEventListener::OnWaveStreamEffectEvent(WaveStreamEffect *peffect, int iEvent)
   {
      UNREFERENCED_PARAMETER(peffect);
      UNREFERENCED_PARAMETER(iEvent);
   }

} // namespace iaudio