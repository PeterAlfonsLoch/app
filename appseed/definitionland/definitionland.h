#pragma once

#include "include/igui.h"
#include "include/_015ca2api00045.h"


#ifdef _CA2_FONTOPUS_DEFINITIONLAND_DLL
    #define CLASS_DECL_CA2_DEFINITIONLAND  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_DEFINITIONLAND  _declspec(dllimport)
#endif

#include "calendar.h"
#include "definitionland_document.h"
#include "definitionland_view.h"
#include "form_callback.h"

