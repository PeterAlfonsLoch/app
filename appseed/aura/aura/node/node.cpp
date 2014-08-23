#include "framework.h"


static oswindow g_oswindowSplash = NULL;


CLASS_DECL_AXIS void set_splash(oswindow oswindow)
{
   g_oswindowSplash = oswindow;
}

CLASS_DECL_AXIS oswindow get_splash()
{
   return g_oswindowSplash;
}
