#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_PROJECTION_DLL
    #define CLASS_DECL_CA2_PROJECTION  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_PROJECTION  _declspec(dllimport)
#endif

namespace projection
{
   class application;
} // namespace projection

#undef App
#define App(pcaapp) (pcaapp->cast_app < projection::application > ())

#include "document.h"
#include "view.h"
#include "frame.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "application.h"
