#pragma once

#include "include/ca2.h"

#ifdef _CA2_FONTOPUS_LOGINSTARTUP_DLL
    #define CLASS_DECL_CA2_LOGINSTARTUP  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_LOGINSTARTUP  _declspec(dllimport)
#endif

#include "loginstartup_document.h"
#include "loginstartup_view.h"
#include "form_callback.h"

