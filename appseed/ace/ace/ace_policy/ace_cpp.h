/////////////////////////////////////////////////////////////////////////////////////////
//
//   All Pure and Aural ca2 and God and Gods and Goddssesses and devils's blessings
//
//   C++
//
//   C => in ca2 scope
//
//   Thank you God for C++!! Cheap and valuable!!
//

#pragma once

#ifdef WINDOWS
#pragma warning(disable: 4251)
#endif

#include "nodeapp/operational_system/operational_system.h"

// very short name ([{c}])ontext (switchers, as it as context) enums
enum e_context_switcher_null
{
   cnull
};

// very short name ([{c}])ontext (switchers, as it as context) enums
enum e_context_switcher_empty
{
   cempty
};

// very short name ([{c}])ontext (switchers, as it as context) enums
enum e_context_switcher_no_exception
{
   no_exception
};

// very short name ([{c}])ontext (switchers, as it as context) enums
enum e_context_switcher_failed
{
   failure,
   failure_no_log
};


template<class T>
struct remove_reference
{
	typedef T TYPE;
};

template<class T>
struct remove_reference<T&>
{
	typedef T TYPE;
};

template<class T>
struct remove_reference<T&&>
{
	typedef T TYPE;
};

template<class T> inline
typename remove_reference<T>::TYPE&& move(T && t)
{

	return (static_cast<typename remove_reference<T>::TYPE&&>(t));

}




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
class base_edit;

class timer_callback;


namespace ace
{

   class Timer;

};

class timer;

typedef bool FN_TIMER(timer * ptimer);
typedef FN_TIMER * PFN_TIMER;


//template < typename Type,typename RawType = typename Type >
//class string_array;
//typedef string_array < string > stringa;


namespace ace
{


   class application;
   class system;
   class application_signal_details;

   class command;

   class str;
   class str_context;


} // namespace ace


namespace user
{

   class primitive;
   class frame;
   class menu;
   class document;

   class impact_system;
   class printer;
   class impact;
   class elemental;


} // namespace ace


namespace install
{

   class install;


} // namespace install


namespace data
{


   class listener;
   class data;
   class simple_data;
   class data_container_base;


} // namespace data

namespace sockets // only usable from base.dll and dependants
{

   class sockets; // only usable from base.dll and dependants


} // namespace sockets // only usable from base.dll and dependants


namespace url
{

   class department; // only usable from base.dll and dependants


} // namespace url


namespace axis // only usable from axis.dll and dependants
{

   class compress; // only usable from axis.dll and dependants


} // namespace axis // only usable from axis.dll and dependants


class dump_context;
//class string_interface;
class id_space;
class type;
class ptra;
class factory_item_base;
class fixed_alloc_no_sync;
class critical_section;
class var_array;
//class pair_set_interface;
//class str_str_interface;
class command_thread;
class thread;
class command_target;
class cmd_ui;
class critical_section;
class mutex;
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


class memory;


//namespace plane
//{
//
//   class session;
//   class system;
//   //class cube;
//
//
//} // namespace plane

class cmd_ui;

namespace datetime
{


   class department;


} // namespace datetime


namespace draw2d
{


   class graphics;


} // namespace draw2d


namespace file
{

   class listing;
   class path;
   typedef CLASS_DECL_ACE ::string_array < ::file::path,string > patha;
   class stream_buffer;
   class istream;
   class ostream;
   class serializable;


} // namespace file


class machine_event_data;


namespace html
{

   class html;

} // namespace html


#include "ace/ace/ace/ace_auto.h"



namespace ace
{

   class allocatorsp;

   template < typename T >
   inline void del(T * & p)
   {

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2015-02-18 19:08
      // catch all (...) here in ace::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if(p != NULL)
         {

            T * pdel = p;

            p = NULL;

            delete pdel;

         }

      }
      catch(...)
      {

      }

   }

   template < typename T >
   inline void adel(T * & p)
   {

      //Thank you Fiora a Eterna!!

      //Fiora Aeterna☄ ‏@FioraAeterna 20m20 minutes ago

      //   maybe it's cynical but I'm starting to think the real reason so many newer games have constant autosaves is because they crash all the time
      //   Details

      // BRT 2015-02-18 19:08
      // catch all (...) here in ace::del ... but should remove try catch from all underlying calls (frees, memory_frees, memory_dbg_frees).

      try
      {

         if(p != NULL)
         {

            delete[] p;

            p = NULL;

         }

      }
      catch(...)
      {

      }

   }

} // namespace ace



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


typedef struct RECTD RECTD;


namespace ace
{


//#if defined METROWIN && defined(__cplusplus_winrt)
//
//   interface class system_window
//   {
//
//      virtual Windows::Foundation::Rect get_window_rect() = 0;
//      virtual Windows::Foundation::Point get_cursor_pos() = 0;
//
//
//
//   };
//
//   CLASS_DECL_ACE bool get_window_rect(system_window ^ pwindow,RECTD * lprect);
//   CLASS_DECL_ACE bool get_window_rect(system_window ^ pwindow,LPRECT lprect);
//
//#endif


   class file;


   namespace trace
   {

      class trace;

   }

   class session;

} // namespace ace


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
   class session;
   class system;

}

typedef ::ace::system * CREATE_SYSTEM();
typedef CREATE_SYSTEM * LPFN_CREATE_SYSTEM;

CLASS_DECL_ACE extern LPFN_CREATE_SYSTEM g_pfn_create_system;
CLASS_DECL_ACE extern const char * g_pszCooperativeLevel;

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


#ifdef WINDOWS

typedef HANDLE HTHREAD;

#else

#ifndef LINUX
typedef pthread_t HTHREAD;
#endif

#endif


class event;


class thread;




class thread;


typedef smart_pointer < thread > thread_sp;


//class thread_impl;


//typedef smart_pointer < thread_impl > thread_impl_sp;


namespace html
{

   class html; // defined and set by html library/component

}



#define SCAST_PTR(TYPE, ptarget, psource) TYPE * ptarget = dynamic_cast < TYPE * > (psource);
#define SCAST_REF(TYPE, rtarget, psource) TYPE & rtarget = *(dynamic_cast < TYPE * > (psource))


#define CaSys(pca) (*pca->m_paceapp->m_pacesystem)
#define Sys(paceapp) (*paceapp->m_pacesystem)
#define System (Sys(this->m_paceapp))
#define threadSystem (Sys(get_thread_app()))


#define Sess(paceapp) (*paceapp->m_pacesession)
#define Session (Sess(m_paceapp))


#undef App
#define App(paceapp) (*paceapp)
#define Application (App(m_paceapp))


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


typedef  void(*PFN_ca2_factory_exchange)(::ace::application * papp);

#ifdef WINDOWS
CLASS_DECL_ACE bool defer_co_initialize_ex();
#endif

CLASS_DECL_ACE bool ace_init();
CLASS_DECL_ACE bool ace_term();

CLASS_DECL_ACE bool __node_ace_pre_init();
CLASS_DECL_ACE bool __node_ace_pos_init();

CLASS_DECL_ACE bool __node_ace_pre_term();
CLASS_DECL_ACE bool __node_ace_pos_term();


CLASS_DECL_ACE ::ace::application * get_thread_app();

#include "ace/primitive/primitive_cflag.h"

#include "ace/ace/ace/ace_definition.h"

#include "ace/ace/ace/ace_action_source.h"

#include "ace/ace/ace/ace_new.h"

#include "ace/ace/ace/ace_lparam.h"
#include "ace/ace/ace/ace_muldiv64.h"



template <class TYPE>
inline bool is_null(const TYPE & ref)
{
   return &ref == NULL;
}

#define NULL_REF(class) (*((class *) NULL))


#include "ace/ace/ace/ace_auto_pointer.h"

#include "ace/ace/ace/ace_smart_pointer1.h"
#include "ace/ace/ace/ace_smart_pointer2.h"


#include "ace/ace/ace/ace_keep_true.h"


namespace file
{


   using buffer_sp = sp(stream_buffer);


} // namespace file


#include "ace/primitive/primitive_logic.h"



#include "ace/primitive/math/math_static_numeric_info.h"
#include "ace/primitive/math/math_numeric_info.h"
#include "ace/primitive/math/math_c_number.h"
//#include "ace/primitive/math/math_complex.h"


#include "ace/primitive/datetime/datetime_duration.h"


#include "ace/primitive/str/str.h"



#include "ace/primitive/datetime/datetime_date_span.h"
#include "ace/primitive/datetime/datetime_time_span.h"
#include "ace/primitive/datetime/datetime_time.h"
#include "ace/primitive/datetime/datetime_file_time_span.h"
#include "ace/primitive/datetime/datetime_file_time.h"

#include "ace/primitive/enum.h"


#include "ace/ace/ace/ace_element.h"

#include "ace/ace/ace/ace_debug.h"


#include "ace/ace/ace_app_core.h"



#include "ace/ace/ace/ace_class.h"

#include "ace/primitive/comparison/comparison_md5.h"

#include "ace/ace/ace/ace_conv.h"

#include "ace/ace/ace/ace_core.h"

#include "ace/primitive/primitive_request_interface.h"

#include "ace/multithreading/multithreading_wait_result.h"

#include "ace/multithreading/multithreading_waitable.h"

#include "ace/primitive/primitive_object.h"


#include "ace/ace/xml/xml_exportable.h"
#include "ace/ace/xml/xml_importable.h"


#include "ace/primitive/comparison/comparison.h"


#include "ace/primitive/collection/collection_decl.h"
#include "ace/primitive/collection/collection_array_decl.h"
#include "ace/primitive/collection/collection_raw_array_decl.h"
#include "ace/primitive/collection/collection_lemon_array_decl.h"
#include "ace/primitive/collection/collection_smart_pointer_array.h"
#include "ace/primitive/collection/collection_comparable_eq_array.h"
#include "ace/primitive/collection/collection_comparable_array.h"
#include "ace/primitive/collection/collection_comparable_raw_array.h"


#include "ace/primitive/collection/collection_ptr_array.h"


#include "ace/primitive/collection/collection_lemon_heap.h"


#include "ace/ace/ace/ace_action_context.h"



#include "ace/ace/ace/ace_fixed_alloc.h"



#include "ace/ace/ace/ace_allocate.h"
#include "ace/ace/ace/ace_plex.h"


#include "ace/primitive/primitive_id.h"

#include "ace/primitive/str/str_interface.h"
#include "ace/primitive/str/str_composite.h"
#include "ace/primitive/str/str_base64.h"



#include "ace/ace/exception/exception.h"
#include "ace/ace/ace/ace_common.h"
#include "ace/filesystem/filesystem/filesystem_path.h"





#include "ace/ace/ace/ace_library.h"






#include "ace/filesystem/filesystem.h"





#include "ace/primitive/geometry/geometry.h"


#include "ace/primitive/collection/collection.h"


#include "ace/primitive/geometry/geometry_box.h"


#include "ace/ace/ace/ace_cmp.h"


#include "ace/filesystem/file/file_string_buffer.h"


#include "ace/primitive/str/str_format.h"


#include "ace/primitive/primitive_var2.h"


#include "ace/primitive/primitive_id_space.h"


#include "ace/primitive/math/math_scalar_enum.h"


#include "ace/primitive/math/math_scalar.h"


#include "ace/ace/ace/ace_progress.h"


#include "ace/ace/ace/ace_enum.h"


#include "ace/multithreading/multithreading.h"


#include "ace/ace/ace/ace_draw2d.h"


CLASS_DECL_ACE mutex & draw2d_direct2_mutex();


#include "ace/ace/ace/ace_gudo.h"




//#include "ace/user/user_create_context.h"


#if defined(LINUX)

#include "ace/os/ansios/ansios.h"

#elif defined(METROWIN)

#include "ace/os/metrowin/metrowin.h"
#include "ace/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "ace/os/ansios/ansios.h"
#include "ace/os/macos/macos.h"

#elif defined(ANDROID)

#include "ace/os/ansios/ansios.h"
#include "ace/os/android/android.h"

#elif defined(WINDOWS)

#include "ace/ace/os/windows/windows.h"

#elif defined(APPLE_IOS)

#include "ace/os/ansios/ansios.h"
#include "ace/os/ios/ios.h"
//#include "ace/os/ios/ios_windowing.h"

#elif defined(SOLARIS)

#include "ace/os/ansios/ansios.h"
#include "ace/os/solaris/solaris_user_impl.h"

#else


#error "not implemented!!"

#endif







CLASS_DECL_ACE string get_system_error_message(uint32_t dwError);


#include "ace/ace/ace/ace_plex_heap.h"

#include "ace/primitive/primitive_type.h"


//#include "user/user/user_enum.h"
//#include "user/user/user_keyboard_focus.h"
//#include "user/user/user_mouse_focus.h"
//#include "user/user/user_elemental.h"
#include "ace/ace/ace/ace_flags.h"
#include "ace/primitive/primitive_check.h"
//#include "user/user/user_check_interface.h"
#include "ace/ace/ace/ace_command.h"
#include "ace/ace/ace/ace_command_msg.h"
#include "ace/ace/ace/ace_command_ui.h"
#include "ace/ace/ace/ace_command_ui_test.h"
//#include "graphics/visual/visual_const.h"
//#include "user/user/user_key_enum.h"
#include "ace/ace/message/message.h"
//#include "ace/user/user/user_check_interface.h"
#include "ace/ace/ace/ace_command_target.h"
//#include "user/user/user_schema.h"
//#include "user/user/user_schema_simple_impl.h"
//#include "user/user/user_schema_layered_frame.h"
//#include "user/user/user_text_interface.h"
//#include "user/user/user_draw_interface.h"
//#include "user/user/user_window_util.h"
//#include "user/user/user_interaction_base.h"
//#include "user/user/user_buffer.h"
#include "ace/ace/ace/ace_keep.h"
#include "ace/ace/ace/ace_restore.h"
#include "ace/ace/ace/ace_md5.h"
#include "ace/filesystem/file/file_stream2.h"
//#include "user/user/user_interaction.h"
//#include "user/user/user_interaction_impl_base.h"
//#include "user/user/user_interaction_child.h"
//#include "user/user/user_interaction_impl.h"
//#include "user/user/user_control_bar.h"
//#include "user/user/user_wait_cursor.h"
//#include "user/user/user_frame_window.h"
//#include "user/user/user_server.h"
//#include "user/user/user_impact_system.h"





#include "ace/primitive/primitive_interlocked_long.h"
#include "ace/primitive/primitive_interlocked_long_pulse.h"

#include "ace/primitive/data/data_data.h"
#include "ace/primitive/data/data_data_listener.h"
#include "ace/primitive/data/data_data_container.h"
#include "ace/primitive/data/data_item.h"
//#include "ace/primitive/data/data_tree_item.h"
//#include "ace/primitive/data/data_tree.h"
//#include "ace/primitive/data/data_simple_item.h"







//----------




#include "ace/primitive/math/math_objects.h"




//----------








#include "ace/primitive/collection/collection_file_path_map.h"

#include "ace/primitive/primitive_edit.h"
#include "ace/ace/ace/ace_department.h"
#include "ace/ace/ace/ace_department_container.h"
#include "ace/ace/xml/xml.h"

//#include "ace/user/simple_ui/simple_ui_style.h"
//#include "ace/user/simple_ui/simple_ui_interaction.h"
//#include "ace/database/database.h"
//#include "user/user/user_document_data_map.h"
//#include "user/user/user_document.h"
//#include "user/user/user_impact.h"
#include "ace/ace/ace/ace_live_object.h"
#include "ace/ace/ace/ace_live_signal.h"
#include "ace/multithreading/multithreading_thread.h"
#include "ace/multithreading/multithreading_forking_thread.h"
#include "ace/ace/ace_timer_callback.h"
#include "ace/ace/ace/ace_timer_item.h"
#include "ace/ace/ace/ace_timer_array.h"
#include "ace/ace/ace_timer.h"
#include "ace/ace/ace_timer_event.h"

//#include "ace/ace/ace/ace_message_queue_listener.h"
//#include "ace/ace/ace/ace_message_queue.h"
#include "ace/multithreading/multithreading_thread_impl.h"
#include "ace/multithreading/multithreading_simple_thread.h"
#include "ace/multithreading/multithreading_go_thread.h"
#include "ace/multithreading/multithreading_signal_thread.h"


#include "ace/primitive/primitive_job.h"

#include "ace/user/simple/simple_message_box.h"

#include "ace/ace/ace/ace_user.h"

#include "ace/ace/ace/ace_log.h"
#include "ace/ace/ace/ace_trace.h"



#include "ace/primitive/primitive_memory_base.h"
#include "ace/primitive/primitive_memory.h"
#include "ace/primitive/primitive_shared_memory.h"
#include "ace/primitive/primitive_virtual_memory.h"
#include "ace/primitive/primitive_memory_container.h"



#include "ace/filesystem/file/file_memory_buffer.h"
#include "ace/filesystem/file/file_byte_stream_memory_buffer.h"
#include "ace/filesystem/file/file_plain_text_stream_memory_buffer.h"
#include "ace/filesystem/file/file_circular_buffer.h"


#include "ace/filesystem/file/file_timeout_buffer.h"
#include "ace/filesystem/file/file_transfer_buffer.h"

#include "ace/ace/ace/ace_local_memory_map.h"

#include "ace/primitive/str/str_international2.h"



//#if defined(METROWIN)
//
//#include "app/appseed/ace/ace/os/metrowin/metrowin_sockets.h"
//
//#endif


#include "ace/primitive/primitive_factory.h"


#include "ace/primitive/math/math_math_rng.h"
#include "ace/primitive/math/math_department.h"
#include "ace/primitive/geometry/geometry_geometry.h"


CLASS_DECL_ACE string get_exe_path();


//#include "user/user/user_window_map.h"
//
//#include "user/user/user_keyboard_layout.h"
//#include "user/user/user_keyboard.h"
//#include "user/user/user_user.h"

#include "ace/ace/ace/ace_main_init_data.h"

#include "ace/ace/ace/ace_savings.h"

#include "ace/net/net.h"


#include "ace/ace/ace/ace_launcher.h"


#include "ace/ace/ace/ace_ipc.h"


#include "ace/ace/ace/ace_app_launcher.h"


#include "ace/ace/ace/ace_ipi.h"




#include "ace/filesystem/filesystem/filesystem_application.h"

#include "ace/filesystem/filesystem/filesystem_dir_application.h"

#include "ace/filesystem/filesystem/filesystem_listing.h"

#include "ace/filesystem/file/file_set.h"

#include "ace/primitive/primitive_application_bias.h"


//#include "ace/ace/ace/ace_application_interface.h"
#include "ace/ace/ace/ace_application.h"
#include "ace/ace/ace/ace_application_ptra.h"


#include "ace/ace/ace/ace_gudo_application.inl"


#include "ace/ace/ace/ace_application_signal_details.h"

#include "ace/ace/ace/ace_session.h"



#include "ace/ace/exception/exception_engine.h"

#include "ace/ace/ace/ace_fixed_alloc_impl.h"
#include "ace/ace/ace/ace_plex_heap_impl.h"
#include "ace/primitive/primitive_command_line.h"
#include "ace/primitive/primitive_command.h"
#include "ace/ace/ace/ace_create_context.h"
#include "ace/primitive/primitive_create.h"
#include "ace/primitive/primitive_request_signal.h"




#include "ace/ace/ace/ace_net.h"



#include "ace/primitive/primitive_command_thread.h"




#include "ace/filesystem/file/file_buffered_buffer.h"


#include "ace/ace/ace/ace_machine_event_data.h"
#include "ace/ace/ace/ace_machine_event.h"
#include "ace/ace/ace/ace_machine_event_central.h"

#include "ace/primitive/datetime/datetime.h"

#include "ace/primitive/str/str_international_locale_schema.h"

#include "ace/ace/ace/ace_id_pool.h"



#include "ace/ace/ace/ace_cregexp.h"
#include "ace/ace/ace/ace_cregexp_util.h"

#ifdef VSNORD

#include "ace/ace/os/android/android_init_data.h"

#endif


#include "ace/ace/process/process.h"

#include "ace/filesystem/filesystem/filesystem_system.h"

#include "ace/ace/ace/ace_file_watcher.h"
#include "ace/ace/ace/ace_file_watcher_thread.h"
#include "ace/ace/ace/ace_file_watcher_listener_thread.h"

#include "ace/filesystem/filesystem/filesystem_dir_system.h"

#include "ace/ace/ace/ace_core_os.h"

#include "ace/ace/ace/ace_system.h"

#include "ace/ace/ace/ace_system_str.h"

#include "ace/os/os_process.h"









//#include "ace/install/install_trace.h"


#define new ACE_NEW


#include "ace/ace/ace/ace_system_trace.h"




#include "ace/multithreading/multithreading.inl"


#include "ace/primitive/str/str.inl"

#include "ace/ace/ace.inl"

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


#ifdef VARIADIC_TEMPLATE_FORMAT2

template<typename T,typename... Args>
inline void string_format::format(const char * & s,const T & value,Args... args)
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

   throw simple_exception(get_thread_app(),"extra arguments provided to format");


}



inline void string_format::format(const char * & s)
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

#include "ace/os/cross/windows/windows_thread_impl.h"

#endif




#include "ace/primitive/collection/collection_array_base.inl"
#include "ace/primitive/collection/collection_array_impl.inl"
#include "ace/primitive/collection/collection_raw_array_impl.inl"
#include "ace/primitive/collection/collection_sort_array_impl.inl"
#include "ace/primitive/collection/collection_lemon_array_impl.inl"

#include "ace/primitive/collection/collection_list_impl.inl"
#include "ace/primitive/collection/collection_map_impl.inl"

#include "ace/primitive/collection/collection_sort_map_impl.inl"

#include "ace/primitive/collection/collection_fifo_map_impl.inl"



#include "ace/primitive/primitive_factory_impl.inl"





#include "ace/ace/ace/ace_system_smart_pointer.inl"
#include "ace/ace/ace/ace_system_object.inl"
#include "ace/ace/ace/ace_system_id.inl"
#include "ace/ace/ace/ace_system_factory.inl"
#include "ace/ace/ace/ace_system_primitive_var.inl"
#include "ace/ace/ace/ace_system_xml.inl"



#include "ace/ace/ace/ace_core_os.h"


#include "ace/ace/ace/ace_microtimer.h"







#include "ace/ace/ace/ace_assert_running_task.h"










#include "ace/ace/ace/ace_number.h"


#include "ace/ace/ace/ace_debug.h"


#include "ace/ace/ace/ace_printf.h"
#include "ace/ace/ace/ace_sprintf.h"



#include "ace/ace/ace/ace_math.h"









#include "ace/ace/ace/ace_file_watcher.h"
#include "ace/ace/ace/ace_file_watcher_impl.h"


#include "ace/ace/ace_console_window.h"


#include "ace/ace/ace/ace_os.h"


#include "ace/multithreading/multithreading_data.h"


#include "ace/ace/ace/ace_shell_launcher.h"


#include "ace/ace/ace/ace_async.h"


#include "ace/ace/ace/ace_message_loop.h"

#include "ace/ace/ace/ace_url.h"

#include "ace/ace/ace/ace_international.h"

#include "ace/ace/ace/ace_static_start.h"



#define return_(y, x) {y = x; return;}


extern "C"
{


   int32_t _c_lock_is_active(const char * pszName);
   int32_t _c_lock(const char * pszName,void ** pdata);
   int32_t _c_unlock(void ** pdata);


}


CLASS_DECL_ACE string _ca_get_file_name(const char * psz,bool bCreate = false,int32_t * pfd = NULL);

CLASS_DECL_ACE string get_system_error_message(uint32_t dwError);


#include "ace/ace/ace/ace_simple_app.h"


#include "ace/ace/ace/ace_profiler.h"


#include "ace/os/os2.h"


#include "app/appseed/ace/ace/node/node.h"


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

   using ostream = ::file::ostream;
   using ofstream = ::file::file_ostream;

   using istream = ::file::istream;
   using ifstream = ::file::file_istream;

   using stream = ::file::stream;
   using fstream = ::file::file_stream;

   using iostream = ::file::stream;
   using iofstream = ::file::file_stream;

   using stringstream = ::file::plain_text_stream_string_buffer;
   using ostringstream = ::file::plain_text_ostream_string_buffer;

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


   using streamsize = file_size_t;
   using streampos = file_position_t;
   using streamoff = file_offset_t;

   using setw = ::file::set_width;

#if !defined(WINDOWSEX) && !defined(APPLEOS) && !defined(METROWIN)

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
inline string & to_json(string & str, const T & value)
{

   return str = ::str::from(value);

}


CLASS_DECL_ACE void dappy(const char * psz);




#include "ace/primitive/primitive_color.h"


#include "ace/graphics/graphics.h"


#include "ace/ace/ace/ace_str_context.h"


#include "ace/filesystem/file/file_html_buffer.h"


#include "ace/primitive/data/data_simple_item.h"


#include "ace/primitive/data/data_tree_item.h"


#include "ace/primitive/data/data_tree.h"


#include "ace/filesystem/file/file_edit_buffer.h"


CLASS_DECL_ACE int trace_hr(const char * psz,HRESULT hr);







CLASS_DECL_ACE void set_ace(void * p,::ace::application * papp);
CLASS_DECL_ACE ::ace::application * get_ace(void * p);



#include "ace/user/user.h"


#include "ace/ace/ace_speaker.h"






namespace user
{


   inline oswindow primitive::get_safe_handle() const
   {
      if(((byte *)this) < (byte *)(((byte *)NULL) + (16 * 1024))) // consider invalid
      {
         return NULL;
      }
      return get_handle();
   }






} // namespace user



#include "ace/primitive/primitive.inl"

#include "ace/filesystem/filesystem.inl"

#include "ace/net/net.inl"







