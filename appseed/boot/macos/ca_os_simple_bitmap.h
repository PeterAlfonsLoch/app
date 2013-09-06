//
//  c_os_simple_bitmap.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once

class simple_graphics;





class CLASS_DECL_ca simple_bitmap
{
public:
   
   
   //Display *               m_pdisplay;
   //Pixmap                  m_pixmap;
   simple_memory              m_mem;
   SIZE                       m_size;
#ifdef __MM
   
   NSBitmapImageRep *         m_nsbitmap;
   NSImage *                  m_nsimage;
   
#else
   
   void *                     m_pnsbitmap;
   void *                     m_pnsimage;
   
#endif
   
   
   simple_bitmap();
   ~simple_bitmap();
   
   
   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();
   
   
};

