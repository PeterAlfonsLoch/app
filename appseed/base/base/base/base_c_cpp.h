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

namespace base
{

   class application;
   class system;
   class application_signal_details;
   class copydesk;

   typedef smart_pointer < copydesk > copydesk_sp;
   class command;



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
class command_target;
class cmd_ui;
class critical_section;
class mutex;
class stringa;
class string;
class id;



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


namespace user
{

   class interaction_impl;
   class view_creator_data;
   class schema;
   class tree;

}

typedef sp(::user::interaction_impl) window_sp;

namespace user
{

   class interaction;
   class control_event;
   class create_context;
   class impact;
   class printer;
   class user;
   class document;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}

namespace base
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

} // namespace base



class message_queue_listener;
class image_list;



#ifndef WINDOWSEX
typedef void * HDWP;
#endif // WINDOWS



typedef struct tagRECTD RECTD;


namespace base
{

   class live_object;

#if defined METROWIN && defined(__cplusplus_winrt)

   interface class system_window
   {
      
      virtual Windows::Foundation::Rect get_window_rect() = 0;
      virtual Windows::Foundation::Point get_cursor_pos() = 0;


    
   };

   CLASS_DECL_BASE bool get_window_rect(system_window ^ pwindow,RECTD * lprect);
   CLASS_DECL_BASE bool get_window_rect(system_window ^ pwindow,LPRECT lprect);

#endif


   class file;


   namespace trace
   {

      class trace;

   }

   class session;

} // namespace base


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


namespace user
{

   class place_holder;
   class menu_base_item;

#if defined METROWIN && defined(__cplusplus_winrt)

    class CLASS_DECL_BASE native_window_initialize
   {
   public:


      Platform::Agile<Windows::UI::Core::CoreWindow> window;
      ::base::system_window ^ pwindow;


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





} // namespace user




namespace install
{

   class install;

} // namespace install



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

#undef CaSys
#undef Sys
#define CaSys(pca) (*pca->m_pbaseapp->m_pbasesystem)
#define Sys(pbaseapp) (*pbaseapp->m_pbasesystem)
#define threadSystem (Sys(get_thread_app()))


//#undef App
//#define App(pbaseapp) (*pbaseapp)
//#define Application (App(m_pbaseapp))


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





CLASS_DECL_BASE bool base_init();
CLASS_DECL_BASE bool base_term();

CLASS_DECL_BASE bool __node_pre_init();
CLASS_DECL_BASE bool __node_pos_init();

CLASS_DECL_BASE bool __node_pre_term();
CLASS_DECL_BASE bool __node_pos_term();



#include "base/net/net.h"


#include "base/filesystem/filesystem.h"


#include "base/base/geoip/geoip.h"


#if defined(LINUX)

#include "base/os/ansios/ansios.h"
#include "base/os/linux/linux_user_impl.h"

#elif defined(METROWIN)

#include "base/os/metrowin/metrowin.h"
#include "base/os/metrowin/metrowin_user_impl.h"

#elif defined(MACOS)

#include "base/os/ansios/ansios.h"
#include "base/os/macos/macos.h"
#include "base/os/macos/macos_windowing.h"

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

#include "base/user/userpresence/userpresence.h"

#include "base/filesystem/fs/fs.h"

#include "base/user/fontopus/fontopus.h"

#include "base/filesystem/file/file_application.h"
#include "base/filesystem/file/file_dir_application.h"


#include "base_application.h"


#include "base_session_interface.h"
#include "base_session.h"

#include "base/net/net_url_departament.h"
#include "base/net/net_url_domain.h"


#include "base/filesystem/file/file_system.h"
#include "base/filesystem/file/file_dir_system.h"


#include "base/compress/compress.h"


#include "base/crypto/crypto.h"


#include "base_system.h"

#include "base/hotplugin/hotplugin.h"

#include "base/install/install.h"



#define AppUser(pbaseapp) (*pbaseapp->m_pbasesession->fontopus()->get_user())
#define ApplicationUser (AppUser(m_pbaseapp))



#include "base/net/http/http.h"
//#include "base_microtimer.h"








//#include "base/vms/vms.h"


//#include "base_cpu_architecture.h"


//#include "base_libc.h"


//#include "base_number.h"


//#include "base_debug.h"
//
//
//#include "base_printf.h"
//#include "base_sprintf.h"



//#include "base_math.h"







#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#ifndef BSD_STYLE_SOCKETS
#define BSD_STYLE_SOCKETS 1
#endif
   //#include "base_small_ipc_channel.h"

#endif



//#include "base_file_watcher.h"
//#include "base_file_watcher_impl.h"


#include "base_os.h"


//#include "base/multithreading/multithreading_data.h"


//#include "base_simple_shell_launcher.h"


//#include "base_file_watcher_thread.h"
//#include "base_file_watcher_listener_thread.h"
//#include "base_async.h"


   //#include "base/hotplugin/hotplugin.h"




//#include "base_message_loop.h"

//#include "base_url.h"

//#include "base_international.h"

//#include "base_static_start.h"


//
//#define return_(y, x) {y = x; return;}
//
//
//   extern "C"
//   {
//
//
//      int32_t _c_lock_is_active(const char * pszName);
//      int32_t _c_lock(const char * pszName, void ** pdata);
//      int32_t _c_unlock(void ** pdata);
//
//
//   }
//
//
//   CLASS_DECL_BASE string _ca_get_file_name(const char * psz, bool bCreate = false, int32_t * pfd = NULL);
//
//   CLASS_DECL_BASE string get_system_error_message(uint32_t dwError);
//

#include "base_simple_app.h"




/*#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)


template < class T >
bool ::file::system::output(sp(::axis::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::file::binary_buffer_sp fileOut = sess(papp).file().get_file(pszOutput, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::output_stream ostream(fileOut);

   return (p->*lpfnOuput)(ostream, lpszSource);

}


template < class T >
bool ::file::system::output(sp(::axis::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, ::file::input_stream &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   string strDownloading = pszOutput;

   strDownloading += ".downloading";

   ::file::binary_buffer_sp fileOut = sess(papp).file().get_file(strDownloading, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::binary_buffer_sp fileIn = sess(papp).file().get_file(lpszInput, ::file::type_binary | ::file::mode_read);

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



*/







#include "app/appseed/base/base/node/node.h"



//#include "base/user/simple/simple.h"
//#include "base/user/simple_ui/simple_ui.h"
