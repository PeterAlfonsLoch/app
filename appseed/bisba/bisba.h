#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_BISBA_DLL
    #define CLASS_DECL_CA2_BISBA  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_BISBA  _declspec(dllimport)
#endif

namespace bisba
{
   class application;
} // namespace bisba

#undef App
#define App(pcaapp) (::bisba::app_cast(pcaapp))

#include "document.h"
#include "view.h"
#include "frame.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "application.h"
