//
//  c_os_simple_bitmap.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#import "ca_os_graphics_mm.h"


simple_bitmap::simple_bitmap()
{
   
   m_context = NULL;

}

simple_bitmap::~simple_bitmap()
{
   
   destroy();
   
}

bool simple_bitmap::create(int cx, int cy, simple_graphics & g,  COLORREF ** ppdata)
{
   
   destroy();
   
   scan = cx * 4;
   
   CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
   
   m_context = CGBitmapContextCreate(NULL, cx, cy, 8, scan, colorspace, kCGImageAlphaPremultipliedLast);
   
   CGColorSpaceRelease(colorspace);
   
   if(m_context == NULL)
   {
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      scan = 0;
      
      return false;
      
   }
   
   m_pdata = (COLORREF *) CGBitmapContextGetData(m_context);
   
   
   if(m_pdata == NULL)
   {
      
      destroy();
      
      return false;
      
   }
   
   if(ppdata != NULL)
   {
      
      *ppdata = m_pdata;
      
   }
   
   m_size.cx = cx;
   
   m_size.cy = cy;
   
   return true;
   
}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{
   
   destroy();
   
   scan = cx * 4;
   
   CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
   
   m_context = CGBitmapContextCreate(NULL, cx, cy, 8, scan, colorspace, kCGImageAlphaPremultipliedLast);
   
   CGColorSpaceRelease(colorspace);
   
   if(m_context == NULL)
   {
      
      m_size.cx = 0;
      
      m_size.cy = 0;
      
      scan = 0;
      
      return false;
      
   }
   
   m_pdata = (COLORREF *) CGBitmapContextGetData(m_context);
   
   
   if(m_pdata == NULL)
   {
      
      destroy();
      
      return false;
      
   }
   
   if(pdata != NULL)
   {
      
      memcpy(m_pdata, pdata, cy * scan);
      
   }
   
   m_size.cx = cx;
   
   m_size.cy = cy;
   
   return true;
   
   
}



bool simple_bitmap::destroy()
{
   
   if(m_context == NULL)
      return true;
   
   CGContextRelease(m_context);
   
   m_context = NULL;
   
   m_pdata = NULL;
   
   m_size.cx = 0;
   
   m_size.cy = 0;
   
   scan = 0;
   
   return true;
   
}

