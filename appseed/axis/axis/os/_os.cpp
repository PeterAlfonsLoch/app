


#ifdef WINDOWSEX

#include "windows/_windows_os.cpp"

#elif defined(ANDROID)

#include "android/android.cpp"
#include "ansios/ansios_crypt.cpp"

#endif