#pragma once


#include "ca2.h"
#include "cairo/cairo.h"


#ifdef _CA2_DRAW2D_CAIRO_LIBRARY
    #define CLASS_DECL_DRAW2D_CAIRO  _declspec(dllexport)
#else
    #define CLASS_DECL_DRAW2D_CAIRO  _declspec(dllimport)
#endif



#include "draw2d_cairo_factory_exchange.h"
#include "draw2d_cairo_keep.h"


#include "draw2d_cairo_object.h"
#include "draw2d_cairo_pen.h"
#include "draw2d_cairo_bitmap.h"
#include "draw2d_cairo_brush.h"
#include "draw2d_cairo_font.h"
#include "draw2d_cairo_palette.h"
#include "draw2d_cairo_region.h"
#include "draw2d_cairo_dib.h"
#include "draw2d_cairo_path.h"


#include "draw2d_cairo_graphics.h"


#pragma comment(lib, "Msimg32.lib") 


