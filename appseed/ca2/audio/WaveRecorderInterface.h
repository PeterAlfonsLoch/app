#pragma once

namespace audio
{

   class CLASS_DECL_ca WaveRecorderInterface :
      virtual public ::radix::object
   {
   public:


      audWaveRecorder *   m_pwaverecorder;

      WaveRecorderInterface(::ca::application * papp);
      virtual ~WaveRecorderInterface();

      audWaveRecorder * GetWaveRecorder();
   };



} // audio