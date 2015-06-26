#include "framework.h"
#include "aura/node/windows/windows.h"
#include "aura/graphics/graphics.h"
#include <fcntl.h>
#include "windows.h"
#include <VersionHelpers.h>
#undef new
#define min MIN
#define max MAX
#include <gdiplus.h>
#undef min
#undef max
#define new AURA_NEW
#include <ddeml.h>
#include <share.h>
#include <io.h>
//#include <fcntl.h>
#include <process.h>    // for _beginthreadex and _endthreadex
#include <Winsvc.h>

//O volume na unidade Z ‚ eco
// O N£mero de S‚rie do Volume ‚ 4A91-94E4
//
// Pasta de Z:\ca2\app\appseed\aura\aura\os\windows
//
#include "windows_ansi_file.cpp"
#include "windows_base_file.cpp"
#include "windows_base_process.cpp"
#include "windows_base_registry.cpp"
#include "windows_debug.cpp"
#include "windows_dll.cpp"
#include "windows_error.cpp"
#include "windows_file_watcher.cpp"
#include "windows_gdi.cpp"
#include "windows_gdi_cursor.cpp"
#include "windows_gdi_icon.cpp"
#include "windows_internal.cpp"
#include "windows_launcher.cpp"
#include "windows_library.cpp"
#include "windows_local_memory_map.cpp"
#include "windows_lock.cpp"
#include "windows_main.cpp"
#include "windows_message_loop.cpp"
#include "windows_multithreading.cpp"
//#include "windows_printer.cpp"
//#include "windows_registry.cpp"
#include "windows_simple_app.cpp"
#include "windows_simple_shell_launcher.cpp"
//#include "windows_simple_ui.cpp"
#include "windows_small_ipc_channel.cpp"
#include "windows_time.cpp"
#include "windows_util.cpp"
#include "windows_utils.cpp"
//2015-01-05  08:08                 0 _windows_os.cpp"
//              30 arquivo(s)        121.416 bytes
//               0 pasta(s)   35.770.142.720 bytes dispon¡veis

//#include "windows_console_window.cpp"



#include "windows_base.cpp"
