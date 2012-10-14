
#pragma once


class CLASS_DECL_c simple_bitmap
{
public:

   
   Gdiplus::Bitmap *             m_pbitmap;
   simple_memory                 m_memory;
   SIZE                          m_size;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};
