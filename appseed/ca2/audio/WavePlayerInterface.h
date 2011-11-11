#pragma once

namespace audio
{

   class CLASS_DECL_ca WavePlayerInterface :
      virtual public ::radix::object
   {
   public:


      audWavePlayer *   m_pwaveplayer;

      WavePlayerInterface(::ca::application * papp);
      virtual ~WavePlayerInterface();

      audWavePlayer * GetWavePlayer();
   };



} // audio