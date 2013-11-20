#pragma once


class CLASS_DECL_BASE simple_bitmap
{
public:


   cairo_surface_t *       m_psurface;
   ::primitive::memory           m_mem;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int32_t cx, int32_t cy, ::draw2d::graphics * pgraphics, COLORREF ** ppdata = NULL);
   bool create_from_data(int32_t cx, int32_t cy, COLORREF * pdata, ::draw2d::graphics * pgraphics);
   bool destroy();


};

