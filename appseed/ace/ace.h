#pragma once


#include "_ace.h"


#ifdef _WIN32
#ifdef _APP_ACE_SHARED
#define CLASS_DECL_ACE __declspec(dllexport)
#else
#define CLASS_DECL_ACE __declspec(dllimport)
#endif
#else
#define CLASS_DECL_ACE
#endif


#if !defined(_ACID_LIBRARY)


#pragma comment(lib, "_ace.lib")


#include "ace_alloc.h"


#endif




