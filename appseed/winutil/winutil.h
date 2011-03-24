#pragma once

#include "include/cube.h"

#ifdef _CA2_FONTOPUS_WINUTIL_DLL
    #define CLASS_DECL_CA2_WINUTIL  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINUTIL  _declspec(dllimport)
#endif

#include "document.h"
#include "view.h"
#include "frame.h"
#include "form_callback.h"

#include "pane_view_update_hint.h"
#include "pane_view.h"
#include "application.h"
