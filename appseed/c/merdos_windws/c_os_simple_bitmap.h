#pragma once


class CLASS_DECL_c simple_bitmap
{
public:


   ID2D1Bitmap1 *          m_pbitmap;
   D2D1_MAPPED_RECT        m_map;


   simple_bitmap();
   ~simple_bitmap();


   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();


};




