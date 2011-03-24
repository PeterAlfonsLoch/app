#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_WINSHELLLINK_DLL
    #define CLASS_DECL_CA2_WINSHELLLINK  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINSHELLLINK  _declspec(dllimport)
#endif

#include "winshelllink_document.h"
#include "winshelllink_view.h"
#include "form_callback.h"

#include "pane_view_update_hint.h"
#include "pane_view.h"
#include "application.h"
