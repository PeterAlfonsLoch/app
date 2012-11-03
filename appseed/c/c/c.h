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


#include "c/version/version.h"


#include "c_types.h"


#include "c_natural.h"


#include "c_logic.h"


#include "c_time.h"


#include "c_cpu_architecture.h"


#include "c_libc.h"


#include "c_count.h"
#include "c_index.h"
#include "c_keep_true.h"


#include "c_debug.h"


#include "c_printf.h"
#include "c_sprintf.h"
#include "c_str.h"
#include "c_std_file.h"
#include "c_atol.h"
#include "c_conv.h"



#include "c_heap.h"
#include "c/simple_graphics/simple_graphics_first_phase.h"
#include "c_mem.h"

#include "c_math.h"

#include "c_geometric_types.h"


#include "c_verisimple_string.h"
#include "c_verisimple_wstring.h"
#include "c_vsstringtow.h"
#include "c_wstringtovss.h"

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
#include "c_simple_shell_launcher.h"


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



#ifndef WINDOWS
#define VK_TAB 1
#define VK_RETURN 2
#define VK_BACK 3
#define VK_DELETE 6
#define VK_SPACE 9
#endif


#include "c/os/os.h"


#include "c/simple_graphics/simple_graphics_second_phase.h"




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

#include "c_international.h"



#define return_(y, x) {y = x; return;}

extern "C"
{
   int _c_lock_is_active(const char * pszName);
   int _c_lock(const char * pszName, void ** pdata);
   int _c_unlock(void ** pdata);
}


vsstring _c_get_file_name(const char * psz, bool bCreate = false, int * pfd = NULL);

CLASS_DECL_c vsstring get_system_error_message(DWORD dwError);


#include "c_simple_app.h"


inline void * zero(void * p, size_t s)
{
   memset(p, 0, s);
   return p;
}


CLASS_DECL_c bool from_string(in6_addr * addr, const char * string);
CLASS_DECL_c vsstring to_string(const in6_addr *addr);






#if BYTE_ORDER == BIG_ENDIAN

#define HTONS(n) (n)
#define NTOHS(n) (n)
#define HTONL(n) (n)
#define NTOHL(n) (n)

#else

#define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))
#define NTOHS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

#define HTONL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))

#define NTOHL(n) (((((unsigned long)(n) & 0xFF)) << 24) | \
                  ((((unsigned long)(n) & 0xFF00)) << 8) | \
                  ((((unsigned long)(n) & 0xFF0000)) >> 8) | \
                  ((((unsigned long)(n) & 0xFF000000)) >> 24))
#endif

#if 0

unsigned short htons(unsigned short n);
unsigned short ntohs(unsigned short n);
unsigned long htonl(unsigned long n);
unsigned long ntohl(unsigned long n);

#define htons(n) HTONS(n)
#define ntohs(n) NTOHS(n)

#define htonl(n) HTONL(n)
#define ntohl(n) NTOHL(n)

#endif