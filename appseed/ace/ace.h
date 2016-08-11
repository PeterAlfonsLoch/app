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



#include "ace_alloc.h"




