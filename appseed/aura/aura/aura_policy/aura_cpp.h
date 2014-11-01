/////////////////////////////////////////////////////////////////////////////////////////
//
//   All Pure and Aural ca2 and God and Gods and Goddssesses and devils's blessings
//
//   C++
//
//   C => in ca2 scope
//
//   Thank you God for C++!!
//

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

namespace aura
{

   class application;
   class system;
   class application_signal_details;
   class platform_interface;

   class command;



} // namespace aura


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
class command_target;
class cmd_ui;
class critical_section;
class mutex;
class stringa;
class string;
class id;

namespace colorertake5
{

   class ParserFactory;


} // namespace colorertake5

namespace visual
{


   class icon;
   class cursor;


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



namespace aura
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

} // namespace aura

namespace aura
{

   class message_queue_listener;

}


class image_list;

namespace user
{


   class interaction;
   class interaction_impl;
   class document;
   class frame_window;
   class create_struct;


} // namespace user



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


namespace aura
{

   class live_object;

#if defined METROWIN && defined(__cplusplus_winrt)

   interface class system_window
   {

      virtual Windows::Foundation::Rect get_window_rect() = 0;
      virtual Windows::Foundation::Point get_cursor_pos() = 0;



   };

   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow,RECTD * lprect);
   CLASS_DECL_AURA bool get_window_rect(system_window ^ pwindow,LPRECT lprect);

#endif


   class file;


   namespace trace
   {

      class trace;

   }

   class session;

} // namespace aura


// only usable from axis and axis dependants
namespace axis
{

   class application;
   class session;
   class system;

}


// only usable from base and base dependants
namespace base
{

   class application;
   class session;
   class system;

}

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


#define CaSys(pca) (*pca->m_pauraapp->m_paurasystem)
#define Sys(pauraapp) (*pauraapp->m_paurasystem)
#define System (Sys(this->m_pauraapp))
#define threadSystem (Sys(get_thread_app()))


#define Sess(pauraapp) (*pauraapp->m_paurasession)
#define Session (Sess(m_pauraapp))

#define Plat(pauraapp) (*pauraapp->m_pcoreplatform)
#define Platform (Plat(m_pauraapp))


#undef App
#define App(pauraapp) (*pauraapp)
#define Application (App(m_pauraapp))


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


typedef  void(*PFN_ca2_factory_exchange)(sp(::aura::application) papp);





CLASS_DECL_AURA bool aura_init();
CLASS_DECL_AURA bool aura_term();

CLASS_DECL_AURA bool __node_aura_pre_init();
CLASS_DECL_AURA bool __node_aura_pos_init();

CLASS_DECL_AURA bool __node_aura_pre_term();
CLASS_DECL_AURA bool __node_aura_pos_term();


CLASS_DECL_AURA ::aura::application * get_thread_app();

#include "aura/aura/aura/aura_definition.h"

#include "aura/aura/aura/aura_action_source.h"

#include "aura/aura/aura/aura_new.h"

#include "aura/aura/aura/aura_lparam.h"
#include "aura/aura/aura/aura_muldiv64.h"



#include "aura/aura/aura/aura_auto_pointer.h"

#include "aura/aura/aura/aura_smart_pointer1.h"
#include "aura/aura/aura/aura_root.h"
#include "aura/aura/aura/aura_smart_pointer2.h"


#include "aura/aura/aura/aura_keep_true.h"


namespace file
{


   typedef sp(stream_buffer) buffer_sp;


} // namespace file


#include "aura/primitive/primitive_logic.h"



#include "aura/primitive/math/math_static_numeric_info.h"
#include "aura/primitive/math/math_numeric_info.h"
#include "aura/primitive/math/math_number.h"
//#include "aura/primitive/math/math_complex.h"


#include "aura/primitive/datetime/datetime_duration.h"


#include "aura/aura/aura/aura_element.h"

#include "aura/aura/aura/aura_debug.h"






#include "aura/aura/aura/aura_class.h"

#include "aura/primitive/comparison/comparison_md5.h"

#include "aura/aura/aura/aura_conv.h"

#include "aura/aura/aura/aura_core.h"

#include "aura/primitive/primitive_request_interface.h"

#include "aura/multithreading/multithreading_wait_result.h"

#include "aura/multithreading/multithreading_waitable.h"

#include "aura/primitive/primitive_object.h"


#include "aura/aura/xml/xml_exportable.h"
#include "aura/aura/xml/xml_importable.h"


#include "aura/primitive/collection/collection_decl.h"
#include "aura/primitive/collection/collection_array_decl.h"
#include "aura/primitive/collection/collection_raw_array_decl.h"
#include "aura/primitive/collection/collection_lemon_array_decl.h"
#include "aura/primitive/collection/collection_smart_pointer_array.h"


#include "aura/aura/aura/aura_action_context.h"



#include "aura/aura/aura/aura_fixed_alloc.h"



#include "aura/aura/aura/aura_allocate.h"
#include "aura/aura/aura/aura_plex.h"


#include "aura/primitive/primitive_id.h"


#include "aura/primitive/str/str.h"
#include "aura/aura/exception/exception.h"
#include "aura/aura/aura/aura_common.h"


#include "aura/aura/aura/aura_library.h"



#include "aura/primitive/datetime/datetime_time.h"




#include "aura/filesystem/filesystem.h"





#include "aura/primitive/geometry/geometry.h"


#include "aura/primitive/comparison/comparison.h"


#include "aura/primitive/collection/collection.h"


#include "aura/filesystem/file/file_string_buffer.h"


#include "aura/filesystem/file/file_set.h"


#include "aura/primitive/primitive_var2.h"


#include "aura/primitive/primitive_id_space.h"


#include "aura/primitive/math/math_scalar_enum.h"


#include "aura/primitive/math/math_scalar.h"


#include "aura/aura/aura/aura_progress.h"


#include "aura/aura/aura/aura_enum.h"


#include "aura/multithreading/multithreading.h"


#include "aura/aura/aura/aura_draw2d.h"


#include "aura/aura/aura/aura_gudo.h"




//#include "aura/user/user_create_context.h"


#if defined(LINUX)

#include "aura/os/ansios/ansios.h"

#elif defined(METROWIN)

#include "aura/os/metrowin/metrowin.h"
#include "aura/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "aura/os/ansios/ansios.h"
#include "aura/os/macos/macos.h"

#elif defined(ANDROID)

#include "aura/os/ansios/ansios.h"
#include "aura/os/android/android.h"

#elif defined(WINDOWS)

#include "aura/aura/os/windows/windows.h"

#elif defined(APPLE_IOS)

#include "aura/os/ansios/ansios.h"
#include "aura/os/ios/ios.h"
#include "aura/os/ios/ios_windowing.h"

#elif defined(SOLARIS)

#include "aura/os/ansios/ansios.h"
#include "aura/os/solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif







CLASS_DECL_AURA string get_system_error_message(uint32_t dwError);


#include "aura/aura/aura/aura_plex_heap.h"

#include "aura/primitive/primitive_type.h"


//#include "graphics/graphics.h"
//#include "user/user/user_enum.h"
//#include "user/user/user_keyboard_focus.h"
//#include "user/user/user_mouse_focus.h"
//#include "user/user/user_elemental.h"
#include "aura/aura/aura/aura_flags.h"
#include "aura/primitive/primitive_check.h"
//#include "user/user/user_check_interface.h"
#include "aura/aura/aura/aura_command.h"
//#include "graphics/visual/visual_const.h"
//#include "user/user/user_key_enum.h"
#include "aura/aura/message/message.h"
#include "aura/user/user/user_check_interface.h"
#include "aura/aura/aura/aura_command_target.h"
//#include "user/user/user_schema.h"
//#include "user/user/user_schema_simple_impl.h"
//#include "user/user/user_schema_layered_frame.h"
//#include "user/user/user_text_interface.h"
//#include "user/user/user_draw_interface.h"
//#include "user/user/user_window_util.h"
//#include "user/user/user_interaction_base.h"
//#include "user/user/user_buffer.h"
#include "aura/aura/aura/aura_keep.h"
#include "aura/filesystem/file/file_stream2.h"
//#include "user/user/user_interaction.h"
//#include "user/user/user_interaction_impl_base.h"
//#include "user/user/user_interaction_child.h"
//#include "user/user/user_interaction_impl.h"
//#include "user/user/user_control_bar.h"
//#include "user/user/user_wait_cursor.h"
//#include "user/user/user_frame_window.h"
//#include "user/user/user_server.h"
//#include "user/user/user_impact_system.h"





#include "aura/primitive/primitive_interlocked_long.h"
#include "aura/primitive/primitive_interlocked_long_pulse.h"

#include "aura/primitive/data/data_data.h"
#include "aura/primitive/data/data_data_listener.h"
#include "aura/primitive/data/data_data_container.h"
#include "aura/primitive/data/data_item.h"
//#include "aura/primitive/data/data_tree_item.h"
//#include "aura/primitive/data/data_tree.h"
//#include "aura/primitive/data/data_simple_item.h"

#include "aura/primitive/primitive_edit.h"
#include "aura/aura/aura/aura_departament.h"
#include "aura/aura/aura/aura_departament_container.h"
#include "aura/aura/xml/xml.h"
//#include "aura/user/simple_ui/simple_ui_style.h"
//#include "aura/user/simple_ui/simple_ui_interaction.h"
//#include "aura/database/database.h"
//#include "user/user/user_document_data_map.h"
//#include "user/user/user_document.h"
//#include "user/user/user_impact.h"
#include "aura/aura/aura/aura_live_object.h"
#include "aura/aura/aura/aura_live_signal.h"
#include "aura/multithreading/multithreading_thread.h"
#include "aura/aura/aura/aura_message_queue_listener.h"
#include "aura/aura/aura/aura_message_queue.h"
#include "aura/user/user/user_timer_item.h"
#include "aura/user/user/user_timer_array.h"
#include "aura/multithreading/multithreading_thread_impl.h"
#include "aura/multithreading/multithreading_simple_thread.h"
#include "aura/multithreading/multithreading_go_thread.h"
#include "aura/multithreading/multithreading_signal_thread.h"


#include "aura/primitive/primitive_job.h"

#include "aura/user/simple/simple_message_box.h"

#include "aura/user/user/user.h"

#include "aura/aura/aura/aura_log.h"
#include "aura/aura/aura/aura_trace.h"



#include "aura/primitive/primitive_memory_base.h"
#include "aura/primitive/primitive_memory.h"
#include "aura/primitive/primitive_shared_memory.h"
#include "aura/primitive/primitive_virtual_memory.h"
#include "aura/primitive/primitive_memory_container.h"



#include "aura/filesystem/file/file_memory_buffer.h"
#include "aura/filesystem/file/file_byte_stream_memory_buffer.h"
#include "aura/filesystem/file/file_plain_text_stream_memory_buffer.h"
#include "aura/filesystem/file/file_circular_buffer.h"


#include "aura/filesystem/file/file_timeout_buffer.h"
#include "aura/filesystem/file/file_transfer_buffer.h"


#include "aura/primitive/str/str_international2.h"



#if defined(METROWIN)

#include "app/appseed/aura/aura/os/metrowin/metrowin_sockets.h"

#endif


#include "aura/primitive/primitive_factory.h"


#include "aura/primitive/math/math_math_rng.h"
#include "aura/primitive/math/math_departament.h"
#include "aura/primitive/geometry/geometry_geometry.h"




//#include "user/user/user_window_map.h"
//
//#include "user/user/user_keyboard_layout.h"
//#include "user/user/user_keyboard.h"
//#include "user/user/user_user.h"

#include "aura/aura/aura/aura_main_init_data.h"

#include "aura/aura/aura/aura_savings.h"


#include "aura/aura/aura/aura_application_interface.h"
#include "aura/aura/aura/aura_application.h"
#include "aura/aura/aura/aura_application_ptra.h"


#include "aura/aura/aura/aura_gudo_application.inl"


#include "aura/aura/aura/aura_application_signal_details.h"

#include "aura/aura/aura/aura_session_interface.h"
#include "aura/aura/aura/aura_platform_interface.h"
#include "aura/aura/aura/aura_session.h"



#include "aura/primitive/primitive_application_bias.h"
#include "aura/aura/exception/exception_engine.h"

#include "aura/aura/aura/aura_fixed_alloc_impl.h"
#include "aura/aura/aura/aura_plex_heap_impl.h"
#include "aura/primitive/primitive_command_line.h"
#include "aura/primitive/primitive_command.h"
#include "aura/user/user/user_create_context.h"
#include "aura/primitive/primitive_create_context.h"
#include "aura/primitive/primitive_request_signal.h"




#include "aura/aura/aura/aura_net.h"



#include "aura/primitive/primitive_command_thread.h"




#include "aura/filesystem/file/file_buffered_buffer.h"


#include "aura/aura/aura/aura_machine_event_data.h"
#include "aura/aura/aura/aura_machine_event.h"
#include "aura/aura/aura/aura_machine_event_central.h"

#include "aura/primitive/datetime/datetime_value.h"

#include "aura/primitive/str/str_international_locale_schema.h"

#include "aura/aura/aura/aura_id_pool.h"


#include "aura/aura/aura/aura_launcher.h"
#ifndef METROWIN
#include "aura/aura/aura/aura_small_ipc_channel.h"
#endif


#include "aura/aura/aura/aura_cregexp.h"
#include "aura/aura/aura/aura_cregexp_util.h"


#include "aura/aura/process/process.h"



#include "aura/aura/aura/aura_core_os.h"

#include "aura/aura/aura/aura_system.h"

#include "aura/aura/aura/aura_system_str.h"

#include "aura/os/os_process.h"










//#include "aura/install/install_trace.h"


#define new AURA_NEW


#include "aura/aura/aura/aura_system_trace.h"




#include "aura/multithreading/multithreading.inl"


#include "aura/primitive/str/str.inl"

#include "aura/aura/aura.inl"

#include "primitive/collection/collection.inl"


/*namespace numeric_info
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
memset(&t,0xff,sizeof(T));
return t;
}

template < typename T >
inline bool is_signed()
{
return ((T)-1) < 0;
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

*/


#ifdef VARIADIC_TEMPLATE

template<typename T,typename... Args>
inline void string_format::printf(const char * & s,const T & value,Args... args)
{

   while(*s)
   {

      if(*s == '%' && *(++s) != '%')
      {

         defer_get_additional_argument(s,value,args...);

         return;

      }

      append(*s++);

   }

   throw simple_exception(get_thread_app(),"extra arguments provided to printf");


}



inline void string_format::printf(const char * & s)
{

   while(*s)
   {

      if(*s == '%' && *(++s) != '%')
         throw simple_exception(get_thread_app(),"invalid format string: missing arguments");

      append(*s++);

   }

   (m_pprinter->*m_pfnPrinter)(m_pvoidPrinter,m_pszBuffer);

}

#endif





#ifndef WINDOWSEX

#include "aura/os/cross/windows/windows_thread_impl.h"

#endif





#include "aura/primitive/collection/collection_array_impl.inl"
#include "aura/primitive/collection/collection_raw_array_impl.inl"
#include "aura/primitive/collection/collection_sort_array_impl.inl"
#include "aura/primitive/collection/collection_lemon_array_impl.inl"

#include "aura/primitive/collection/collection_list_impl.inl"
#include "aura/primitive/collection/collection_map_impl.inl"

#include "aura/primitive/collection/collection_sort_map_impl.inl"

#include "aura/primitive/collection/collection_fifo_map_impl.inl"



#include "aura/primitive/primitive_factory_impl.inl"





#include "aura/aura/aura/aura_system_smart_pointer.inl"
#include "aura/aura/aura/aura_system_object.inl"
#include "aura/aura/aura/aura_system_id.inl"
#include "aura/aura/aura/aura_system_factory.inl"
#include "aura/aura/aura/aura_system_primitive_var.inl"
#include "aura/aura/aura/aura_system_xml.inl"



#include "aura/aura/aura/aura_core_os.h"


#include "aura/aura/aura/aura_microtimer.h"








#include "aura/aura/aura/aura_libc.h"


#include "aura/aura/aura/aura_number.h"


#include "aura/aura/aura/aura_debug.h"


#include "aura/aura/aura/aura_printf.h"
#include "aura/aura/aura/aura_sprintf.h"



#include "aura/aura/aura/aura_math.h"









#include "aura/aura/aura/aura_file_watcher.h"
#include "aura/aura/aura/aura_file_watcher_impl.h"


#include "aura/aura/aura/aura_os.h"


#include "aura/multithreading/multithreading_data.h"


#include "aura/aura/aura/aura_simple_shell_launcher.h"


#include "aura/aura/aura/aura_file_watcher_thread.h"
#include "aura/aura/aura/aura_file_watcher_listener_thread.h"
#include "aura/aura/aura/aura_async.h"


//#include "aura/hotplugin/hotplugin.h"




#include "aura/aura/aura/aura_message_loop.h"

#include "aura/aura/aura/aura_url.h"

#include "aura/aura/aura/aura_international.h"

#include "aura/aura/aura/aura_static_start.h"



#define return_(y, x) {y = x; return;}


extern "C"
{


   int32_t _c_lock_is_active(const char * pszName);
   int32_t _c_lock(const char * pszName,void ** pdata);
   int32_t _c_unlock(void ** pdata);


}


CLASS_DECL_AURA string _ca_get_file_name(const char * psz,bool bCreate = false,int32_t * pfd = NULL);

CLASS_DECL_AURA string get_system_error_message(uint32_t dwError);


#include "aura/aura/aura/aura_simple_app.h"






#include "app/appseed/aura/aura/node/node.h"


namespace math
{

   template < typename T >
   class complex;


} // namespace math


namespace std
{

   using string = ::string;
   using wstring = ::wstring;

   template < class KEY,class VALUE,class COMPARE = ::comparison::less < KEY >,bool bMultiKey = false >
   using map = ::sort_map < KEY,const KEY &,VALUE,const VALUE &,COMPARE,bMultiKey >;

   template < class TYPE >
   using list = ::list< TYPE >;

   template < class TYPE >
   using vector = ::array< TYPE >;

   template < class TYPE >
   using set = ::set< TYPE >;

   using ostream = ::file::output_stream;
   using ofstream = ::file::file_output_stream;

   using istream = ::file::input_stream;
   using ifstream = ::file::file_input_stream;

   using stream = ::file::stream;
   using fstream = ::file::file_stream;

   using iostream = ::file::stream;
   using iofstream = ::file::file_stream;

   using stringstream = ::file::plain_text_stream_string_buffer;
   using ostringstream = ::file::plain_text_output_stream_string_buffer;

   template < typename T >
   using numeric_limits = ::numeric_info < T >;

   //      template <class T> void sort(T & t1,T & t2)
   //    {
   //     ::sort::sort < T >(t1,t2);
   //}

   template < class iterator,class COMPARE = ::comparison::less < typename iterator::BASE_TYPE,typename iterator::BASE_ARG_TYPE > >
   void sort(const iterator & a, const iterator & b)
   {
      ::sort::quick_sort < iterator,COMPARE >(a,b);
   }

   template < typename T >
   using auto_ptr = ::auto_pointer < T >;

   template < typename T >
   using stack = ::stack < T >;


   using filebuf = ::file::streambuf;

   //using ios_base = ::file::stream_base;

   // replace ::::file:: => ::file::


   using runtime_error = ::runtime_error;

   using streambuf = ::file::stream_buffer;


   template < typename T >
   T abs(T t)
   {
      if(t < ::numeric_info< T >::null())
         return -t;
      else
         return t;
   }


   using streamsize = ::file_size;
   using streampos = ::file_position;
   using streamoff = ::file_offset;

   using setw = ::file::set_width;

#if !defined(WINDOWSEX) && !defined(MACOS) && !defined(METROWIN)

   using bad_alloc = ::memory_exception;

#endif

   template < typename T >
   using complex = ::math::complex < T >;


   template <class T> const T& min(const T& a,const T& b) { return !(a > b) ? a : b; }
   template <class T> const T& max(const T& a,const T& b) { return !(a < b) ? a : b; }

   template <class RandomAccessIterator>
   void make_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::lemon::make_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void make_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::lemon::make_heap(first,last,comp);
   }

   template <class RandomAccessIterator,class Compare>
   void pop_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::lemon::pop_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void pop_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::lemon::pop_heap(first,last,comp);
   }

   template <class RandomAccessIterator,class Compare>
   void push_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::lemon::push_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void push_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::lemon::push_heap(first,last,comp);
   }

   template <class RandomAccessIterator>
   void sort_heap(RandomAccessIterator first,RandomAccessIterator last)
   {
      ::lemon::sort_heap(first,last);
   }

   template <class RandomAccessIterator,class Compare>
   void sort_heap(RandomAccessIterator first,RandomAccessIterator last,Compare comp)
   {
      ::lemon::sort_heap(first,last,comp);
   }
   
#ifndef __APPLE__

   template <class T> void swap(T& a,T& b)
   {
      T c(a); a=b; b=c;
   }
   
#endif

}


template < typename T >
inline string to_json(const T & value)
{
   return ::str::from(value);
}


CLASS_DECL_AURA void dappy(const char * psz);




#include "aura/primitive/primitive_color.h"





CLASS_DECL_AURA void set_aura(void * p,::aura::application * papp);
CLASS_DECL_AURA ::aura::application * get_aura(void * p);



#include "aura/user/user.h"



