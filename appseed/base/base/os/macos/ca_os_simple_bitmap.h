//
//  c_os_simple_bitmap.h
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 9/30/12.
//
//
#pragma once

class simple_graphics;





class CLASS_DECL_BOOT simple_bitmap
{
public:
   
   
   COLORREF *              m_pdata;
   ::size                  m_size;
   CGContextRef            m_context;
   int32_t                 scan;
   
   
   simple_bitmap();
   ~simple_bitmap();
   
   
   bool create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata = NULL);
   bool create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g);
   bool destroy();
   
   
};

