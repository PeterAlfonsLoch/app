
#pragma once


class CLASS_DECL_ca simple_bitmap
{
public:

   
   Gdiplus::Bitmap *             m_pbitmap;
   simple_memory                 m_memory;
   SIZE                          m_size;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int32_t cx, int32_t cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int32_t cx, int32_t cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};
