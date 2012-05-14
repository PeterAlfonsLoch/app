#include "framework.h"


namespace ca
{

   interlocked_long::interlocked_long()
   {
#ifdef WINDOWS
      m_plong = (LONG *) _aligned_malloc(sizeof(LONG), 4);
#else
      m_plong = (LONG *) malloc(sizeof(LONG));
#endif
      *m_plong = 0;
   }

   interlocked_long::~interlocked_long()
   {
      if(m_plong != NULL)
      {
#ifdef WINDOWS
         _aligned_free(m_plong);
#else
         free(m_plong);
#endif
      }
   }

   void interlocked_long::add(long l)
   {
#ifdef WINDOWS
      InterlockedExchangeAdd(m_plong, l);
#else
      __sync_fetch_and_add(m_plong, l);
#endif
   }

   void interlocked_long::subtract(long l)
   {
#ifdef WINDOWS
      InterlockedExchangeAdd(m_plong, -l);
#else
      __sync_fetch_and_sub(m_plong, l);
#endif
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
