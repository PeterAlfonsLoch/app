#include "framework.h"
#include "axis/user/user.h"
#ifdef LINUX
#include "axis/os/linux/linux_cross_win_gdi_internal.h"
#elif defined(ANDROID)
//#include "axis/os/android/android_cross_win_gdi_internal.h"
#endif


#ifdef WINDOWSEX
#define min MIN
#define max MAX
#undef new
#include <gdiplus.h>
#define new AURA_NEW
#undef min
#undef max
#endif

#include <math.h>


//#if defined(LINUX) || defined(ANDROID) || defined(APPLEOS) || defined(SOLARIS)
//int_ptr get_map_failed();
//void my_munmap(void * pcolorref,HANDLE hfile);
//void * my_open_map(const char * psz,HANDLE * pfile,bool bRead,bool bWrite,int64_t size);
//#endif


#include "base/_base_base_base.cpp"
//#include "hotplugin/_hotplugin.cpp"
//#include "install/_install.cpp"
//#include "message/_message.cpp"
#include "node/_node.cpp"
#include "os/_os.cpp"













