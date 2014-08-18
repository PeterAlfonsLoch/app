#pragma once

#pragma warning(disable: 4251)

#include "nodeapp/operational_system/operational_system.h"




template < class T >
class smart_pointer;


#define sp(TYPE) ::smart_pointer < TYPE >


class string;
class istring;
class var;
class property;
class property_set;
class object;
class type;

namespace axis
{

   class application;
   class system;
   class application_signal_details;

   class command;



} // namespace axis


class dump_context;
class string_interface;
class id_space;
class type;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class critical_section;
class allocatorsp;
class var_array;
class pair_set_interface;
class str_str_interface;
class cmd_ui;
class critical_section;
class mutex;
class string_array;
class string;
class id;



namespace primitive
{

   class memory;

} // namespace primitive

namespace plane
{

   class session;
   class system;
   //class cube;


} // namespace plane

class cmd_ui;





namespace html
{
   class html;
} // namespace html




namespace axis
{

   template < typename T >
   inline void del(T * & p)
   {
      if(p != NULL)
      {
         delete p;
         p = NULL;
      }
   }

} // namespace axis



class message_queue_listener;
class image_list;



#ifndef WINDOWSEX
typedef void * HDWP;
#endif // WINDOWS

// special struct for WM_SIZEPARENT
struct __SIZEPARENTPARAMS
{

   HDWP hDWP;       // handle for DeferWindowPos
   RECT rect;       // parent client rectangle (trim as appropriate)
   SIZE sizeTotal;  // total size on each side as layout proceeds
   bool bStretch;   // should stretch to fill all space

};


typedef struct tagRECTD RECTD;


namespace axis
{

   class live_object;

#if defined METROWIN && defined(__cplusplus_winrt)

   interface class system_window
   {
      
      virtual Windows::Foundation::Rect get_window_rect() = 0;
      virtual Windows::Foundation::Point get_cursor_pos() = 0;


    
   };

   CLASS_DECL_AXIS bool get_window_rect(system_window ^ pwindow,RECTD * lprect);
   CLASS_DECL_AXIS bool get_window_rect(system_window ^ pwindow,LPRECT lprect);

#endif



   namespace trace
   {

      class trace;

   }

   class session;

} // namespace axis


// only usable from core and core dependants
namespace core
{

   class application;
   class platform;
   class system;

}


namespace data
{


   class item;


} // namespace data


namespace xml
{

   class node;

} // namespace xml




enum e_extract
{

   extract_none,
   extract_first,
   extract_all

};


namespace str
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace str




namespace draw2d
{


   class graphics;


} // namespace draw2d


class random_access_iterator { public: };


#ifdef WINDOWSEX

typedef HANDLE HTHREAD;

#else

typedef hthread * HTHREAD;

#endif


class event;


class thread;




class thread;


typedef smart_pointer < thread > thread_sp;


class thread_impl;


typedef smart_pointer < thread_impl > thread_impl_sp;




#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));


#define CaSys(pca) (*pca->m_pbaseapp->m_pbasesystem)
#define Sys(pbaseapp) (*pbaseapp->m_pbasesystem)
#define System (Sys(this->m_pbaseapp))
#define threadSystem (Sys(get_thread_app()))


#undef App
#define App(pbaseapp) (*pbaseapp)
#define Application (App(m_pbaseapp))


// return - result - if not ok
#ifndef RINOK
#define RINOK(x) { int32_t __result__ = (x); if (__result__ != 0) return __result__; }
#endif

// throw - exception - result exception - if not ok
#ifndef TINOK
#define TINOK(e, x) { int32_t __result__ = (x); if (__result__ != 0) throw new e(get_app(), __result__); }
#endif


#ifdef WINDOWS
#pragma warning(disable: 4251)  // using non-exported as public in exported
#endif


#ifndef WINDOWSEX

typedef void * HDWP;

#endif


typedef  void(*PFN_ca2_factory_exchange)(sp(::axis::application) papp);







CLASS_DECL_AXIS ::axis::application * get_thread_app();



#include "axis_definition.h"

#include "axis_action_source.h"

#include "axis_new.h"

#include "axis_lparam.h"
#include "axis_muldiv64.h"

#include "axis_auto_pointer.h"

#include "axis_smart_pointer1.h"
#include "axis_root.h"
#include "axis_smart_pointer2.h"


#include "axis_keep_true.h"



#include "axis/primitive/primitive_logic.h"



#include "axis/primitive/math/math_static_numeric_info.h"
#include "axis/primitive/math/math_numeric_info.h"
#include "axis/primitive/math/math_number.h"


#include "axis/primitive/datetime/datetime_duration.h"


#include "axis/axis/axis_element.h"

#include "axis_debug.h"




#include "axis_class.h"

#include "axis/primitive/comparison/comparison_md5.h"

#include "axis/net/net.h"

#include "axis_conv.h"

#include "axis_core.h"

#include "axis/multithreading/multithreading_wait_result.h"

#include "axis/multithreading/multithreading_waitable.h"

#include "axis/primitive/primitive_object.h"




#include "axis/primitive/collection/collection_decl.h"
#include "axis/primitive/collection/collection_raw_array_decl.h"
#include "axis/primitive/collection/collection_lemon_array_decl.h"
#include "axis/primitive/collection/collection_smart_pointer_array.h"


#include "axis_action_context.h"



#include "axis_fixed_alloc.h"



#include "axis_allocate.h"
#include "axis_plex.h"


#include "axis/primitive/primitive_id.h"


#include "axis/primitive/str/str.h"
#include "axis/exception/exception.h"
#include "axis_common.h"


#include "axis_library.h"


#include "axis_dir.h"



#include "axis/primitive/datetime/datetime_time.h"





#include "axis/primitive/geometry/geometry.h"


#include "axis/primitive/comparison/comparison.h"


#include "axis/primitive/collection/collection.h"


#include "axis/primitive/primitive_id_space.h"


#include "axis/primitive/math/math_scalar_enum.h"


#include "axis/primitive/math/math_scalar.h"


#include "axis_progress.h"


#include "axis_enum.h"


#include "axis/multithreading/multithreading.h"



#include "axis_gudo.h"



#include "axis_file.h"

//#include "axis/user/user_create_context.h"


#if defined(LINUX)

#include "axis/os/ansios/ansios.h"
#include "axis/os/linux/linux_user_impl.h"

#elif defined(METROWIN)

#include "axis/os/metrowin/metrowin.h"
#include "axis/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/macos/macos.h"
#include "axis/os/macos/macos_windowing.h"

#elif defined(ANDROID)

#include "axis/os/ansios/ansios.h"
#include "axis/os/android/android.h"

#elif defined(WINDOWS)

#include "axis/os/windows/windows.h"

#elif defined(APPLE_IOS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/ios/ios.h"
#include "axis/os/ios/ios_windowing.h"

#elif defined(SOLARIS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif







CLASS_DECL_AXIS string get_system_error_message(uint32_t dwError);


#include "axis_plex_heap.h"

#include "axis/primitive/primitive_type.h"


#include "primitive/primitive_check.h"
#include "axis_keep.h"



#include "primitive/primitive_interlocked_long.h"
#include "primitive/primitive_interlocked_long_pulse.h"



#include "axis_log.h"
#include "axis_trace.h"


#include "axis/net/net.h"


#include "axis/primitive/primitive_memory_base.h"
#include "axis/primitive/primitive_memory.h"
#include "axis/primitive/primitive_shared_memory.h"
#include "axis/primitive/primitive_virtual_memory.h"
#include "axis/primitive/primitive_memory_container.h"




#include "axis/primitive/str/str_international2.h"




#include "axis/primitive/primitive_factory.h"





#include "axis_main_init_data.h"

#include "axis_live_object.h"
#include "axis_application_interface.h"
#include "axis_application.h"


#include "axis_gudo_application.h"


#include "axis_session_interface.h"
#include "axis_session.h"

#include "axis/net/net_url_domain.h"




#include "axis/exception/exception_engine.h"

#include "axis_fixed_alloc_impl.h"
#include "axis_plex_heap_impl.h"












#include "primitive/datetime/datetime_value.h"


#include "axis_id_pool.h"


#include "axis_launcher.h"
#ifndef METROWIN
#include "axis_small_ipc_channel.h"
#endif


#include "axis_cregexp.h"
#include "axis_cregexp_util.h"


#include "axis_system.h"

#include "axis_system_str.h"

#include "axis/os/os_process.h"

#define new AXIS_NEW

#include "axis_system_trace.h"

#include "axis/multithreading/multithreading.inl"

#include "axis/primitive/str/str.inl"

#include "axis/axis/axis.inl"

namespace numeric_info
{


   template < typename T >
   inline T get_maximum_value()
   {
      throw not_implemented(get_thread_app());
   }

   template < typename T >
   inline T get_minimum_value()
   {
      throw not_implemented(get_thread_app());
   }
   template < typename T >
   inline T get_null_value()
   {
      return 0;
   }
   template < typename T >
   inline T get_unitary_value()
   {
      return 1;
   }

   template < typename T >
   inline T get_allset_value()
   {
      T t;
      memset(&t, 0xff, sizeof(T));
      return t;
   }

   template < typename T >
   inline bool is_signed()
   {
      return ((T) -1) < 0;
   }

   template < typename T >
   inline bool is_integer()
   {
      // guess, as float and double is implemented
      return true;
   }


   template < typename T >
   inline string json(const T & value)
   {
      return ::str::from(value);
   }

} // namespace numeric_info




#ifdef VARIADIC_TEMPLATE

   template<typename T, typename... Args>
   inline void string_format::printf(const char * & s, const T & value, Args... args)
   {

      while (*s)
      {

         if (*s == '%' && *(++s) != '%')
         {

            defer_get_additional_argument(s, value, args...);

            return;

         }

         append(*s++);

      }

      throw simple_exception(get_thread_app(), "extra arguments provided to printf");


   }



   inline void string_format::printf(const char * & s)
   {

      while (*s)
      {

         if(*s == '%' && *(++s) != '%')
            throw simple_exception(get_thread_app(), "invalid format string: missing arguments");

         append(*s++);

      }

      (m_pprinter->*m_pfnPrinter)(m_pvoidPrinter, m_pszBuffer);

   }

#endif





#ifndef WINDOWSEX

#include "axis/os/cross/windows/windows_thread_impl.h"

#endif





#include "axis/primitive/collection/collection_raw_array_impl.inl"
#include "axis/primitive/collection/collection_lemon_array_impl.inl"

#include "axis/primitive/collection/collection_list_impl.inl"
#include "axis/primitive/collection/collection_map_impl.inl"




#include "axis/primitive/primitive_factory_impl.inl"





#include "axis_system_smart_pointer.inl"
#include "axis_system_object.inl"
#include "axis_system_id.inl"
#include "axis_system_factory.inl"





#define AppUser(pbaseapp) (*pbaseapp->m_pbasesession->fontopus()->get_user())
#define ApplicationUser (AppUser(m_pbaseapp))



#include "axis_microtimer.h"








#include "axis/vms/vms.h"


#include "axis_cpu_architecture.h"


#include "axis_libc.h"


#include "axis_number.h"


#include "axis_debug.h"


#include "axis_printf.h"
#include "axis_sprintf.h"



#include "axis_math.h"







#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#ifndef BSD_STYLE_SOCKETS
#define BSD_STYLE_SOCKETS 1
#endif
   //#include "axis_small_ipc_channel.h"

#endif




#include "axis/multithreading/multithreading_data.h"


#include "axis_simple_shell_launcher.h"


#include "axis_async.h"


   //#include "axis/hotplugin/hotplugin.h"




#include "axis_message_loop.h"

#include "axis_url.h"

#include "axis_international.h"

#include "axis_static_start.h"



#define return_(y, x) {y = x; return;}


   extern "C"
   {


      int32_t _c_lock_is_active(const char * pszName);
      int32_t _c_lock(const char * pszName, void ** pdata);
      int32_t _c_unlock(void ** pdata);


   }


   CLASS_DECL_AXIS string _ca_get_file_name(const char * psz, bool bCreate = false, int32_t * pfd = NULL);

   CLASS_DECL_AXIS string get_system_error_message(uint32_t dwError);



#include "primitive/collection/collection_raw_array_impl.inl"