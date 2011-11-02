#pragma once


#include "bzlib.h"


#define libbsdif_API CLASS_DECL_____


libbsdif_API int bsdiff(const char * oldfile, const char * newfile, const char * patchfile);
libbsdif_API int bspatch(const char * oldfile, const char * newfile, const char * patchfile);
