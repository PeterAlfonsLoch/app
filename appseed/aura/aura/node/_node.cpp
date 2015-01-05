#include "framework.h"

#ifdef WINDOWSEX
#include "windows/_windows_node.cpp"
#elif defined(METROWIN)
#include "metrowin/_metrowin_node.cpp"
#elif defined(ANDROID)
#include "android/_android_node.cpp"
#include "ansios/_ansios_node.cpp"
#endif



static oswindow g_oswindowSplash = NULL;


CLASS_DECL_AURA void set_splash(oswindow oswindow)
{
   g_oswindowSplash = oswindow;
}

CLASS_DECL_AURA oswindow get_splash()
{
   return g_oswindowSplash;
}
