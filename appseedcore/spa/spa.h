#pragma once


#include "os.h"


#ifdef SPALIB_LIB
#define SPALIB_API
#elif defined(SPALIB_DLL)
#define SPALIB_API __declspec(dllexport)
#else
#define SPALIB_API __declspec(dllimport)
#endif


#include "spa_ca2.h"

//SPALIB_API void spa();

