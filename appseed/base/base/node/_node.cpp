//#include "framework.h"


#ifdef WINDOWSEX

#include "windows/_windows_node.cpp"

#elif defined(METROWIN)

//#include "windows/windows_message_queue.h"

//#include "windows/windows_message_queue.cpp"
#include "metrowin/_metrowin_node.cpp"

#elif defined(ANDROID)

#include "android/_android_node.cpp"

#elif defined(LINUX)

#include "linux/_linux_node.cpp"

#elif defined(MACOS)

#include "macos/_macos_node.cpp"

#endif
