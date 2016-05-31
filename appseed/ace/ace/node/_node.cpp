#include "framework.h"

#ifdef WINDOWSEX
#include "windows/_windows_node.cpp"
#elif defined(METROWIN)
#include "metrowin/_metrowin_node.cpp"
#elif defined(ANDROID)
#include "android/_android_node.cpp"
#include "ansios/_ansios_node.cpp"
#elif defined(LINUX)
#include "linux/_linux_node.cpp"
#include "ansios/_ansios_node.cpp"
#elif defined(MACOS)
#include "macos/_macos_node.cpp"
#include "ansios/_ansios_node.cpp"
#elif defined(APPLE_IOS)
#include "ansios/_ansios_node.cpp"
#include "ios/_ios_node.cpp"
#endif



static oswindow g_oswindowSplash = NULL;


CLASS_DECL_ACE void set_splash(oswindow oswindow)
{
   g_oswindowSplash = oswindow;
}

CLASS_DECL_ACE oswindow get_splash()
{
   return g_oswindowSplash;
}
