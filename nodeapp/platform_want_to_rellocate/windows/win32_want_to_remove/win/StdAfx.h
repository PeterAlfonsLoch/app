#pragma once

#define IMPLEMENT_VISTA_TOOLS
#include "win.h"
#include "win_internal.h"

CLASS_DECL_VMSWIN void vfxThrowFileException(::ca::application * papp, int cause, LONG lOsError, const char * lpszFileName = NULL);
