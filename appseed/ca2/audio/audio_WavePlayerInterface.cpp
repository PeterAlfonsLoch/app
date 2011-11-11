#include "StdAfx.h"

namespace audio
{

   WavePlayerInterface::WavePlayerInterface(::ca::application * papp) :
      ca(papp)
   {
      m_pwaveplayer = AfxBeginThread < audWavePlayer > (get_app());
   }

   WavePlayerInterface::~WavePlayerInterface()
   {
   }

   audWavePlayer * WavePlayerInterface::GetWavePlayer()
   {
      return m_pwaveplayer;
   }
}
