//
//  c_os_simple_bitmap.cpp
//  c
//
//  Created by Carlos Gustavo Cecyn Lundgren on 10/6/12.
//
//
#import "c_os_gdi_mm.h"


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
   
   m_pdisplay = g.m_pdisplay;
   
   m_pixmap = XCreatePixmapFromBitmapData(g.m_pdisplay, g.m_d, (char *) pdata, cx, cy, BlackPixel(g.m_pdisplay, g.m_iScreen), WhitePixel(g.m_pdisplay, g.m_iScreen), 32);
   
   if(m_pixmap == 0)
   {
      
      m_pdisplay = NULL;
      
      return false;
      
   }
   
   
   return true;
   
}



bool simple_bitmap::destroy()
{
   
   if(m_pixmap == NULL)
      return true;
   
   
   bool bOk = ::XFreePixmap(m_pdisplay, m_pixmap) != FALSE;
   
   m_pixmap = 0;
   
   if(!bOk)
      return false;
   
   return true;
   
}

