#pragma once




#ifdef __cplusplus
//#define EXTERN_C			extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		}
#else
//#define EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C
#endif



#ifndef __cplusplus
   #error ca API requires C++ compilation (use a .cpp suffix)
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

#define system_user_1 "system_user_1"
#define system_user_2 "system_user_2"

#ifdef _LP64
#define OS64BIT
#endif


namespace ca
{


   class application;


} // namespace ca


#include "nodeapp/operational_system/_.h"


class CLASS_DECL_c lparam
{
public:


   LPARAM m_lparam;


   lparam(LPARAM lparam = 0)
   {
      m_lparam = lparam;
   }

   lparam(const void * p)
   {
      m_lparam = (LPARAM) p;
   }

   lparam(const lparam & lparam)
   {
      m_lparam = lparam.m_lparam;
   }

   lparam(const ::ca::null &)
   {
      m_lparam = 0;
   }

   operator LPARAM &()
   {
      return m_lparam;
   }

   lparam & operator = (const lparam & lparam)
   {
      m_lparam = lparam.m_lparam;
      return *this;
   }

   lparam & operator = (LPARAM lparam)
   {
      m_lparam = lparam;
      return *this;
   }

   lparam & operator = (const ::ca::null &)
   {
      m_lparam = 0;
      return *this;
   }

};


#include "c/vms/vms.h"


#include "c/version/version.h"


#include "c_types.h"


#include "c_natural.h"


#include "c_logic.h"


#include "c_time.h"


#include "c_cpu_architecture.h"


#include "c_libc.h"


#include "c_count.h"
#include "c_index.h"
#include "c_number.h"
#include "c_keep_true.h"


#include "c_debug.h"


#include "c_printf.h"
#include "c_sprintf.h"
#include "c_str.h"



#include "c_heap.h"
#include "c/simple_graphics/simple_graphics_first_phase.h"
#include "c_memory.h"

#include "c_math.h"

#include "c_geometric_types.h"


#include "c_verisimple_string.h"
#include "c_verisimple_wstring.h"
#include "c_vsstringtow.h"
#include "c_wstringtovss.h"


#include "c_c.h"
#include "c_smart_pointer1.h"
#include "c_smart_pointer2.h"



#include "c_dir.h"
#include "c_md5.h"

#include "c_simple_obj.h"

#include "c_template.h"
#include "c_simple_array.h"
#include "c_simple_map.h"
#include "c_simple_list.h"
#include "c_stra.h"

#include "c_xmlite.h"
#include "c_file.h"

#include "c_launcher.h"


#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#define BSD_STYLE_SOCKETS
#include "c_small_ipc_channel.h"

#endif


#include "c_simple_mutex.h"
#include "c_simple_event.h"

#include "c_mutex_lock.h"

#include "c_simple_critical_section.h"

#include "c_library.h"

#include "c_simple_memory.h"

#include "c_file_watcher.h"
#include "c_file_watcher_impl.h"



/*#ifndef WINDOWS
#define VK_TAB 1
#define VK_RETURN 2
#define VK_BACK 3
#define VK_DELETE 6
#define VK_SPACE 9
#endif*/


#include "c/os/os.h"

#include "c/cross/cross.h"


#include "c_conv.h"
#include "c_string_to_integer.h"
#include "c_integer_to_string.h"


#include "c/simple_graphics/simple_graphics_second_phase.h"


#include "c_simple_shell_launcher.h"



#include "c_file_watcher_thread.h"
#include "c_file_watcher_listener_thread.h"
#include "c_async.h"


#include "c_base64.h"


#include "c/hotplugin/hotplugin.h"
#include "c/simple_ui/simple_ui.h"
#include "c/crypt/crypt.h"
#include "c/spa/spa.h"

#include "c/bsdiff/bsdiff.h"




#include "c_message_loop.h"

#include "c_url.h"
#include "c_net.h"

#include "c_international.h"



#define return_(y, x) {y = x; return;}

extern "C"
{
   int32_t _c_lock_is_active(const char * pszName);
   int32_t _c_lock(const char * pszName, void ** pdata);
   int32_t _c_unlock(void ** pdata);
}


CLASS_DECL_c vsstring _c_get_file_name(const char * psz, bool bCreate = false, int32_t * pfd = ::null());

CLASS_DECL_c vsstring get_system_error_message(uint32_t dwError);

//#ifndef METROWIN
//#include <openssl/ssl.h>
//#endif

#ifndef WINDOWSEX
#if !defined(LINUX) && !defined(MACOS)
CLASS_DECL_c WINBOOL IsWindow(oswindow oswindow);
#endif
#endif


#include "c_user.h"

#include "zlib/zlib.h"

#include "c_simple_app.h"



