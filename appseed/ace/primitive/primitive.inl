#pragma once

#include "ace/primitive/comparison/comparison_equals.h"

inline property & object::oprop(const char * psz)
{

   return oprop_set()[psz];

}


inline property & object::oprop(const char * psz) const
{

   return const_cast < object * > (this)->oprop_set()[psz];

}


inline property_set & object::oprop_set()
{

   if(m_psetObject == NULL)
   {

      m_psetObject = new property_set(get_app());

   }

   return *m_psetObject;

}




inline ::ace::allocatorsp & object::allocer()
{

   return m_pauraapp->m_allocer;

}



inline sp(::command_thread) object::command_thread()
{

   return m_pauraapp->command_thread();

}



template < class T >
inline bool dispatch::AddMessageHandler(
   signalid * pid,
   T * psignalizable,
   void (T::*pfn)(signal_details *),
   bool bAddUnique)
{

   synch_lock sl(m_pmutex);

   signal_item * psignal = m_signala.GetSignalById(pid);
   // If not found a existing Signal, create one
   if(psignal == NULL)
   {
      psignal                    = canew(signal_item);
      psignal->m_pid             = pid;
      psignal->m_psignal         = new class ::signal();
      m_signala.add(psignal);
   }
   else
   {
      if(bAddUnique && psignal->m_psignal->is_connected(psignalizable,pfn))
         return false;
   }

   // connect to the signal.
   psignal->m_psignal->connect(psignalizable, pfn);
   handler_item <T> * pitem = new handler_item<T>;
   pitem->m_psignalizable = psignalizable;
   psignal->m_handlera.add(pitem);
   m_iHandling++;
   return true;
}



template<>
inline UINT HashKey<const wchar_t *>(const wchar_t * key)
{
    uint64_t * puiKey = (uint64_t *)key;
#if defined(LINUX) || defined(MACOS)
    strsize counter = wcs32len_dup(key) * sizeof(wchar_t);
#else
    strsize counter = wcslen(key) * sizeof(wchar_t);
#endif
    uint64_t nHash = 0;
    while (compare::ge(counter, sizeof(*puiKey)))
    {
        nHash = (nHash << 5) + nHash + *puiKey++;
        counter -= sizeof(*puiKey);
    }
    const char * pszKey = (const char *)puiKey;
    while (counter-- >= 0) nHash = (nHash << 5) + nHash + *pszKey++;
    return (UINT)nHash;
}


