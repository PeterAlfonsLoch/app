#pragma once

#include "include/ca2.h"


#ifdef _CA2_FONTOPUS_STATUS_DLL
    #define CLASS_DECL_CA2_STATUS  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_STATUS  _declspec(dllimport)
#endif

#include "document.h"
#include "class.h"
#include "frame.h"
#include "view.h"
#include "application.h"

