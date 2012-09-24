#pragma once


class CLASS_DECL_c simple_bitmap
{
public:


   Display *               m_pdisplay;
   Pixmap                  m_pixmap;
   simple_memory           m_mem;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};

