#pragma once


class simple_brush;
class simple_bitmap;
class simple_font;
class simple_pen;


class simple_path;


class simple_graphics;


#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define ARGB(a, r, g, b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))


#include "c_graphics_round_rect.h"







