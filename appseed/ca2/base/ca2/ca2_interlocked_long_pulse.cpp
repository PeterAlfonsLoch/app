#include "framework.h"


namespace ca2
{

   interlocked_long_pulse::interlocked_long_pulse(interlocked_long * plockedlong, long lLevel)
   {
      m_plockedlong     = plockedlong;
      m_lLevel          = lLevel;
      if(m_plockedlong != NULL)
      {
         m_plockedlong->add(m_lLevel);
      }
   }
      
   interlocked_long_pulse::~interlocked_long_pulse()
   {
      if(m_plockedlong != NULL)
      {
         m_plockedlong->subtract(m_lLevel);
      }
   }

} // namespace ca2
