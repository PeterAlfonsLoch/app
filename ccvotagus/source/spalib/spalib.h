#pragma once

#ifdef SPALIB_LIB
#define SPALIB_API
#elif defined(SPALIB_DLL)
#define SPALIB_API __declspec(dllexport)
#else
#define SPALIB_API __declspec(dllimport)
#endif


#include <string>
#include <vector>
#include <map>


#include "ccvotagus_ca2_spa.h"
