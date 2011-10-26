#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_HELLOMULTIVERSE_DLL
    #define CLASS_DECL_CA2_HELLOMULTIVERSE  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_HELLOMULTIVERSE  _declspec(dllimport)
#endif

namespace hellomultiverse
{

   class application;


} // namespace flag

#undef App
#define App(pcaapp) (::hellomultiverse::app_cast(pcaapp))

#include "document.h"
#include "view.h"
#include "frame.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "application.h"
