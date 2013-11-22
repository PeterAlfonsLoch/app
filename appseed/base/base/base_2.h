#pragma once


#include "base/base/base.h"


#ifndef __cplusplus
   #error ca API requires C++ compilation (use a .cpp suffix)
#endif


#ifdef __CA__STATIC
   #define CLASS_DECL_BOOT
#elif defined(__CA__LIBRARY)
   #define CLASS_DECL_BOOT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_BOOT  CLASS_DECL_IMPORT
#endif






#include "nodeapp/operational_system/_ca_2.h"


#if defined(MACOS)
#include "ca/macos/ca_os_internal.h"
#elif defined(LINUX)
#include "ca/linux/ca_os_internal.h"
#elif defined(WINDOWS)
#include "ca/windows/ca_os_internal.h"
#elif defined(ANDROID)
#include "ca/android/ca_os_internal.h"
#endif





#include "ca/vms/vms.h"


#include "ca/version/version.h"


#include "ca_types.h"


#include "ca_natural.h"


#include "ca_logic.h"


#include "ca_time.h"


#include "ca_cpu_architecture.h"


#include "ca_libc.h"


#include "ca_count.h"
#include "ca_index.h"
#include "ca_number.h"
#include "ca_keep_true.h"


#include "ca_debug.h"


#include "ca_printf.h"
#include "ca_sprintf.h"
#include "ca_str.h"



#include "ca_heap.h"
#include "ca/simple_graphics/simple_graphics_first_phase.h"
#include "ca_memory.h"

#include "ca_math.h"

#include "ca_geometric_types.h"


#include "ca_verisimple_string.h"
#include "ca_verisimple_wstring.h"
#include "ca_vsstringtow.h"
#include "ca_wstringtovss.h"


#include "ca_ca.h"
#include "ca_smart_pointer1.h"
#include "ca_smart_pointer2.h"



#include "ca_dir.h"
#include "ca_md5.h"

#include "ca_simple_obj.h"

#include "ca_template.h"
#include "ca_simple_array.h"
#include "ca_simple_map.h"
#include "ca_simple_list.h"
#include "ca_stra.h"

#include "ca_xmlite.h"
#include "ca_file.h"

#include "ca_launcher.h"


#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#define BSD_STYLE_SOCKETS
#include "ca_small_ipca_channel.h"

#endif


#include "ca_mutex.h"
#include "ca_simple_event.h"

#include "ca_single_lock.h"

#include "ca_simple_critical_section.h"

#include "ca_library.h"

#include "ca_simple_memory.h"

#include "ca_file_watcher.h"
#include "ca_file_watcher_impl.h"



/*#ifndef WINDOWS
#define VK_TAB 1
#define VK_RETURN 2
#define VK_BACK 3
#define VK_DELETE 6
#define VK_SPACE 9
#endif*/
#include "ca_window_graphics.h"

#include "ca/os/os.h"

#include "ca/cross/cross.h"


#include "ca_conv.h"
#include "ca_string_to_integer.h"
#include "ca_integer_to_string.h"


#include "ca/simple_graphics/simple_graphics_second_phase.h"


#include "ca_simple_shell_launcher.h"



#include "ca_file_watcher_thread.h"
#include "ca_file_watcher_listener_thread.h"
#include "ca_async.h"


#include "ca_base64.h"


#include "ca/hotplugin/hotplugin.h"
#include "ca/::simple_ui::interaction/::simple_ui::interaction.h"
#include "ca/crypt/crypt.h"
#include "ca/spa/spa.h"

#include "ca/bsdiff/bsdiff.h"




#include "ca_message_loop.h"

#include "ca_url.h"
#include "ca_net.h"

#include "ca_international.h"



#define return_(y, x) {y = x; return;}


extern "C"
{


   int32_t _c_lock_is_active(const char * pszName);
   int32_t _c_lock(const char * pszName, void ** pdata);
   int32_t _c_unlock(void ** pdata);


}


CLASS_DECL_BOOT string _ca_get_file_name(const char * psz, bool bCreate = false, int32_t * pfd = NULL);



//#ifndef METROWIN
//#include <openssl/ssl.h>
//#endif



#include "ca_user.h"

#include "zlib/zlib.h"

#include "ca_simple_app.h"


