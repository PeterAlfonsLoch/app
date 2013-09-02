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
   
   m_nsimage = NULL;
}

simple_bitmap::~simple_bitmap()
{
   
   if(m_nsimage != 0)
   {
      
      destroy();
      
   }
   
}

bool simple_bitmap::create(int cx, int cy, simple_graphics & g,  COLORREF ** ppdata)
{
   
   /*BITMAPINFO m_Info;
    
    m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
    m_Info.bmiHeader.biWidth=cx;
    m_Info.bmiHeader.biHeight=cy;
    m_Info.bmiHeader.biPlanes=1;
    m_Info.bmiHeader.biBitCount=32;
    m_Info.bmiHeader.biCompression=BI_RGB;
    m_Info.bmiHeader.biSizeImage=cx*cy*4;*/
   
	m_mem.allocate(cx * cy * 4);
   
	memset(m_mem.get_data(), 0, m_mem.get_size());
   
	if(!create_from_data(cx, cy, (COLORREF *) m_mem.get_data(), g))
	{
      
      m_mem.allocate(0);
      
      return false;
      
	}
   
	if(ppdata != NULL)
	{
      
      *ppdata = (COLORREF *) m_mem.get_data();
      
	}
   
   return true;
   
}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{
   m_size.cx = cx;
   m_size.cy = cy;
   
   m_nsbitmap = [[NSBitmapImageRep alloc] initWithBitmapDataPlanes:nil
               
                                                      pixelsWide:m_size.cx
               
                                                      pixelsHigh:m_size.cy
               
                                                   bitsPerSample:8
               
                                                 samplesPerPixel:4
               
                                                        hasAlpha:YES
               
                                                        isPlanar:NO
               
                                                  colorSpaceName:NSCalibratedRGBColorSpace
               
                                                    bitmapFormat:0
               
                                                     bytesPerRow:(4 * m_size.cx)
               
                                                    bitsPerPixel:32];
   
   
   
   if(m_nsbitmap == 0)
   {
      
      return false;
      
   }
   
   m_nsimage = [[NSImage alloc] initWithCGImage:[m_nsbitmap CGImage] size: NSZeroSize];
   
   
   return true;
   
}



bool simple_bitmap::destroy()
{
   
   if(m_nsimage != NULL)
   {
      
      [m_nsimage release];
      
      m_nsimage = NULL;
      
   }
   
   if(m_nsbitmap != NULL)
   {
      
      [m_nsbitmap release];
      
      m_nsbitmap = NULL;
      
   }
   
   return true;
   
}

