#pragma once


#include "cairo/cairo.h"


class CLASS_DECL_AURA window_cairo :
   public window_graphics
{
public:


   cairo_t *                     m_cairo;
   cairo_surface_t *             m_cairosurface;
   cairo_t *                     m_cairoSource;
   cairo_surface_t *             m_cairosurfaceSource;
   ::primitive::memory                 m_mem;


   window_cairo();
   virtual ~window_cairo();

   virtual void create_window_graphics(oswindow window, int64_t cx, int64_t cy, int iStride = -1);
   virtual void destroy_window_graphics();

   virtual void update_window(oswindow window, COLORREF * pOsBitmapData, const RECT & lpcrect, int iStride = -1);

};
