#include "StdAfx.h"

namespace audio
{

   WaveRecorderInterface::WaveRecorderInterface(::ca::application * papp) :
      ca(papp)
   {
      m_pwaverecorder = AfxBeginThread < audWaveRecorder > (get_app());
   }

   WaveRecorderInterface::~WaveRecorderInterface()
   {
   }

   audWaveRecorder * WaveRecorderInterface::GetWaveRecorder()
   {
      return m_pwaverecorder;
   }
}
