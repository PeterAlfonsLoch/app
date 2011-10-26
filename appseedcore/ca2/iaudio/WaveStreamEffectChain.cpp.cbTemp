#include "StdAfx.h"
#include "WaveStreamEffect.h"
#include "WaveStreamEffectChain.h"


namespace iaudio
{

   WaveStreamEffectChain::WaveStreamEffectChain()
   {

   }

   WaveStreamEffectChain::~WaveStreamEffectChain()
   {

   }


   bool WaveStreamEffectChain::InsertEffect(EWaveEffectInsert einsert, WaveStreamEffect *peffect)
   {
      ASSERT(peffect != this);

      if(peffect == this)
         return false;

      switch(einsert)
      {
      case WaveEffectInsertBeforeFirst:
         {
            m_effectptra.insert_at(0, peffect);
         }
         break;
      case WaveEffectInsertAfterLast:
         {
            m_effectptra.add(peffect);
         }
         break;
      default:
         ASSERT(FALSE);
         return false;
      }

      return true;

   }

   void WaveStreamEffectChain::SortEffectChain()
   {
   }

   int WaveStreamEffectChain::Process16bits(short *pshStream, int iCount)
   {
      for(int i = 0; i < m_effectptra.get_size(); i++)
      {
         iCount = m_effectptra[i]->Process16bits(pshStream, iCount);
      }
      return iCount;
   }


} // namespace iaudio



