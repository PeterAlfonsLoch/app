#include "framework.h"


#if defined(WINDOWS)

#include <mmsystem.h>
#endif

#if defined(LINUX)

#include <unistd.h>

#endif



#ifdef WINDOWS
//#include <WinInet.h>
//#include <Winternl.h>
#endif

#ifdef APPLEOS
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif


#undef App
#define App(papp) (papp->cast_app < ::install::application >())

#define ID_ONE 1


//O volume na unidade C n∆o tem nome.
//O N£mero de SÇrie do Volume Ç 72AC-5E14

//Pasta de C:\nordroid\app\appseed\axis\axis\install

#include "install.cpp"
#include "install_focus.cpp"
#include "install_install.cpp"
#include "install_installer_launcher.cpp"
#include "install_installer_square.cpp"
#include "install_small_bell.cpp"
#include "install_trace.cpp"
#include "install_trace_file.cpp"
#include "install_tool.cpp"
#include "install_socket_thread.cpp"
#include "install_socket_handler.cpp"
#include "install_socket.cpp"
#include "install_bootstrap.cpp"
#include "install_install_item.cpp"
#include "install_installer.cpp"

#ifdef WINDOWS

#include "windows/install_windows_boot.cpp"
#include "windows/install_windows_service.cpp"
#include "windows/install_windows_win.cpp"

#endif
//          3 arquivo(s)          4.530 bytes

//Total de Arquivos na Lista:
//         14 arquivo(s)        194.203 bytes
//          0 pasta(s)   19.202.347.008 bytes dispon°veis




#include "install_launcher.cpp"
#include "install_module_list.cpp"


#include "install_window.cpp"


#include "install_application.cpp"



