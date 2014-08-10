#include "framework.h"


//static mutex * s_pmutex = NULL;

mutex & cairo_mutex()
{

   //return *s_pmutex;

   return user_mutex();

}


void init_cairo_mutex()
{

//    s_pmutex = new mutex(papp);

}
