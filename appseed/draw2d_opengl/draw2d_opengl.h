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


#ifdef _DRAW2D_OPENGL_STATIC
    #define CLASS_DECL_DRAW2D_OPENGL
#elif defined(_DRAW2D_OPENGL_LIBRARY)
    #define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_DRAW2D_OPENGL  CLASS_DECL_IMPORT
#endif


#include "draw2d_opengl_factory_exchange.h"


#include "draw2d_opengl_object.h"
#include "draw2d_opengl_pen.h"
#include "draw2d_opengl_bitmap.h"
#include "draw2d_opengl_brush.h"
#include "draw2d_opengl_font.h"
#include "draw2d_opengl_palette.h"
#include "draw2d_opengl_region.h"
#include "draw2d_opengl_dib.h"
#include "draw2d_opengl_path.h"

#include "draw2d_opengl_printer.h"


#include "draw2d_opengl_graphics.h"



#define GL2D_GRAPHICS(pgraphics) (dynamic_cast < ::draw2d_opengl::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define GL2D_HDC(pgraphics) ((dynamic_cast < ::draw2d_opengl::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))->get_handle())



