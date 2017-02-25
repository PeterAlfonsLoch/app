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
#include "linux/_linux_os.cpp"
#include "cross/_cross_os.cpp"


#elif defined(MACOS)


#include "ansios/_ansios_os.cpp"
#include "macos/_macos_os.cpp"


#elif defined(APPLE_IOS)


#include "ansios/_ansios_os.cpp"
#include "ios/_ios_os.cpp"


#endif
















