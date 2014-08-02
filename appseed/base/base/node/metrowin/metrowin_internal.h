#pragma once


#undef new
#include <GdiPlus.h>
#include <Gdipluseffects.h>

#define new BASE_NEW

#include <wincrypt.h>


#include "metrowin_dir.h"
#include "metrowin_file_find.h"
#include "metrowin_file_system.h"
#include "metrowin_file.h"
#include "metrowin_shell.h"
//#include "ca2/ex1_resource.h"
#include "metrowin_resource.h"
//#include "application.h"
#include "metrowin_stdio_file.h"
#include "metrowin_file_set.h"

#include "metrowin_copydesk.h"
#include "metrowin_crypto.h"
#include "metrowin_ip_enum.h"
#include "metrowin_registry.h"

#include "metrowin_os.h"


// Sanity checks for ATOMs
//CLASS_DECL_metrowin bool __is_valid_atom(ATOM nAtom);
//CLASS_DECL_metrowin bool __is_valid_atom(const char * psz);
