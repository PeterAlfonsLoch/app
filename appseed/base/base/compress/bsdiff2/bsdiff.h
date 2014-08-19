#pragma once


#include "bzlib.h"


#define libbsdif_API CLASS_DECL_BASE


libbsdif_API int32_t bsdiff(const char * oldfile, const char * newfile, const char * patchfile);
libbsdif_API int32_t bspatch(const char * oldfile, const char * newfile, const char * patchfile);
