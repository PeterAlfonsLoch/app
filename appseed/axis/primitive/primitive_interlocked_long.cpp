#include "framework.h"


interlocked_long::interlocked_long()
{
#if defined(WINDOWS) || defined(APPLEOS)
   m_plong = (long *) aligned_memory_alloc(sizeof(long));
#else
   m_plong = (long *) malloc(sizeof(long));
#endif
   *m_plong = 0;
}

interlocked_long::~interlocked_long()
{
   if(m_plong != NULL)
   {
#if defined(WINDOWS) || defined(APPLEOS)
      memory_free(m_plong);
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

bool interlocked_long::operator > (long i) const
{
   return *m_plong > i;
}

bool interlocked_long::operator == (long i) const
{
   return *m_plong == i;
}



