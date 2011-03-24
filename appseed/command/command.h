#pragma once

#include "include/cube.h"

#ifdef _CA2_FONTOPUS_COMMAND_DLL
    #define CLASS_DECL_CA2_COMMAND  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_COMMAND  _declspec(dllimport)
#endif

#include "document.h"
#include "frame.h"
#include "view.h"
#include "primary_command_view.h"
#include "form_callback.h"

#include "application.h"