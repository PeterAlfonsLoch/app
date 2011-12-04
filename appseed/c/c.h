#include "radix.h"




#pragma once

#ifdef _WIN32
#ifdef __C__LIB
   #define CLASS_DECL_c
#elif defined(__C__DLL)
   #define CLASS_DECL_c  _declspec(dllexport)
#else
   #define CLASS_DECL_c  _declspec(dllimport)
#endif
#else
   #define CLASS_DECL_c
#endif



#include "version.h"


#include "types.h"


#include "natural.h"


#define if_then(p, q)  ((!(p))||(!(q)))





extern "C"
{

   #include "cpu_architecture.h"

}




#include "_libct.h"

#include "printf.h"
#include "sprintf.h"
#include "str.h"
#include "std_file.h"
#include "atol.h"


#include "count.h"
#include "index.h"
#include "keep_true.h"

#include "heap.h"
#include "gdi.h"
#include "mem.h"
#include "_c_math.h"

#include "verisimple_string.h"
#include "verisimple_wstring.h"
#include "vsstringtow.h"
#include "wstringtovss.h"

#include "dir.h"
#include "md5.h"

#include "simple_obj.h"

#include "template.h"
#include "simple_array.h"
#include "simple_map.h"
#include "stra.h"

#include "xmlite.h"
#include "file.h"

#include "launcher.h"

#include "small_ipc_channel.h"

#include "simple_mutex.h"
#include "simple_event.h"

#include "mutex_lock.h"

#include "simple_critical_section.h"

#include "library.h"
#include "hotplugin/hotplugin.h"
#include "spa/spa.h"

#include "bsdiff/bsdiff.h"


#if defined(MACOS)

#include "macos/c_os.h"

#elif defined(LINUX)

#include "linux/c_os.h"

#else

#include "windows/c_os.h"

#endif


#include "message_loop.h"


#define return_(y, x) {y = x; return;}

extern "C"
{
   int _c_lock_is_active(const char * pszName);
   int _c_lock(const char * pszName, void ** pdata);
   int _c_unlock(void ** pdata);
}


vsstring _c_get_file_name(const char * psz, bool bCreate = false, int * pfd = NULL);

