//#include "framework.h"

#ifdef WINDOWSEX

#include "windows/_windows_os.cpp"

#elif defined(METROWIN)

#include "metrowin/_metrowin_os.cpp"

#elif defined(ANDROID)


#include "ansios/_ansios_os.cpp"
#include "android/_android_os.cpp"


#elif defined(LINUX)


#include "ansios/_ansios_os.cpp"
//#include "linux/_linux_os.cpp"


#endif
















