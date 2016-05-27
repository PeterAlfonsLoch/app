#pragma once


#include "base/base/base.h"
#include "aura/graphics/graphics.h"
#include "aura/aura/aura/aura_printer.h"


#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#ifdef LINUX
#include <GL/glx.h>
#endif


#ifdef _DRAW2D_GL2D_STATIC
    #define CLASS_DECL_DRAW2D_GL2D
#elif defined(_DRAW2D_GL2D_LIBRARY)
    #define CLASS_DECL_DRAW2D_GL2D  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_DRAW2D_GL2D  CLASS_DECL_IMPORT
#endif


#include "draw2d_gl2d_factory_exchange.h"


#include "draw2d_gl2d_object.h"
#include "draw2d_gl2d_pen.h"
#include "draw2d_gl2d_bitmap.h"
#include "draw2d_gl2d_brush.h"
#include "draw2d_gl2d_font.h"
#include "draw2d_gl2d_palette.h"
#include "draw2d_gl2d_region.h"
#include "draw2d_gl2d_dib.h"
#include "draw2d_gl2d_path.h"

#include "draw2d_gl2d_printer.h"


#include "draw2d_gl2d_graphics.h"



#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_gl2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define GL2D_HDC(pgraphics) ((dynamic_cast < ::draw2d_gl2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))->get_handle())



