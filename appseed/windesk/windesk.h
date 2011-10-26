#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_WINDESK_DLL
    #define CLASS_DECL_CA2_WINDESK  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINDESK  _declspec(dllimport)
#endif


#include "document.h"
#include "view.h"
#include "frame.h"
#include "form_callback.h"
#include "menu_view.h"
#include "menu_right_view.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"
#include "application.h"


