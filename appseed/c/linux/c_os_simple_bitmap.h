#pragma once


class CLASS_DECL_c simple_bitmap
{
public:


   cairo_surface_t *       m_psurface;
   simple_memory           m_mem;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};

