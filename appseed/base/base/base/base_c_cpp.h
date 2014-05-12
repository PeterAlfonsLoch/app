#pragma once


#include "nodeapp/operational_system/operational_system.h"




template < class T >
class smart_pointer;


#define sp(TYPE) smart_pointer < TYPE >


class string;
class istring;
class var;
class property;
class property_set;
class object;
class type;

namespace base
{

   class application;
   class system;
   class application_signal_details;

} // namespace base


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
class command_thread;
class thread;
class application;


namespace visual
{


   class icon;


} // namespace visual

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


namespace draw2d
{


   class graphics;


} // namespace draw2d


class base_command;

namespace file
{


   class stream_buffer;
   class input_stream;
   class output_stream;
   class serializable;


} // namespace file

class machine_event_data;
namespace html
{
   class html;
} // namespace html



class window;

typedef sp(window) window_sp;

namespace user
{


   class interaction;
   class control_event;
   class create_context;
   class impact;
   class printer;
   class user;
   class object;
   class frame_window;





} // namespace user

class message_queue_listener;
class image_list;
class base_session;

#ifndef WINDOWS
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

namespace core
{


   class live_object;

#if defined METROWIN && defined(__cplusplus_winrt)

   interface class system_window
   {
      virtual Windows::Foundation::Rect get_window_rect() = 0;
      virtual Windows::Foundation::Point get_cursor_pos() = 0;
   };

#endif

} // namespace core


namespace data
{


   class item;


} // namespace data


namespace xml
{

   class node;

} // namespace xml


namespace user
{

   class place_holder;
   class menu_base_item;

#if defined METROWIN && defined(__cplusplus_winrt)

    class CLASS_DECL_BASE native_window_initialize
   {
   public:


      Platform::Agile<Windows::UI::Core::CoreWindow> window;
      ::core::system_window ^ pwindow;


   };
    
#elif defined(APPLE_IOS)
    
    class CLASS_DECL_BASE native_window_initialize
    {
    public:
        
        RECT   m_rect;
        
    };

#else

   class native_window_initialize;

#endif


   class control_event;
   class frame_window;
   class menu_base;





   CLASS_DECL_BASE bool is_descendant(::user::interaction * puiParent, ::user::interaction * puiChild);


} // namespace user




namespace install
{

   class install;

} // namespace install

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







#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));


#define CaSys(pca) (*pca->m_pbaseapp->m_pbasesystem)
#define Sys(pbaseapp) (*pbaseapp->m_pbasesystem)
#define System (Sys(this->m_pbaseapp))
#define threadSystem (Sys(get_thread_app()))

//#define Sess(papp) (*papp->m_pplaneapp->m_psession)
//#define Session (Sess(this->m_pbaseapp))

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


typedef  void(*PFN_ca2_factory_exchange)(sp(::base::application) papp);



namespace core
{

   class copydesk;

   typedef smart_pointer < copydesk > copydesk_sp;


} // namespace core

CLASS_DECL_BASE ::base::application * get_thread_app();

#include "base_definition.h"

#include "base_action_source.h"

#include "base_new.h"

#include "base_lparam.h"
#include "base_muldiv64.h"

#include "base_auto_pointer.h"

#include "base_smart_pointer1.h"
#include "base_root.h"
#include "base_smart_pointer2.h"


#include "base_keep_true.h"


namespace file
{


   typedef sp(stream_buffer) buffer_sp;


} // namespace file


#include "base/primitive/primitive_logic.h"



#include "base/primitive/math/math_static_numeric_info.h"
#include "base/primitive/math/math_numeric_info.h"
#include "base/primitive/math/math_number.h"


#include "base/primitive/datetime/datetime_duration.h"


#include "base/base/base_element.h"

#include "base_debug.h"






#include "base_class.h"

#include "base/primitive/comparison/comparison_md5.h"

#include "base/net/net.h"

#include "base_conv.h"

#include "base_core.h"

#include "base_library.h"

#include "base/primitive/primitive_request_interface.h"

#include "base/multithreading/multithreading_wait_result.h"

#include "base/multithreading/multithreading_waitable.h"

#include "base/primitive/primitive_object.h"


#include "base/primitive/collection/collection_decl.h"
#include "base/primitive/collection/collection_array_decl.h"
#include "base/primitive/collection/collection_raw_array_decl.h"
#include "base/primitive/collection/collection_lemon_array_decl.h"
#include "base/primitive/collection/collection_smart_pointer_array.h"


#include "base_action_context.h"



#include "base_fixed_alloc.h"



#include "base_allocate.h"
#include "base_plex.h"


#include "base/primitive/primitive_id.h"


#include "base/primitive/str/str.h"
#include "base/exception/exception.h"
#include "base_common.h"




#include "base/primitive/datetime/datetime_time.h"




#include "base/filesystem/filesystem.h"





#include "base/primitive/geometry/geometry.h"


#include "base/primitive/comparison/comparison.h"


#include "base/primitive/collection/collection.h"


#include "base/filesystem/file/file_string_buffer.h"


#include "base/filesystem/file/file_set.h"


#include "base/primitive/primitive_var2.h"


#include "base/primitive/primitive_id_space.h"


#include "base/primitive/math/math_scalar_enum.h"


#include "base/primitive/math/math_scalar.h"


#include "base_progress.h"


#include "base_enum.h"


#include "base/multithreading/multithreading.h"


#include "base/base/geoip/geoip.h"



#include "base_draw2d.h"








//#include "base/user/user_create_context.h"


#if defined(LINUX)

#include "base/os/ansios/ansios.h"
#include "base/os/linux/linux_user_impl.h"

#elif defined(METROWIN)

#include "base/os/metrowin/metrowin.h"
#include "base/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "base/os/ansios/ansios.h"
#include "base/os/macos/macos.h"
#include "base/os/macos/macos_window.h"

#elif defined(ANDROID)

#include "base/os/ansios/ansios.h"
#include "base/os/android/android.h"

#elif defined(WINDOWS)

#include "base/os/windows/windows.h"

#elif defined(APPLE_IOS)

#include "base/os/ansios/ansios.h"
#include "base/os/ios/ios.h"
#include "base/os/ios/ios_windowing.h"

#elif defined(SOLARIS)

#include "base/os/ansios/ansios.h"
#include "base/os/solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif







CLASS_DECL_BASE string get_system_error_message(uint32_t dwError);


#include "base_plex_heap.h"

#include "base/primitive/primitive_type.h"


#include "graphics/graphics.h"
#include "user/user/user_enum.h"
#include "user/user/user_keyboard_focus.h"
#include "user/user/user_mouse_focus.h"
#include "user/user/user_elemental.h"
#include "base_flags.h"
#include "primitive/primitive_check.h"
#include "user/user/user_check_interface.h"
#include "base_command.h"
#include "graphics/visual/visual_const.h"
#include "user/user/user_key_enum.h"
#include "base/base/message/message.h"
#include "base_command_target.h"
#include "user/user/user_text_interface.h"
#include "user/user/user_draw_interface.h"
#include "user/user/user_window_util.h"
#include "user/user/user_window_interface.h"
#include "user/user/user_buffer.h"
#include "base_keeper.h"
#include "base/filesystem/file/file_stream2.h"
#include "user/user/user_interaction.h"
#include "user/user/user_virtual_user_interface.h"
#include "user/user/user_window.h"
#include "user/user/user_control_bar.h"
#include "user/user/user_wait_cursor.h"
#include "user/user/user_frame_window.h"
#include "user/user/user_server.h"
#include "user/user/user_impact_system.h"
#include "primitive/primitive_interlocked_long.h"
#include "primitive/primitive_interlocked_long_pulse.h"
#include "primitive/primitive_data.h"
#include "primitive/primitive_data_listener.h"
#include "primitive/primitive_data_container.h"
#include "base/primitive/primitive_edit.h"
#include "base_departament.h"
#include "base_departament_container.h"
#include "base/xml/xml.h"
#include "base/user/simple_ui/simple_ui.h"
#include "base/database/database.h"
#include "user/user/user_object.h"
#include "user/user/user_impact.h"
#include "base_live_object.h"
#include "base_live_signal.h"
#include "multithreading/multithreading_thread.h"
#include "multithreading/multithreading_simple_thread.h"
#include "multithreading/multithreading_go_thread.h"
#include "multithreading/multithreading_signal_thread.h"


#include "primitive/primitive_job.h"


#include "base_log.h"
#include "base_trace.h"


#include "base/net/net.h"


#include "base/primitive/primitive_memory_base.h"
#include "base/primitive/primitive_memory.h"
#include "base/primitive/primitive_shared_memory.h"
#include "base/primitive/primitive_virtual_memory.h"
#include "base/primitive/primitive_memory_container.h"


#include "base/filesystem/file/file_memory_buffer.h"
#include "base/filesystem/file/file_byte_stream_memory_buffer.h"
#include "base/filesystem/file/file_plain_text_stream_memory_buffer.h"
#include "base/filesystem/file/file_circular_buffer.h"


#include "base/primitive/str/str_international2.h"

#include "net/http/http_output_stream.h"


#if defined(METROWIN)

#include "app/appseed/base/base/os/metrowin/metrowin_sockets.h"

#endif


#include "base/net/sockets/sockets.h"

#include "base/programming/javascript/javascript.h"

#include "net/http/http_http.h"
#include "net/http/http_application.h"
#include "net/http/http_system.h"
#include "net/http/http_get_socket.h"

#include "base_message_queue_listener.h"
#include "base_message_queue.h"
#include "base/user/userpresence/userpresence.h"
#include "base/primitive/primitive_factory.h"
#include "base/filesystem/fs/fs.h"
#include "base/user/fontopus/fontopus.h"

#include "base/filesystem/file/file_application.h"
#include "base/filesystem/file/file_dir_application.h"

#include "base/primitive/math/math_math_rng.h"
#include "base/primitive/math/math_math.h"
#include "base/primitive/geometry/geometry_geometry.h"




#include "user/user/user_window_map.h"

#include "user/user/user_keyboard_layout.h"
#include "user/user/user_keyboard.h"
#include "user/user/user_user.h"

#include "base_main_init_data.h"

#include "base_savings.h"



#include "base_application.h"

#include "base_application_signal_details.h"


#include "base_session.h"

#include "base/net/net_url_departament.h"
#include "base/net/net_url_domain.h"




#include "base/primitive/primitive_application_bias.h"
#include "base/exception/exception_engine.h"

#include "base_fixed_alloc_impl.h"
#include "base_plex_heap_impl.h"
#include "base/primitive/primitive_command_line.h"
#include "base/primitive/primitive_command.h"
#include "user/user/user_create_context.h"
#include "base/primitive/primitive_create_context.h"
#include "base/primitive/primitive_request_signal.h"








#include "base/primitive/primitive_command_thread.h"





//#include "base/graphics/visual/visual.h"


#include "base/filesystem/file/file_system.h"
#include "base/filesystem/file/file_dir_system.h"

#include "base/filesystem/file/file_buffered_buffer.h"


#include "base/compress/compress.h"


#include "base_machine_event_data.h"
#include "base_machine_event.h"
#include "base_machine_event_central.h"

#include "base/crypto/crypto.h"


#include "primitive/datetime/datetime_value.h"
#include "primitive/datetime/datetime_departament.h"


#include "user/user/user_window_draw.h"

#include "base/primitive/str/str_international_locale_schema.h"

#include "user/user/user_str.h"

#include "base_id_pool.h"


#include "base_launcher.h"
#ifndef METROWIN
#include "base_small_ipc_channel.h"
#endif





#include "base_core_os.h"

#include "base_system.h"

#include "base/hotplugin/hotplugin.h"

#include "base/install/install.h"

#include "base_system_str.h"

#include "base/os/os_process.h"










//#include "base/install/install_trace.h"


#define new BASE_NEW


#include "base_system_trace.h"


#include "user/user/user_place_holder.h"
#include "user/user/user_place_holder_container.h"
#include "user/user/user_view_creator_data.h"
#include "user/user/user_view_container.h"
#include "user/user/user_view_creator.h"


#include "base/multithreading/multithreading.inl"


#include "base/primitive/str/str.inl"

#include "base/base/base.inl"


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

#include "base/os/cross/windows/windows_thread_impl.h"

#endif





#include "base/primitive/collection/collection_array_impl.inl"
#include "base/primitive/collection/collection_raw_array_impl.inl"
#include "base/primitive/collection/collection_sort_array_impl.inl"
#include "base/primitive/collection/collection_lemon_array_impl.inl"

#include "base/primitive/collection/collection_list_impl.inl"
#include "base/primitive/collection/collection_map_impl.inl"

#include "base/primitive/collection/collection_sort_map_impl.inl"

#include "base/primitive/collection/collection_fifo_map_impl.inl"



#include "base/primitive/primitive_factory_impl.inl"





#include "base_system_smart_pointer.inl"
#include "base_system_object.inl"
#include "base_system_id.inl"
#include "base_system_factory.inl"
#include "base_system_primitive_var.inl"
#include "base_system_xml.inl"



#include "base_core_copydesk.h"


#include "base_core_os.h"


#define AppUser(pbaseapp) (*pbaseapp->m_pbasesession->m_pfontopus->get_user())
#define ApplicationUser (AppUser(m_pbaseapp))
#define Sess(pbaseapp) (*pbaseapp->m_pbasesession)
#define Session (Sess(this->m_pbaseapp))



#include "base/net/http/http.h"
#include "base_microtimer.h"


#include "base/user/user/user.h"
#include "user/user/user_control_event.h"
#include "base_cregexp.h"
#include "base_cregexp_util.h"








#include "base/vms/vms.h"


#include "base_cpu_architecture.h"


#include "base_libc.h"


#include "base_number.h"


#include "base_debug.h"


#include "base_printf.h"
#include "base_sprintf.h"



#include "base_math.h"







#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#ifndef BSD_STYLE_SOCKETS
#define BSD_STYLE_SOCKETS 1
#endif
   //#include "base_small_ipc_channel.h"

#endif



#include "base_file_watcher.h"
#include "base_file_watcher_impl.h"


#include "base_os.h"


#include "base/multithreading/multithreading_data.h"


#include "base_simple_shell_launcher.h"


#include "base_file_watcher_thread.h"
#include "base_file_watcher_listener_thread.h"
#include "base_async.h"


   //#include "base/hotplugin/hotplugin.h"




#include "base_message_loop.h"

#include "base_url.h"

#include "base_international.h"



#define return_(y, x) {y = x; return;}


   extern "C"
   {


      int32_t _c_lock_is_active(const char * pszName);
      int32_t _c_lock(const char * pszName, void ** pdata);
      int32_t _c_unlock(void ** pdata);


   }


   CLASS_DECL_BASE string _ca_get_file_name(const char * psz, bool bCreate = false, int32_t * pfd = NULL);

   CLASS_DECL_BASE string get_system_error_message(uint32_t dwError);


#include "base_simple_app.h"




#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)


template < class T >
bool ::file::system::output(sp(::base::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(pszOutput, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::output_stream ostream(fileOut);

   return (p->*lpfnOuput)(ostream, lpszSource);

}


template < class T >
bool ::file::system::output(sp(::base::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, ::file::input_stream &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   string strDownloading = pszOutput;

   strDownloading += ".downloading";

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(strDownloading, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::binary_buffer_sp fileIn = App(papp).file().get_file(lpszInput, ::file::type_binary | ::file::mode_read);

   if(fileIn.is_null())
      return false;

   {

      ::file::output_stream ostream(fileOut);

      ::file::input_stream istream(fileIn);

      if(!(p->*lpfnOuput)(ostream, istream))
         return false;

   }

   try
   {

      fileOut->close();

   }
   catch(...)
   {

   }


   try
   {

      fileIn->close();

   }
   catch(...)
   {

   }

   if(::rename(strDownloading, pszOutput) != 0)
   {
      del(strDownloading);
      return false;
   }

   return true;

}

#endif // defined LINUX











#include "app/appseed/base/base/node/node.h"
