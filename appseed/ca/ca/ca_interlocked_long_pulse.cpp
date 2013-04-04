#include "framework.h"


namespace ca
{

   interlocked_long_pulse::interlocked_long_pulse(interlocked_long * plockedlong, long lLevel)
   {
      m_plockedlong     = plockedlong;
      m_lLevel          = lLevel;
      if(m_plockedlong != ::null())
      {
         m_plockedlong->add(m_lLevel);
      }
   }
      
   interlocked_long_pulse::~interlocked_long_pulse()
   {
      if(m_plockedlong != ::null())
      {
         m_plockedlong->subtract(m_lLevel);
      }
   }

} // namespace ca
