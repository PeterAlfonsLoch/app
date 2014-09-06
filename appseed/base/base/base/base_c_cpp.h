#pragma once


namespace plane
{

   class session;
   class system;
   //class cube;


} // namespace plane


namespace html
{

   class html;

} // namespace html


namespace user
{

   class schema;
   class tree;

}

namespace user
{

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


namespace install
{

   class install;

} // namespace install


#undef CaSys
#undef Sys
#define CaSys(pca) (*pca->m_pauraapp->m_pbasesystem)
#define Sys(pbaseapp) (*pbaseapp->m_pbasesystem)
#define threadSystem (Sys(get_thread_app()))

#undef Sess
#define Sess(paxisapp) (*paxisapp->m_pbasesession)
//#define Session (Sess(m_pauraapp))
//#define Plat(paxisapp) (*paxisapp->m_pcoreplatform)
//#define Platform (Plat(m_pauraapp))

#undef App
#undef Application
#define App(paxisapp) (*paxisapp->m_pbaseapp)
#define Application (App(m_pauraapp->m_pbaseapp))

#define AppUser(pbaseapp) (*pbaseapp->m_pbasesession->fontopus()->get_user())
#define ApplicationUser (AppUser(m_pauraapp->m_pbaseapp))




CLASS_DECL_BASE bool base_init();
CLASS_DECL_BASE bool base_term();

CLASS_DECL_BASE bool __node_base_pre_init();
CLASS_DECL_BASE bool __node_base_pos_init();

CLASS_DECL_BASE bool __node_base_pre_term();
CLASS_DECL_BASE bool __node_base_pos_term();



#include "base/net/net.h"


#include "base/filesystem/filesystem.h"


#include "base/base/geoip/geoip.h"


#if defined(LINUX)

#include "base/os/ansios/ansios.h"

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


#include "base/graphics/graphics.h"


#include "base_application.h"


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





#include "base/net/http/http.h"


#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#ifndef BSD_STYLE_SOCKETS

#define BSD_STYLE_SOCKETS 1

#endif

#endif


#include "base_os.h"


#include "base_static_start.h"


#include "base_simple_app.h"


#include "app/appseed/base/base/node/node.h"











#include "base.inl"


