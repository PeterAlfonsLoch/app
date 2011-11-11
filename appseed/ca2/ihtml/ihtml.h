#pragma once

#include "include/igui.h"
#include "shared/vmsconfiguration.h"


#ifdef _CA2_FONTOPUS_IHTML_DLL
    #define CLASS_DECL_CA2_IHTML  _declspec(dllexport)
#else
    #define CLASS_DECL_CA2_IHTML  _declspec(dllimport)
#endif

#include "signal.h"
#include "view_update_hint.h"

#include "document.h"
#include "document_container.h"

#include "form.h"
#include "view.h"
