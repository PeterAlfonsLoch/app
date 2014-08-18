#include "framework.h"


::mutex * g_pmutexThreading = NULL;

int g_iThreadingCount = 0;


CLASS_DECL_AXIS void __init_threading_count()
{

   g_pmutexThreading = new mutex(NULL);

   g_iThreadingCount = 0;

}


CLASS_DECL_AXIS void __term_threading_count()
{

   delete g_pmutexThreading;

   g_pmutexThreading = NULL;

}


CLASS_DECL_AXIS void __inc_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount++;

}


CLASS_DECL_AXIS void __dec_threading_count()
{

   single_lock sl(g_pmutexThreading,false);

   g_iThreadingCount--;

}




