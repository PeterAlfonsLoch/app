#pragma once

#define _BIND_TO_CURRENT_CRT_VERSION 1
#define _CRT_NOFORCE_MANIFEST
#define _STL_NOFORCE_MANIFEST


extern "C"
{
   __declspec(selectany)  int _forceCRTManifest;
}

#define NOTHROW throw()
#define THROWS throw(...)

#define WINVER 0x0502
#define _WIN32_WINNT	0x0502

#define VC_EXTRALEAN

/*
#ifndef _NOFORCE_CRT_MANIFEST

//#include <crtassem.h>

#ifdef _DEBUG
#define __LIBRARIES_SUB_VERSION	"Debug"
#else
#define __LIBRARIES_SUB_VERSION	""
#endif

// Manifest for the CRT
#pragma comment(linker,"/manifestdependency:\"type='win32' "						\
	"name='" __LIBRARIES_ASSEMBLY_NAME_PREFIX "." __LIBRARIES_SUB_VERSION "CRT' "   \
	"version='" _CRT_ASSEMBLY_VERSION "' "											\
	"processorArchitecture='x86' \"")

#endif
*/

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
