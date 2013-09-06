#pragma once


class CLASS_DECL_c simple_bitmap
{
public:


   cairo_surface_t *       m_psurface;
   ::primitive::memory           m_mem;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int32_t cx, int32_t cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int32_t cx, int32_t cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};

