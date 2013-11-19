#pragma once


#include "nodeapp/operational_system/operational_system.h"




class string;
class istring;
class var;
class property;
class property_set;
class object;
class type;
class base_application;
class base_system;
class dump_context;
class string_interface;
class id_space;
class type;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class critical_section;
class allocatorsp;
class application_signal_details;
class var_array;
class pair_set_interface;
class str_str_interface;
class command_thread;
class thread;





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

   class application;
   class session;
   class system;
   //class cube;


} // namespace plane



namespace file
{


   class stream_buffer;
   class input_stream;
   class output_stream;
   class serializable;


} // namespace file


namespace user
{


   class base_interaction;
   class create_context;
   class view;
   class printer;


} // namespace user


enum e_extract
{
   extract_none,
   extract_first,
   extract_all,
};



class random_access_iterator { public: };





#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource));


#define sp(TYPE) smart_pointer < TYPE >

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





CLASS_DECL_BASE base_application * get_thread_app();

#include "base_definition.h"

#include "base_new.h"

#include "base_lparam.h"
#include "base_muldiv64.h"

#include "base_auto_pointer.h"

#include "base_smart_pointer1.h"
#include "base_root.h"
#include "base_smart_pointer2.h"


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







#include "base_template.h"

#include "base/primitive/comparison/comparison_md5.h"

#include "base/net/net.h"

#include "base_conv.h"



#include "base_core.h"

#include "base/primitive/primitive_request_interface.h"


#include "base/multithreading/multithreading_wait_result.h"
#include "base/multithreading/multithreading_waitable.h"



#include "base/primitive/primitive_object.h"


#include "base/primitive/collection/collection_decl.h"
#include "base/primitive/collection/collection_array_decl.h"
#include "base/primitive/collection/collection_raw_array_decl.h"
#include "base/primitive/collection/collection_lemon_array_decl.h"


#include "base_fixed_alloc.h"



#include "base_allocate.h"
#include "base_plex.h"


#include "base/primitive/primitive_id.h"


#include "base/str/str.h"
#include "base/exception/exception.h"
#include "base_common.h"


#include "base/primitive/datetime/datetime_time.h"




#include "base/filesystem/filesystem.h"




#include "base/primitive/geometry/geometry.h"


#include "base/primitive/comparison/comparison.h"


#include "base/primitive/collection/collection.h"


#include "base/filesystem/file/file_string_buffer.h"


#include "base/primitive/primitive_var2.h"


#include "base/primitive/primitive_id_space.h"



#include "base_enum.h"


#include "base/multithreading/multithreading.h"


#include "base_draw2d.h"






#include "base/user/user_base_document.h"
#include "base/user/user_base_document_template.h"
#include "base/user/user_base_interaction.h"
#include "base/user/user_create_context.h"


#if defined(LINUX)

#include "base/ansios/ansios.h"
#include "base/linux/linux_user_impl.h"

#elif defined(METROWIN)

#include "base/metrowin/metrowin.h"

#elif defined(MACOS)

#include "base/ansios/ansios.h"
#include "base/macos/macos.h"
#include "base/macos/macos_window.h"

#elif defined(WINDOWS)

#include "base/os/windows/windows.h"

#endif







CLASS_DECL_BASE string get_system_error_message(uint32_t dwError);


#include "base_plex_heap.h"

#include "base/primitive/primitive_type.h"


#include "graphics/graphics.h"
#include "user/user_keyboard_focus.h"
#include "user/user_mouse_focus.h"
#include "user/user_elemental.h"
#include "base_flags.h"
#include "primitive/primitive_check.h"
#include "user/user_check_interface.h"
#include "base_command.h"
#include "graphics/visual/visual_const.h"
#include "base/user/user_key_enum.h"
#include "base_message.h"
#include "base_command_target.h"
#include "user/user_text_interface.h"
#include "user/user_draw_interface.h"
#include "user/user_window_util.h"
#include "user/user_window_interface.h"
#include "user/user_buffer.h"
#include "core/core/core_keeper.h"
#include "base/filesystem/file/file_stream2.h"
#include "user/user_interaction.h"
#include "user/user_virtual_user_interface.h"
#include "user/user_window.h"
#include "base_live_object.h"
#include "base_live_signal.h"
#include "multithreading/multithreading_thread.h"
#include "multithreading/multithreading_simple_thread.h"
#include "multithreading/multithreading_go_thread.h"
#include "multithreading/multithreading_signal_thread.h"


#include "base/base_log.h"
#include "base/base_trace.h"


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


#include "base/str/str_international2.h"

#include "net/http/http_output_stream.h"

#include "base_departament.h"
#include "base_departament_container.h"

#include "base/net/sockets/sockets.h"

#include "base/programming/javascript/javascript.h"

#include "net/http/http_http.h"
#include "net/http/http_application.h"
#include "net/http/http_system.h"
#include "net/http/http_get_socket.h"

#include "base_message_queue_listener.h"
#include "base_message_queue.h"
#include "base/user/userpresence/userpresence.h"
#include "base/primitive/primitive_interlocked_long.h"
#include "base/primitive/primitive_interlocked_long_pulse.h"
#include "base/primitive/primitive_factory.h"
#include "base/primitive/primitive_data.h"
#include "base/primitive/primitive_data_listener.h"
#include "base/primitive/primitive_data_container.h"
#include "base/primitive/primitive_edit.h"
#include "base/filesystem/fs/fs.h"
#include "base/user/fontopus/fontopus.h"

#include "base/filesystem/file/file_application.h"
#include "base/filesystem/file/file_dir_application.h"

#include "base/primitive/math/math_math_rng.h"
#include "base/primitive/math/math_math.h"
#include "base/primitive/geometry/geometry_geometry.h"


#include "base/xml/xml.h"

#include "user/user_window_map.h"

#include "user/user_keyboard_layout.h"
#include "user/user_keyboard.h"
#include "user/user_user.h"

#include "base_main_init_data.h"

#include "base_application.h"


#include "base_session.h"

#include "base/net/net_url_departament.h"
#include "base/net/net_url_domain.h"




#include "base/primitive/primitive_application_bias.h"
#include "base/exception/exception_engine.h"

#include "base_fixed_alloc_impl.h"
#include "base_plex_heap_impl.h"
#include "base/primitive/primitive_command_line.h"
#include "base/primitive/primitive_create_context.h"
#include "base/primitive/primitive_command.h"
#include "base/primitive/primitive_request_signal.h"








#include "base/primitive/primitive_command_thread.h"





#include "base/graphics/visual/visual.h"


#include "base/filesystem/file/file_system.h"
#include "base/filesystem/file/file_dir_system.h"

#include "base/filesystem/file/file_buffered_buffer.h"


#include "compress/compress.h"


#include "base_machine_event_data.h"
#include "base_machine_event.h"
#include "base_machine_event_central.h"

#include "crypto/crypto.h"


#include "primitive/datetime/datetime_value.h"
#include "primitive/datetime/datetime_departament.h"


#include "user/user_window_draw.h"

#include "base/str/str_international_locale_schema.h"

#include "base/user/user_str.h"

#include "base_system.h"


#include "base_system_str.h"



#include "base/os/os.h"


#include "base/os/os_process.h"










#include "base/spa/spa_trace.h"


#define new BASE_NEW


#include "base_system_trace.h"


#include "base/multithreading/multithreading.inl"


#include "base/str/str.inl"

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



#ifdef WINDOWSEX
#define _DRAW2D_GDIPLUS_STATIC
#include "nodeapp/appseed/draw2d_gdiplus/draw2d_gdiplus.h"
#undef _DRAW2D_GDIPLUS_STATIC
#endif


#define AppUser(pbaseapp) (*App(pbaseapp).m_pfontopus->get_user())
#define ApplicationUser (AppUser(m_pbaseapp))
#define Sess(pbaseapp) (*pbaseapp->m_pbasesession)
#define Session (Sess(this->m_pbaseapp))



#include "base/net/http/http.h"
#include "base_microtimer.h"


#include "user/user.h"
#include "user/user_control_event.h"
#include "base_cregexp.h"
#include "base_cregexp_util.h"




