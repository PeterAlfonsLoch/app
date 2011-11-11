#pragma once

#include "WaveStreamEffect.h"

namespace iaudio
{

   class WaveStreamEffect;
   class WaveStreamEffectOrder;

   enum EWaveEffectInsert
   {
      WaveEffectInsertBeforeFirst,
      WaveEffectInsertAfterLast,
   };

   class CLASS_DECL_ca WaveStreamEffectChain :
      public WaveStreamEffect   
   {
      // Attributes
   protected:
      base_array < WaveStreamEffect *, WaveStreamEffect * > m_effectptra;

   public:

   public:
      


      WaveStreamEffectChain();
      virtual ~WaveStreamEffectChain();

      bool InsertEffect(EWaveEffectInsert einsert, WaveStreamEffect * peffect);

      virtual int Process16bits(short * pshStream, int iCount);

   protected:
      void SortEffectChain();

   };

} // namespace iaudio
