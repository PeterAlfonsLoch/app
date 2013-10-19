#include "framework.h"

simple_bitmap::simple_bitmap()
{

   m_psurface = NULL;

}

simple_bitmap::~simple_bitmap()
{

   if(m_psurface != NULL)
   {

      destroy();

   }

}

bool simple_bitmap::create(int32_t cx, int32_t cy, simple_graphics & g,  COLORREF ** ppdata)
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


bool simple_bitmap::create_from_data(int32_t cx, int32_t cy, COLORREF * pdata, simple_graphics & g)
{

   if(m_psurface != NULL)
   {

      destroy();

   }

   int32_t iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, cx);

   m_mem.allocate(iStride * cy);

   if(cx * 4 != iStride)
   {

      int32_t iW = cx * 4;

      for(int32_t i = 0; i < cy; i++)
      {

         memcpy(&((byte *) m_mem.get_data())[iStride * i], &pdata[iW * i], iW);

      }

   }
   else
   {
      memcpy(m_mem.get_data(), pdata, iStride * cy);
   }


   m_psurface = cairo_image_surface_create_for_data((unsigned char *) m_mem.get_data(), CAIRO_FORMAT_ARGB32, cx, cy, iStride);

   if(m_psurface == NULL)
   {

      return false;

   }


   return true;

}



bool simple_bitmap::destroy()
{

   if(m_psurface == NULL)
      return true;

   if(m_psurface == ca_cairo_keep::g_cairosurface)
   {
   
      printf("123");

   }

   cairo_surface_destroy(m_psurface);

   return true;

}

