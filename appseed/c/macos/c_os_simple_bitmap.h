//
//  c_os_simple_bitmap.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once


class CLASS_DECL_c simple_bitmap
{
public:
   
   
   //Display *               m_pdisplay;
   //Pixmap                  m_pixmap;
   //simple_memory              m_mem;
   //SIZE                       m_size
   #ifdef __cplusplus
   void * m_pnsimage;
#else
   NSBitmapImageRep * m_nsimage;
   
#endif
   
   
   simple_bitmap();
   ~simple_bitmap();
   
   
   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();
   
   
};

