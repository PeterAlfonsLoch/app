#pragma once


#include "app/appseed/core/core.h" // System.ftlibrary()


#include "ft2build.h"
#include FT_FREETYPE_H


#include "app/base/cairo/cairo.h"
#include "app/base/cairo/cairo-ft.h"


mutex & cairo_mutex();
void init_cairo_mutex(sp(::base::application) papp);


#ifdef _DRAW2D_CAIRO_LIBRARY
    #define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_DRAW2D_CAIRO  CLASS_DECL_IMPORT
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


