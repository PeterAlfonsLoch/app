#include "framework.h"


static mutex * s_pmutex = NULL;

mutex & cairo_mutex()
{

   return *s_pmutex;

}


void init_cairo_mutex(sp(::base::application) papp)
{

    s_pmutex = new mutex(papp);

}
