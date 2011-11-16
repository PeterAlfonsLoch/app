#pragma once



#include "spa_spa.h"
#include "spa_starter_start.h"
#include "spa_boot.h"
#include "spa_cube_run.h"
#include "spa_small_bell.h"
#include "spa_install_ca2.h"
#include "spa_canvas.h"
#include "spa_window.h"
#include "spa_trace.h"
#include "spa_machine_event_data.h"
#include "spa_machine_event.h"
#include "spa_installer.h"




#pragma once

#ifdef CLASS_DECL_MACHINE_EVENT
#undef CLASS_DECL_MACHINE_EVENT
#endif

#define CLASS_DECL_MACHINE_EVENT

#include "resource.h"

#include "spa_machine_event_data.h"

#include "spa_focus.h"
#include "spa_machine_event_data.h"
#include "spa_machine_event.h"
#include "spa_http.h"
#include "spa_plugin.h"
#include "spa_installer.h"











CLASS_DECL_____ int bzuncompress(LPCTSTR lpcszUncompressed, LPCTSTR lpcszGzFileCompressed);


CLASS_DECL_____ int call_spaadmin(const char * pszCommandLine);


CLASS_DECL_____ void installation_file_lock(bool bLock);


CLASS_DECL_____ vsstring get_installation_lock_file_path();


CLASS_DECL_____ bool is_installation_lock_file_locked();