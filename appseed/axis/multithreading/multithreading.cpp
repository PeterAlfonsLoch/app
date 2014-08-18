#include "framework.h"


namespace multithreading
{


   CLASS_DECL_AXIS raw_array < HTHREAD > * s_phaThread = NULL;
   CLASS_DECL_AXIS raw_array < thread * > * s_pthreadptra = NULL;
   CLASS_DECL_AXIS mutex * s_pmutex = NULL;


   CLASS_DECL_AXIS void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_phaThread = new raw_array < HTHREAD >;
      s_pthreadptra = new raw_array < thread * >;

      __node_init_multithreading();

   }


   CLASS_DECL_AXIS void term_multithreading()
   {

      __node_term_multithreading();

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_phaThread;
      s_phaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }


} // namespace multithreading











mutex & user_mutex()
{

   static mutex * s_pmutexUser = new mutex();

   return *s_pmutexUser;
   //return *((mutex *)NULL);

}

mutex & message_dispatch_mutex()
{

   static mutex * s_pmutexMessageDispatch = new mutex();

   return *s_pmutexMessageDispatch;

}



