#include "framework.h"
#include "axis/net/net_sockets.h"
#include "axis/compress/compress.h"
#if defined(WINDOWS)

#include <mmsystem.h>
#endif
#if defined(LINUX) || defined(WINDOWS)
#include <omp.h>
#else
int omp_get_thread_num()
{
   return 0;
}
#endif

#if defined(LINUX)

#include <unistd.h>

#endif

#if defined(WINDOWS) || defined(LINUX)
#include <omp.h>
#else
extern int omp_get_thread_num();
#endif


#ifdef WINDOWS
#include <WinInet.h>
#include <Winternl.h>
#endif

#ifdef APPLEOS
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif

//O volume na unidade C n∆o tem nome.
 //O N£mero de SÇrie do Volume Ç 72AC-5E14

 //Pasta de C:\nordroid\app\appseed\axis\axis\install

#include "install.cpp"
#include "install_boot.cpp"
#include "install_bz.cpp"
#include "install_canvas.cpp"
#include "install_focus.cpp"
#include "install_install.cpp"
#include "install_installer.cpp"
//#include "install_installer_square.cpp"
#include "install_small_bell.cpp"
#include "install_trace.cpp"
//2015-01-04  19:35                 0 _install.cpp"
//              11 arquivo(s)        189.673 bytes
//
// Pasta de C:\nordroid\app\appseed\axis\axis\install\windows

#ifdef WINDOWS

#include "windows/install_windows_boot.cpp"
#include "windows/install_windows_service.cpp"
#include "windows/install_windows_win.cpp"

#endif
     //          3 arquivo(s)          4.530 bytes

     //Total de Arquivos na Lista:
     //         14 arquivo(s)        194.203 bytes
     //          0 pasta(s)   19.202.347.008 bytes dispon°veis
