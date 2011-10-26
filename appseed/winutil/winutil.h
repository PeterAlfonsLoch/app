#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_WINUTIL_DLL
    #define CLASS_DECL_CA2_WINUTIL  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINUTIL  _declspec(dllimport)
#endif


#include "winutil_document.h"
#include "winutil_view.h"
#include "winutil_frame.h"
#include "winutil_form_callback.h"


#include "winutil_pane_view_update_hint.h"
#include "winutil_pane_view.h"
#include "winutil_application.h"

