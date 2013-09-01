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

#include "spa_focus.h"
#include "spa_http.h"
#include "spa_login.h"
#include "spa_plugin.h"











CLASS_DECL_ca int32_t bzuncompress(LPCSTR lpcszUncompressed, LPCSTR lpcszGzFileCompressed);


CLASS_DECL_ca int32_t synch_spaadmin(const char * pszCommandLine);


CLASS_DECL_ca int32_t start_spaadmin(const char * pszCommandLine);


CLASS_DECL_ca void installation_file_lock(bool bLock);


CLASS_DECL_ca vsstring get_installation_lock_file_path();


CLASS_DECL_ca bool is_installation_lock_file_locked();




class CLASS_DECL_ca installation_lock_file_lock
{
public:


   installation_lock_file_lock();
   ~installation_lock_file_lock();


};



