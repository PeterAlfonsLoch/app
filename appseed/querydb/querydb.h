#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_QUERYDB_DLL
    #define CLASS_DECL_CA2_QUERYDB  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_QUERYDB  _declspec(dllimport)
#endif

namespace querydb
{
   class application;
} // namespace querydb

#undef App
#define App(pcaapp) (querydb::app_cast(pcaapp))

#include "document.h"
#include "view.h"
#include "table_view.h"
#include "frame.h"
#include "form_callback.h"
#include "query_view.h"
#include "query_edit_view.h"
#include "menu_right_view.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "application.h"
