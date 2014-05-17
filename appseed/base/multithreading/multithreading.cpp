#include "framework.h"


namespace multithreading
{


   CLASS_DECL_BASE comparable_array < HTHREAD > * s_phaThread = NULL;
   CLASS_DECL_BASE comparable_array < thread * > * s_pthreadptra = NULL;
   CLASS_DECL_BASE mutex * s_pmutex = NULL;


   CLASS_DECL_BASE void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_phaThread = new comparable_array < HTHREAD >;
      s_pthreadptra = new comparable_array < thread * >;
   }


   CLASS_DECL_BASE void term_multithreading()
   {

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_phaThread;
      s_phaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }

   CLASS_DECL_BASE void __node_on_init_thread(HTHREAD hthread,thread * pthread)
   {

      synch_lock sl(s_pmutex);

      s_phaThread->add(hthread);

      s_pthreadptra->add(pthread);

   }


   CLASS_DECL_BASE void __node_on_term_thread(HTHREAD hthread,thread * pthread)
   {

      synch_lock sl(s_pmutex);

      s_phaThread->remove(hthread);

      s_pthreadptra->remove(pthread);

   }



} // namespace multithreading