#pragma once


#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_FLAG_DLL
    #define CLASS_DECL_CA2_FLAG  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_FLAG  _declspec(dllimport)
#endif

namespace flag
{
   class application;
} // namespace flag

#undef App
#define App(pcaapp) (::flag::app_cast(pcaapp))

#include "document.h"
#include "view.h"
#include "frame.h"
#include "pane_view.h"
#include "pane_view_update_hint.h"

#include "application.h"
