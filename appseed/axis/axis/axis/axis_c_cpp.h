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


namespace aura
{

   class impact;

}

namespace install
{

   class install;

} // namespace install


#undef CaSys
#undef Sys
#define CaSys(pca) (*pca->m_pauraapp->m_paxissystem)
#define Sys(paxisapp) (*paxisapp->m_paxissystem)
#define threadSystem (Sys(get_thread_app()))

#undef Sess
#define Sess(paxisapp) (*paxisapp->m_paxissession)
//#define Session (Sess(m_pauraapp))
//#define Plat(paxisapp) (*paxisapp->m_pcoreplatform)
//#define Platform (Plat(m_pauraapp))

#undef App
#undef Application
#define App(paxisapp) (*paxisapp->m_paxisapp)
#define Application (App(m_pauraapp->m_paxisapp))

#define AppUser(paxisapp) (*paxisapp->m_paxissession->fontopus()->get_user())
#define ApplicationUser (AppUser(m_pauraapp->m_paxisapp))




CLASS_DECL_AXIS bool axis_init();
CLASS_DECL_AXIS bool axis_term();

CLASS_DECL_AXIS bool __node_axis_pre_init();
CLASS_DECL_AXIS bool __node_axis_pos_init();

CLASS_DECL_AXIS bool __node_axis_pre_term();
CLASS_DECL_AXIS bool __node_axis_pos_term();


#include "axis/net/net.h"


#include "axis/filesystem/filesystem.h"


#include "axis/axis/geoip/geoip.h"


#if defined(LINUX)

#include "axis/os/ansios/ansios.h"

#elif defined(METROWIN)

#include "axis/os/metrowin/metrowin.h"

#elif defined(MACOS)

#include "axis/os/ansios/ansios.h"
#include "axis/os/macos/macos.h"

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



#if defined(METROWIN)

#include "app/appseed/axis/axis/os/metrowin/metrowin_sockets.h"

#endif


#include "axis/programming/javascript/javascript.h"

#include "axis/filesystem/fs/fs.h"

#include "axis/axis/fontopus/fontopus.h"

#include "axis/filesystem/file/file_application.h"

#include "axis/filesystem/file/file_dir_application.h"


#include "axis/graphics/graphics.h"


#include "axis/primitive/datetime/datetime_value.h"


#include "axis/primitive/datetime/datetime_departament.h"

#include "axis/database/database/database.h"

#include "axis/database/sqlitedb/sqlitedb.h"

#include "axis/database/simpledb/simpledb.h"

#include "axis_application.h"


#include "axis_session.h"

#include <openssl/md5.h>
#include "axis/filesystem/file/file_system.h"
#include "axis/filesystem/file/file_dir_system.h"


#include "axis/compress/compress.h"


#include "axis/crypto/crypto.h"

#include "axis/net/net_email_departament.h"

#include "axis_system.h"

#include "axis/install/install.h"





#ifdef METROWIN

#define BYESHYTOULA_STYLE_SOCKS

#else

#ifndef BSD_STYLE_SOCKETS

#define BSD_STYLE_SOCKETS 1

#endif

#endif


#include "axis_os.h"


#include "axis_static_start.h"


#include "axis_simple_app.h"


#include "app/appseed/axis/axis/node/node.h"




#include "primitive/data/data_tree_item.h"

#include "primitive/data/data_tree.h"

#include "primitive/data/data_simple_item.h"


//#include "axis/database/database/database.h"
//
//#include "axis/database/sqlitedb/sqlitedb.h"
//
//#include "axis/database/simpledb/simpledb.h"




#include "axis.inl"


