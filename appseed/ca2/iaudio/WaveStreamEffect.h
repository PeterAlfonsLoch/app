#pragma once

namespace iaudio
{
   class WaveStreamEffectChain;

   class CLASS_DECL_ca WaveStreamEffect :
      virtual public ::radix::object
   {
   public:
      friend class WaveStreamEffectChain;

      bool     m_bEnd;

      WaveStreamEffect();
      virtual ~WaveStreamEffect();

      virtual bool IsEndOfEffect();
      virtual int Process16bits(short * pshStream, int iCount) = 0;

   };

} // namespace iaudio