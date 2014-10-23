#include "framework.h"


static mutex * s_pmutexDraw2dXlib = NULL;


mutex & xlib_mutex()
{

   return *s_pmutexDraw2dXlib;

}


void init_xlib_mutex(sp(::aura::application) papp)
{

    s_pmutexDraw2dXlib = new mutex(papp);

}
