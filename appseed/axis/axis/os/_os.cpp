


#ifdef WINDOWSEX

#include "windows/_windows_os.cpp"

#elif defined(ANDROID)

#include "android/android.cpp"
#include "ansios/ansios_crypt.cpp"

#elif defined(LINUX)

#include "linux/_linux_os.cpp"
#include "x11/_x11.cpp"
#include "ansios/ansios_crypt.cpp"

#endif
