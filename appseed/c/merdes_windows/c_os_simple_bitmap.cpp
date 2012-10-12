#include "framework.h"


simple_bitmap::simple_bitmap()
{
   
   m_hbitmap = NULL;

}

simple_bitmap::~simple_bitmap()
{
   
   if(m_hbitmap != NULL)
   {

      destroy();

   }

}

bool simple_bitmap::create(int cx, int cy, simple_graphics & g, COLORREF ** ppdata)
{

   UNREFERENCED_PARAMETER(g);

   BITMAPINFO m_Info;

	m_Info.bmiHeader.biSize=sizeof (BITMAPINFOHEADER);
	m_Info.bmiHeader.biWidth=cx;
	m_Info.bmiHeader.biHeight=cy;
	m_Info.bmiHeader.biPlanes=1;
	m_Info.bmiHeader.biBitCount=32;
	m_Info.bmiHeader.biCompression=BI_RGB;
	m_Info.bmiHeader.biSizeImage=cx*cy*4;

	m_hbitmap = CreateDIBSection ( NULL, &m_Info, DIB_RGB_COLORS, (void **)ppdata, NULL, 0);

   if(m_hbitmap == NULL)
      return false;

   return true;

}


bool simple_bitmap::create_from_data(int cx, int cy, COLORREF * pdata, simple_graphics & g)
{

   UNREFERENCED_PARAMETER(g);

   m_hbitmap = ::CreateBitmap(cx, cy, 1, 32, pdata);

   if(m_hbitmap == NULL)
      return false;

   return true;

}



bool simple_bitmap::destroy()
{
   
   if(m_hbitmap == NULL)
      return true;


   bool bOk = ::DeleteObject(m_hbitmap) != FALSE;

   m_hbitmap = NULL;

   if(!bOk)
      return false;

   return true;

}
