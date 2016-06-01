#include "framework.h"

#ifdef WINDOWS
#pragma warning(disable:4101)
#endif

#define NANOSVG_IMPLEMENTATION  // Expands implementation
#include "nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvgrast.h"
