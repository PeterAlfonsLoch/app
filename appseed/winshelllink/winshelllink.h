#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_WINSHELLLINK_DLL
    #define CLASS_DECL_CA2_WINSHELLLINK  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINSHELLLINK  _declspec(dllimport)
#endif


#include "winshelllink_document.h"
#include "winshelllink_frame.h"
#include "winshelllink_view.h"
#include "winshelllink_form_callback.h"


#include "winshelllink_pane_view_update_hint.h"
#include "winshelllink_pane_view.h"
#include "winshelllink_application.h"


