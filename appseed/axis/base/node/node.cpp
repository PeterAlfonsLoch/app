#include "framework.h"


static oswindow g_oswindowSplash = NULL;


CLASS_DECL_BASE void set_splash(oswindow oswindow)
{
   g_oswindowSplash = oswindow;
}

CLASS_DECL_BASE oswindow get_splash()
{
   return g_oswindowSplash;
}
