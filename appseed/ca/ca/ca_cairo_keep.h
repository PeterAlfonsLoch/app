#pragma once

#ifdef XYZNODEF

#include <cairo/cairo.h>



class CLASS_DECL_ca cairo_keep
{
public:


   cairo_t *         m_pdc;
   bool              m_bSave;

   static cairo_surface_t * g_cairosurface;
   static cairo_t *  g_cairo;


   cairo_keep(cairo_t * pdc, bool bSave = true);
   ~cairo_keep();


   void save();
   void restore();
   void pulse();


};


#endif