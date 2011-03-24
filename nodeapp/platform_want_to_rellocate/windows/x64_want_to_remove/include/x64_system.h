#pragma once

#define core_level 2

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
#define _WIN64_WINNT	0x0502

#define VC_EXTRALEAN

#ifndef _NOFORCE_CRT_MANIFEST

#ifdef _DEBUG
#define __LIBRARIES_SUB_VERSION	"Debug"
#else
#define __LIBRARIES_SUB_VERSION	""
#endif


#endif