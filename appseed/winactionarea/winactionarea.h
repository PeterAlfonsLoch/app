#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_WINACTIONAREA_DLL
    #define CLASS_DECL_CA2_WINACTIONAREA  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_WINACTIONAREA  _declspec(dllimport)
#endif


namespace winactionarea
{


   class application;


} // namespace winactionarea


#undef App
#define App(pcaapp) (winactionarea::app_cast(pcaapp))


#include "winactionarea_document.h"
#include "winactionarea_view.h"
#include "winactionarea_frame.h"
#include "winactionarea_form_callback.h"
#include "winactionarea_menu_view.h"
#include "winactionarea_menu_right_view.h"
#include "winactionarea_pane_view.h"
#include "winactionarea_pane_view_update_hint.h"


#include "winactionarea_application.h"

