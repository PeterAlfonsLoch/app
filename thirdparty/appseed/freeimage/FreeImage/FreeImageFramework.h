#ifndef __GNUC__
#pragma once
#endif


#include "base/base/base/base.h"


#ifdef _MSC_VER
#pragma warning (disable : 4786) // identifier was truncated to 'number' characters
#endif


/*
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <ctype.h>
#endif // _WIN32


#include <stdlib.h>
#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__)
#include <malloc.h>
#endif // _WIN32 || _WIN64 || __MINGW32__

#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <ASSERT.h>
#include <errno.h>
#include <float.h>
#include <limits.h>

//
//#include <list>
//#include <map>
//#include <set>
//
//#include <stack>
//
//
//
//#include <memory>
*/

#include "freeimage.h"
#include "CacheFile.h"
#include "FreeImageIO.h"
#include "Plugin.h"
#include "Utilities.h"
#include "Quantizers.h"
#include "../Metadata/FreeImageTag.h"


