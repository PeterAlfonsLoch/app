#include "framework.h"
#include "graphics/cairo/cairo-xlib.h"


window_cairo::window_cairo()
{

    m_cairo                = NULL;
    m_cairosurface         = NULL;
    m_cairoSource          = NULL;
    m_cairosurfaceSource   = NULL;

}


window_cairo::~window_cairo()
{

}


void window_cairo::create(oswindow window, int64_t cxParam, int64_t cyParam, int iStrideParam)
{

   destroy();


   single_lock sl(&user_mutex(), true);

   xdisplay d(window->display());

   if(m_cairoSource != NULL)
   {

      cairo_destroy(m_cairoSource);

   }

   if(m_cairosurfaceSource != NULL)
   {

      cairo_surface_destroy(m_cairosurfaceSource);

   }

   if(m_cairosurface == NULL)
   {

      m_cairosurface = cairo_xlib_surface_create(window->display(), window->window(), window->visual(), cxParam, cyParam);

      m_cairo = cairo_create(m_cairosurface);

   }
   else
   {

      cairo_xlib_surface_set_size(m_cairosurface, cxParam, cyParam);

   }

   int32_t iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cxParam);

   m_mem.allocate(iStride * cyParam);

   m_cairosurfaceSource = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cxParam, cyParam, iStride);

   m_cairoSource = cairo_create(m_cairosurfaceSource);

   window_graphics::create(window, cxParam, cyParam, iStride);

}






void window_cairo::destroy()
{

   window_graphics::destroy();


}


void window_cairo::update_window(oswindow window, COLORREF * pOsBitmapData, LPCRECT lpcrect, int iStride)
{

   copy_colorref((COLORREF *) m_mem.get_data(), pOsBitmapData, iStride);

   cairo_surface_mark_dirty(m_cairosurfaceSource);

   try
   {

      cairo_set_operator(m_cairo, CAIRO_OPERATOR_SOURCE);

      cairo_reset_clip(m_cairo);

      cairo_set_source_surface(m_cairo, m_cairosurfaceSource, 0, 0);

      cairo_paint(m_cairo);


      #if TEST
      {

      cairo_rectangle(m_cairo, 10, 10, 50, 50);

      cairo_set_source_rgba(m_cairo, 84 / 255.0, 184 / 255.0, 77 / 255.0, 128 / 255.0);

      cairo_fill(m_cairo);

      }
      #endif

      cairo_show_page(m_cairo);

   }
   catch(...)
   {


   }

}



