#pragma once


#include "c/_/CarlosGustavoCecynLundgrenVidaEternaDeCamiloSasukeTsumanuma.h"


#ifndef __cplusplus
   #error ca2 API requires C++ compilation (use a .cpp suffix)
#endif


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


namespace ca
{


   class application;


} // namespace ca



#include "nodeapp/operational_system/_.h"


#include "c/vms/vms.h"


#include "c/version.h"


#include "types.h"


#include "natural.h"

#include "nessie.h"


#define if_then(p, q)  ((!(p))||(!(q)))


extern "C"
{

   #include "cpu_architecture.h"

}


#include "_libct.h"


#include "count.h"
#include "index.h"
#include "keep_true.h"


#include "debug.h"


#include "printf.h"
#include "sprintf.h"
#include "str.h"
#include "std_file.h"
#include "atol.h"



#include "heap.h"
#include "gdi.h"
#include "mem.h"

#include "_c_math.h"

#include "geometric_types.h"


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
#include "simple_list.h"
#include "stra.h"

#include "xmlite.h"
#include "file.h"

#include "launcher.h"
#include "simple_shell_launcher.h"

#include "small_ipc_channel.h"

#include "simple_mutex.h"
#include "simple_event.h"

#include "mutex_lock.h"

#include "simple_critical_section.h"

#include "library.h"
#include "simple_memory.h"
#include "base64.h"
#include "c/hotplugin/hotplugin.h"
#include "c/simple_ui/simple_ui.h"
#include "c/spa/spa.h"

#include "c/bsdiff/bsdiff.h"


#include "c/os/os.h"


#include "message_loop.h"

#include "url.h"

#include "international.h"




#define return_(y, x) {y = x; return;}

extern "C"
{
   int _c_lock_is_active(const char * pszName);
   int _c_lock(const char * pszName, void ** pdata);
   int _c_unlock(void ** pdata);
}


vsstring _c_get_file_name(const char * psz, bool bCreate = false, int * pfd = NULL);

CLASS_DECL_c vsstring get_system_error_message(DWORD dwError);


#include "simple_app.h"
