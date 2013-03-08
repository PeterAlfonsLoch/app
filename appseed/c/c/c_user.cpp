#include "framework.h"




simple_mutex & user_mutex()
{

   static simple_mutex * s_pmutexUser = new simple_mutex();

   return *s_pmutexUser;

}
