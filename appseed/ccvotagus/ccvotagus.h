#pragma once

#include "include/igui.h"


#ifdef _CA2_FONTOPUS_PAINT_DLL
    #define CLASS_DECL_CA2_PAINT  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_PAINT  _declspec(dllimport)
#endif

#include "font.h"
#include "style.h"
#include "elemental.h"

#include "text.h"
#include "image.h"
#include "input_text.h"
#include "input_button.h"

#include "document.h"

#include "paint_document.h"
#include "paint_view.h"

