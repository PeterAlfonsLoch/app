#include "StdAfx.h"


namespace ca
{

   interlocked_long::interlocked_long()
   {
      m_plong = (LONG *) _aligned_malloc(sizeof(LONG), 4);
      *m_plong = 0;
   }

   interlocked_long::~interlocked_long()
   {
      if(m_plong != NULL)
      {
         _aligned_free(m_plong);
      }
   }

   void interlocked_long::add(long l)
   {
      InterlockedExchangeAdd(m_plong, l);
   }
    
   void interlocked_long::subtract(long l)
   {
      InterlockedExchangeAdd(m_plong, -l);
   }

   bool interlocked_long::operator > (int i) const
   {
      return *m_plong > i;
   }

   bool interlocked_long::operator == (int i) const
   {
      return *m_plong == i;
   }

} // namespace ca
