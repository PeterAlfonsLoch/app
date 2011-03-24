#pragma once

#include "include/igui.h"
#include "include/filemanager.h"
#include "include/html.h"


#ifdef _CA2_FONTOPUS_PAINTAPPLICATION_DLL
    #define CLASS_DECL_CA2_PAINTAPPLICATION  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_PAINTAPPLICATION  _declspec(dllimport)
#endif

#include "paint_application.h"

