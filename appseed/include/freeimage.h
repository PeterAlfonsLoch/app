#pragma once


#ifndef WINDOWS


#define _WINDOWS_ // for freeimage not including windows things included in cross windows includes


#define BOOL int


#endif


#include "FreeImage/FreeImage.h"

#pragma comment(lib, "FreeImage.lib")
