#pragma once

#include "include/igui.h"


#ifdef _CA2_FONTOPUS_HTML_DLL
    #define CLASS_DECL_CA2_HTML  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_HTML  _declspec(dllimport)
#endif

#include "font.h"
#include "style.h"
#include "elemental.h"

#include "text.h"
#include "image.h"
#include "input_text.h"
#include "input_button.h"

#include "document.h"

#include "html_document.h"
#include "html_view.h"

