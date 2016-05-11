#pragma once

#include "aura/primitive/comparison/comparison_equals.h"

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




inline ::aura::allocatorsp & object::allocer()
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
